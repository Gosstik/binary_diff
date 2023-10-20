# COLOR can be passed as additional argument.
function(project_log MESSAGE)
    if(${ARGC} EQUAL 2)
        set(COLOR ${ARGV1})
        message_color_mode("[${PROJECT_NAME}] ${MESSAGE}" ${COLOR} STATUS)
    else()
        message(STATUS "[${PROJECT_NAME}] ${MESSAGE}")
    endif()
endfunction()

macro(project_warning MESSAGE)
    message(WARNING "[${PROJECT_NAME}] ${MESSAGE}")
endmacro()

# --------------------------------------------------------------------
