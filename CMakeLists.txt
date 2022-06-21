cmake_minimum_required(VERSION 3.22)

project(Liepa VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

include(FetchContent)

FetchContent_Declare(googletest
                     GIT_REPOSITORY    https://github.com/google/googletest.git
                     GIT_TAG           release-1.11.0
                     )


FetchContent_MakeAvailable(googletest)

function(add)
    set(prefix          ARG)
    set(no_values       TEST)
    set(single_values   TARGET)
    set(multi_values    SOURCES LIBS FLAGS)

    cmake_parse_arguments(${prefix}
                          "${no_values}"
                          "${single_values}"
                          "${multi_values}"
                          ${ARGN}
                          )

    if(ARG_TEST)
        add_executable(${ARG_TARGET} Tests/${ARG_TARGET}.cpp ${ARG_SOURCES})

        add_test(NAME       ${ARG_TARGET}
                 COMMAND    ${ARG_TARGET}
                 )
    else()
        add_executable(${ARG_TARGET} Source/${ARG_TARGET}.cpp ${ARG_SOURCES})
    endif()

    foreach(LIB "${ARG_LIBS}")
        target_link_libraries(${ARG_TARGET} PRIVATE ${LIB})
    endforeach()
endfunction()

add(TARGET Liepa 
    FLAGS -Wall
    LIBS glfw GL
    SOURCES Source/Window.cpp   
    )

add(TEST TARGET Globals_test LIBS gtest_main)
add(TEST TARGET Delegate_test LIBS gtest_main)