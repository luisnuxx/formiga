cmake_minimum_required(VERSION 3.0.0)

project(formiga)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCE_DIR src)

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
    find_package( Boost 1.52 COMPONENTS system filesystem thread REQUIRED )
endif()

include_directories( ${Boost_INCLUDE_DIR} )

set(PROJECT_INCLUDE_DIR
        ${PROJECT_SOURCE_DIR}/include
        )

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")


#dependencies
include_directories(include dependencies dependencies/crow/include dependencies/spdlog/include)


# just copy to the build folder.
file(COPY www DESTINATION ".")
file(COPY log DESTINATION ".")

#set(INCLUDE_FILES test_json.cpp)

file(GLOB
        SOURCE_FILES
        src/*.cpp
        include/*.h
        include/*.hpp)


#set(SOURCE_FILES include/app/container.cpp include/app/routes.cpp include/object.hpp)set(SOURCE_FILES src/main.cpp src/utils.cpp include/utils.hpp src/logger.cpp include/logger.h include/config.hpp)

#set(CMAKE_EXE_LINKER_FLAGS "-O3 -lboost_system -lboost_thread -lboost_filesystem")

#add_executable(formiga ${SOURCE_FILES})
add_executable(formiga ${SOURCE_FILES})
target_link_libraries(formiga ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


#-lboost_thread-mt -rdynamic -stdlib=libc++