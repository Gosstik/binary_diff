#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdio>
#include <limits>

namespace fs = std::filesystem;

constexpr size_t kSymbolsInByte = 1 << 8;

void ZeroInds(std::array<size_t, kSymbolsInByte>& inds) {
  for (size_t i = 0; i < kSymbolsInByte; ++i) {
    inds[i] = 0;
  }
}

size_t GetApproximateLcs(const std::string& str2,
                         const std::array<std::vector<size_t>, kSymbolsInByte>& occurs,
                         std::array<size_t, kSymbolsInByte>& inds,
                         size_t window_size) {
  // Result.
  size_t lcs_len = 0;

  // Init
  ZeroInds(inds);
  size_t left_bound = 0;

  // Algo
  for (size_t i = 0; i < str2.size(); ++i) {
    size_t cur_s = str2[i];

    size_t ind = inds[cur_s];
    while (ind < occurs[cur_s].size() && occurs[cur_s][ind] < left_bound) {
      ++ind;
    }
    inds[cur_s] = ind;

    // No occurrences or all symbols are on the left of left_border.
    if (ind == occurs[cur_s].size()) {
      continue;
    }

    if (occurs[cur_s][ind] - i < window_size) {
      left_bound = occurs[cur_s][ind];
      ++lcs_len;
    } else {
      continue;
    }
  }

  return lcs_len;
}

double GetDifference(const std::string& str1, const std::string& str2) {
  // Check if files equal.
  if (str1 == str2) {
    return 100.0;
  }

  // Generate array of symbols occurrences.
  std::array<std::vector<size_t>, kSymbolsInByte> occurs;
  for (size_t i = 0; i < str1.size(); ++i) {
    occurs[str1[i]].push_back(i);
  }
  std::array<size_t, kSymbolsInByte> inds;

  // Unbounded window_size
  size_t window_size = std::numeric_limits<size_t>::max();
  size_t lcs_len = GetApproximateLcs(str2, occurs, inds, window_size);

  // window_size = degrees of 2
  size_t str_max_len = std::max(str1.size(), str2.size());
  size_t str_len = str_max_len / 2;
  window_size = 2;
  while (str_len > 0) {
    str_len >>= 1;
    window_size <<= 1;
    size_t res = GetApproximateLcs(str2, occurs, inds, window_size);
    lcs_len = std::max(lcs_len, res);
  }
  return 100.0 * (double(lcs_len) / str_max_len);
}

std::string GetFileContent(const char* filename) {
  std::FILE* file = std::fopen(filename, "rb");

  if (file == nullptr) {
    std::perror("Unable to open file.");
    exit(1);
  }

  std::fseek(file, 0, SEEK_END);
  auto file_size = std::ftell(file);
  char* cdata = new char[file_size + 1];
  cdata[file_size] = '\0';

  // TODO: handle errors
  std::fseek(file, 0, SEEK_SET);
  std::fread(cdata, 1, file_size, file);

  std::string res(cdata);

  delete[] cdata;

  return res;
}

std::vector<fs::path> GetDirPaths(const fs::path& dir) {
  std::vector<fs::path> res;
  for (const auto& dir_entry : std::filesystem::directory_iterator(dir)) {
    res.push_back(dir_entry.path());
  }
  return res;
}

void Equal(const fs::path& dir1, const fs::path& dir2) {
  std::vector<fs::path> paths_vec1 = GetDirPaths(dir1);
  std::vector<fs::path> paths_vec2 = GetDirPaths(dir2);

  for (const auto& path1 : paths_vec1) {
    std::string data1 = GetFileContent(path1.c_str());
    for (const auto& path2 : paths_vec2) {
      std::string data2 = GetFileContent(path2.c_str());
      if (data1 == data2) {
        std::cout << path1.c_str() << " - " << path2.c_str() << '\n';
      }
    }
  }
}

void Similar(const fs::path& dir1, const fs::path& dir2, double required_coef) {
  std::vector<fs::path> paths_vec1 = GetDirPaths(dir1);
  std::vector<fs::path> paths_vec2 = GetDirPaths(dir2);

  // Make the greatest common subsequence.
  for (const auto& path1 : paths_vec1) {
    std::string data1 = GetFileContent(path1.c_str());
    for (const auto& path2 : paths_vec2) {
      std::string data2 = GetFileContent(path2.c_str());
      double eq_coef = std::max(GetDifference(data1, data2),
                                GetDifference(data2, data1));
      if (eq_coef > required_coef) {
        std::cout << path1.c_str() << " - " << path2.c_str() << " - "
                  << std::setprecision(2) << std::fixed << eq_coef << '\n';
      }
    }
  }
}

void Unique(const fs::path& dir1, const fs::path& dir2, double required_coef) {
  std::vector<fs::path> paths_vec1 = GetDirPaths(dir1);
  std::vector<fs::path> paths_vec2 = GetDirPaths(dir2);

  // Make the greatest common subsequence.
  for (const auto& path1 : paths_vec1) {
    std::string data1 = GetFileContent(path1.c_str());
    bool file_exists = false;
    for (const auto& path2 : paths_vec2) {
      std::string data2 = GetFileContent(path2.c_str());
      double eq_coef = std::max(GetDifference(data1, data2),
                                GetDifference(data2, data1));
      if (eq_coef > required_coef) {
        file_exists = true;
        break;
      }
    }
    if (!file_exists) {
      std::cout << path1.c_str() << '\n';
    }
  }
}

void ValidateInputFolder(const fs::path& dir) {
  if (!fs::exists(dir)) {
    std::cerr << "Path does not exists: " << dir.c_str() << '\n';
    exit(1);
  }
  if (dir.is_relative()) {
    std::cerr << "Path to folder must be absolute: " << dir.c_str() << '\n';
    exit(1);
  }
  if (!fs::is_directory(dir)) {
    std::cerr << "It is not a folder: " << dir.c_str() << '\n';
    exit(1);
  }
}

void ValidateNumberOfArgc(int argc, int correct) {
  if (argc != correct + 1) {
    std::cerr << "Invalid number of arguments. Required " << correct << ", but "
              << (argc - 1)
              << " were provided.";
    exit(1);
  }
}

int main(int argc, char** argv) {
  // Read and validate input.
  if (argc < 4) {
    std::cerr << "Invalid number of arguments. Required at least 3, but "
              << (argc - 1)
              << " were provided.";
    exit(1);
  }

  fs::path dir1(argv[1]);
  ValidateInputFolder(dir1);
  fs::path dir2(argv[2]);
  ValidateInputFolder(dir2);

  std::string option(argv[3]);

  if (option == "--equal") {
    ValidateNumberOfArgc(argc, 3);
    Equal(dir1, dir2);
  } else {
    ValidateNumberOfArgc(argc, 4);
     double coef = std::strtod(argv[4], nullptr);
    if (option == "--similar") {
      Similar(dir1, dir2, coef);
    } else if (option == "--unique1") {
      Unique(dir1, dir2, coef);
    } else if (option == "--unique2") {
      Unique(dir2, dir1, coef); // NOLINT
    } else {
      std::cerr << "Invalid option: " << option << '\n'
                << "Available options:" << '\n'
                << "--equal" << '\n'
                << "--similar" << '\n'
                << "--unique1" << '\n'
                << "--unique2" << '\n';
      exit(1);
    }
  }
}
