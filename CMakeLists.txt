cmake_minimum_required(VERSION 3.8)
project(formiga)

set(CMAKE_CXX_STANDARD 17)

#boost
#include_directories("/usr/local/Cellar/boost/1.64.0_1/include/")
#link_directories("/usr/local/Cellar/boost/1.64.0_1/lib/")
include_directories("dependencies/boost")
link_directories("dependencies/boost/stage/lib")

find_package(Tcmalloc)
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
    find_package( Boost 1.52 COMPONENTS system thread regex REQUIRED )
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y -pedantic -Wextra")
    find_package( Boost 1.52 COMPONENTS system thread filesystem REQUIRED )
endif()

include_directories( ${Boost_INCLUDE_DIR} )


#dependencies
include_directories(dependencies dependencies/crow/include dependencies/spdlog/include)

include_directories(include)
include_directories(include/app)

# just copy to the build folder.
file(COPY www DESTINATION ".")
file(COPY log DESTINATION ".")

#set(INCLUDE_FILES test_json.cpp)
set(SOURCE_FILES include/app/container.cpp include/app/routes.cpp include/object.hpp)
set(SOURCE_FILES src/main.cpp src/utils.cpp include/utils.hpp src/logger.cpp include/logger.h include/config.hpp)

set(CMAKE_EXE_LINKER_FLAGS "-O3 -lboost_system -lboost_filesystem")

add_executable(formiga ${SOURCE_FILES})

target_link_libraries(formiga ${Boost_LIBRARIES})

#-lboost_thread-mt -rdynamic -stdlib=libc++