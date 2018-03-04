cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

#############################################################################
# Catch library with the main function to speed up build
#############################################################################

add_library(doctest_main OBJECT
        "src/unit.cpp"
        )
set_target_properties(doctest_main PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
        COMPILE_DEFINITIONS "$<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>"
        COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/EHsc;$<$<CONFIG:Release>:/Od>>"
        )
target_include_directories(doctest_main PRIVATE "thirdparty/doctest")

# https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake
if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()

    # Disable warning C4389: '==': signed/unsigned mismatch
    # Disable warning C4309: 'static_cast': truncation of constant value
    # Disable warning C4566: character represented by universal-character-name '\uFF01' cannot be represented in the current code page (1252)
    # Disable warning C4996: 'nlohmann::basic_json<std::map,std::vector,std::string,bool,int64_t,uint64_t,double,std::allocator,nlohmann::adl_serializer>::operator <<': was declared deprecated
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4389 /wd4309 /wd4566 /wd4996")
endif()

if (MSVC)
    set(Boost_USE_STATIC_LIBS "On)")
    find_package( Boost 1.54 COMPONENTS system filesystem iostreams regex thread REQUIRED )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1z -pedantic -Wextra")
    find_package( Boost 1.54 COMPONENTS system filesystem iostreams regex thread REQUIRED )
endif()
include_directories( ${Boost_INCLUDE_DIR} )
file(COPY ../config DESTINATION ".")

#############################################################################
# one executable for each unit test_catch2 file
#############################################################################

file(GLOB files "src/unit-*.cpp")
foreach(file ${files})
    get_filename_component(file_basename ${file} NAME_WE)
    string(REGEX REPLACE "unit-([^$]+)" "test-\\1" testcase ${file_basename})

    add_executable(${testcase} $<TARGET_OBJECTS:doctest_main> ${file})
    set_target_properties(${testcase} PROPERTIES
            CXX_STANDARD 11
            CXX_STANDARD_REQUIRED ON
            COMPILE_DEFINITIONS "$<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>"
            COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/EHsc;$<$<CONFIG:Release>:/Od>>"
            )
    target_include_directories(${testcase} PRIVATE "thirdparty/doctest")
    target_link_libraries(${testcase} ${OBJECT} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    if(NOT MSVC)
        set_target_properties(${testcase} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated -Wno-float-equal")
    endif()

    add_test(NAME "${testcase}_default"
            COMMAND ${testcase} ${CATCH_TEST_FILTER}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            )
    set_tests_properties("${testcase}_default" PROPERTIES LABELS "default")

    add_test(NAME "${testcase}_all"
            COMMAND ${testcase} ${CATCH_TEST_FILTER} "*"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            )
    set_tests_properties("${testcase}_all" PROPERTIES LABELS "all")


endforeach()