#!/usr/bin/env bash
CURRENT_DIR=`pwd`
DEPS_DIR=${CURRENT_DIR}/dependencies
USE_BOOST="no"
CROW_DIR="crow"
SPDLOG_DIR="spdlog"
BOOST_DIR="boost"
JSON_DIR="json"
TOOLSET="clang" # possible [gcc,clang]

while getopts b: option
do
case "${option}" in
b) USE_BOOST=${OPTARG};;
esac
done

echo "IF BOOST IS REQUIRED ::  use ::  -b yes "
echo "USE BOOST :: ${USE_BOOST}"

if [ ! -d ${DEPS_DIR} ]; then
    mkdir -p ${DEPS_DIR}
fi

cd ${DEPS_DIR}

## CROW
if [ ! -d ${CROW_DIR} ]; then
  git clone https://github.com/ipkn/crow.git ${CROW_DIR}
else
  cd ${CROW_DIR}
  git stash
  git pull
  cd ${DEPS_DIR}
fi

## SPDLOG
if [ ! -d ${SPDLOG_DIR} ]; then
    git clone https://github.com/gabime/spdlog.git ${SPDLOG_DIR}
else
  cd ${SPDLOG_DIR}
  git stash
  git pull
  cd ${DEPS_DIR}
fi


## JSON
if [ ! -d ${JSON_DIR} ]; then
    git clone https://github.com/nlohmann/json.git ${JSON_DIR}
else
  cd ${JSON_DIR}
  git stash
  git pull
  cd ${DEPS_DIR}
fi

#BOOST
# (this MIGHT work for Linux and MacOS :D )
# https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz
# READ:: http://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html

if [ "${USE_BOOST}" == "yes" ]; then
    echo "CHECKING IF BOOST IS REQUIRED"
    if [ ! -d ${BOOST_DIR} ]; then
        # wget https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.gz -O boost_install.tgz
        wget https://sourceforge.net/projects/boost/files/boost/1.69.0/boost_1_69_0.tar.gz/download -O boost_install.tgz
        tar -zxf boost_install.tgz
        rm -f boost_install.tgz
        ln -s boost_1_69_0/ ${BOOST_DIR}

        #build boost
        cd ${BOOST_DIR}
        ./bootstrap.sh --prefix=/tmp/build-boost
        ./b2 --build-dir=/tmp/build-boost toolset=${TOOLSET} stage
    fi
fi

#return to the initial place.
cd ${CURRENT_DIR}


