cmake_minimum_required(VERSION 2.8)

project(formiga)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCE_DIR src)

#find_package(Tcmalloc)
find_package(Threads)
find_package(OpenSSL)

if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()


if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (MSVC)
    set(Boost_USE_STATIC_LIBS "On")
    find_package( Boost 1.54 COMPONENTS system thread regex REQUIRED )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1z -pedantic -Wextra")
    find_package( Boost 1.54 COMPONENTS system filesystem iostreams thread REQUIRED )
endif()

include_directories( ${Boost_INCLUDE_DIR} )

set(PROJECT_INCLUDE_DIR include)
#set(V8_LIB lib)


include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

#dependencies
include_directories(dependencies)
include_directories(dependencies/crow/include) #crow
include_directories(dependencies/spdlog/include) #spdlog
include_directories(dependencies/json/single_include) #json

#include_directories(dependencies/libv8/include/) #V8
include_directories(/Users/luisnuxx/Development/C++/V8/v8/include) #V8
include_directories(/Users/luisnuxx/Development/C++/V8/v8/out/x64.release)
include_directories(/Users/luisnuxx/Development/C++/V8/v8/)

set(WL_START_GROUP "-Wl,--start-group")
set(WL_END_GROUP "-Wl,--end-group")

set(V8_PATH "/Users/luisnuxx/Development/C++/V8/v8/")
set(V8_LINK_LIBS
        "${V8_PATH}/out/x64.release/libv8_base.a"
        "${V8_PATH}/out/x64.release/libv8_external_snapshot.a"
        "${V8_PATH}/out/x64.release/libv8_libbase.a"
        "${V8_PATH}/out/x64.release/libv8_libplatform.a"
        "${V8_PATH}/out/x64.release/libv8_libsampler.a"
        "${V8_PATH}/out/x64.release/libicuuc.a"
        "${V8_PATH}/out/x64.release/libicui18n.a"
        "${V8_PATH}/out.gn/x64.release/obj/src/inspector/libinspector.a"
        )

#-Wno-unused-variable

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${V8_LINK_LIBS} -lrt -ldl -pthread")


MESSAGE(STATUS "Compiler Flags: ${CMAKE_CXX_FLAGS}")
MESSAGE(STATUS "V8_LINK_LIBS: ${V8_LINK_LIBS}")
if (CMAKE_DEBUG)
    MESSAGE(STATUS "Linker Libs: ${V8_LINK_LIBS}")
endif()

#include_directories(test_doctest/thirdparty/catch2) #catch - for unit testing

# just copy to the build folder.
file(COPY www DESTINATION ".")
file(COPY www/js DESTINATION ".")
file(COPY log DESTINATION ".")
file(COPY config DESTINATION ".")

#set(INCLUDE_FILES test_json.cpp)

file(GLOB
        SOURCE_FILES
        src/*.cpp
        include/*.h
        include/*.hpp)




##
## TESTS
## create and configure the unit test_catch2 target
##
include(CTest) #adds option BUILD_TESTING (default ON)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test/test_catch2/)
endif()



#set(SOURCE_FILES include/app/container.cpp include/app/routes.cpp include/object.hpp)set(SOURCE_FILES src/main.cpp src/utils.cpp include/utils.hpp src/logger.cpp include/logger.h include/config.hpp)

#set(CMAKE_EXE_LINKER_FLAGS "-O3 -lboost_system -lboost_thread -lboost_filesystem")

#add_executable(formiga ${SOURCE_FILES})
add_executable(formiga ${SOURCE_FILES})

target_link_libraries(formiga
        ${Boost_LIBRARIES}
        ${V8_LINK_LIBS}
        )


#${CMAKE_THREAD_LIBS_INIT}
#-lboost_thread-mt -rdynamic -stdlib=libc++


