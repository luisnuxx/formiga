cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)
set(CATCH2_PATH ${CMAKE_SOURCE_DIR}/test/test_catch2/thirdparty/catch2)

message(STATUS "CATCH2_PATH:: DUMP :: " ${CATCH2_PATH})

#############################################################################
# Catch library with the main function to speed up build
#############################################################################

include_directories(${CATCH2_PATH}) #catch - for unit testing

add_library(catch_main OBJECT "src/unit.cpp")

target_include_directories(catch_main PRIVATE ${CATCH2_PATH})

if (MSVC)
    set(Boost_USE_STATIC_LIBS "On)")
    find_package( Boost 1.54 COMPONENTS system filesystem iostreams regex thread REQUIRED )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -pedantic -Wextra")
    find_package( Boost 1.54 COMPONENTS system filesystem iostreams regex thread REQUIRED )
endif()

include_directories( ${Boost_INCLUDE_DIR} )
file(COPY ../../config DESTINATION ".")

#############################################################################
# one executable for each unit test file
#############################################################################

file(GLOB files "src/unit-*.cpp")
foreach(file ${files})
    get_filename_component(file_basename ${file} NAME_WE)
    string(REGEX REPLACE "unit-([^$]+)" "test-\\1" testcase ${file_basename})

    add_executable(${testcase} $<TARGET_OBJECTS:catch_main> ${file} )

    target_include_directories(${testcase} PRIVATE ${CATCH2_PATH})

    target_link_libraries(${testcase} ${OBJECT} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    if(NOT MSVC)
        set_target_properties(${testcase} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-float-equal")
    endif()

    #add_test(NAME "${testcase}_default"
    #        COMMAND ${testcase} ${CATCH_TEST_FILTER}
    #        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    #        )
    #set_tests_properties("${testcase}_default" PROPERTIES LABELS "default")

    add_test(NAME "${testcase}_all"
            COMMAND ${testcase} ${CATCH_TEST_FILTER} "*"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            )
    set_tests_properties("${testcase}_all" PROPERTIES LABELS "all")


endforeach()
#print_all_variables()