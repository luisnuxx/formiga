cmake_minimum_required(VERSION 2.8.7)
project(formiga_tests)

#Setup CMake to run tests
enable_testing()
set(BINARY_DEST ${CMAKE_SOURCE_DIR}/testBin)

#Prep ourselves for compiling boost
find_package(Boost COMPONENTS system filesystem iostreams unit_test_framework thread  REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

# get all test files and store them in TEST_FILES
file(GLOB TEST_FILES RELATIVE .. test_boost/src/*.cpp)

file(COPY ../../config DESTINATION ${BINARY_DEST})

#Run through each source
foreach(test_file ${TEST_FILES})
    #Extract the filename without an extension (NAME_WE)
    get_filename_component(testName ${test_file} NAME_WE)

    #Add compile target
    add_executable(${testName} ${test_file})

    #link to Boost libraries AND your targets and dependencies
    target_link_libraries(${testName} ${Boost_LIBRARIES} )

    #I like to move testing binaries into a testBin directory
    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${BINARY_DEST})

    #Finally add it to test execution -
    #Notice the WORKING_DIRECTORY and COMMAND
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${BINARY_DEST}
            COMMAND ${BINARY_DEST}/${testName} )

endforeach(test_file)

#${CMAKE_CURRENT_SOURCE_DIR}/