cmake_minimum_required(VERSION 3.8)
project(formiga)

set(CMAKE_CXX_STANDARD 17)

#boost
#include_directories("/usr/local/Cellar/boost/1.64.0_1/include/")
#link_directories("/usr/local/Cellar/boost/1.64.0_1/lib/")
include_directories("dependencies/boost")
link_directories("dependencies/boost/stage/lib")

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

set(CMAKE_EXE_LINKER_FLAGS "-O3 -DBOOST_NO_CXX11_SCOPED_ENUMS -lboost_system -lboost_filesystem -lboost_thread-mt -rdynamic -stdlib=libc++")


add_executable(formiga ${SOURCE_FILES})


