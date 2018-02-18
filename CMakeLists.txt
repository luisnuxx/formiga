cmake_minimum_required(VERSION 3.8)
project(formiga)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/Cellar/boost/1.64.0_1/include/")
link_directories("/usr/local/Cellar/boost/1.64.0_1/lib/")

#dependencies
include_directories(dependencies dependencies/crow/ dependencies/spdlog/include)


include_directories(src/include)
include_directories(src/include/app)

# just copy to the build folder.
file(COPY www DESTINATION ".")
file(COPY log DESTINATION ".")

#set(INCLUDE_FILES test_json.cpp)
set(SOURCE_FILES include/app/container.cpp include/app/routes.cpp include/object.hpp)

set(SOURCE_FILES src/main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-O3 -lboost_system -lboost_thread-mt -rdynamic -stdlib=libc++")


add_executable(formiga ${SOURCE_FILES})


