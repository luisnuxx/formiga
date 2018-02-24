#!/usr/bin/env bash
CURRENT_DIR=`pwd`
DEPS_DIR=${CURRENT_DIR}/dependencies

CROW_DIR="crow"
SPDLOG_DIR="spdlog"
BOOST_DIR="boost"


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

#BOOST
# (this MIGHT work for Linux and MacOS :D )
# https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz
# READ:: http://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html
if [ ! -d ${BOOST_DIR} ]; then
    wget https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.gz -O boost_install.tgz
    tar -zxf boost_install.tgz
    rm -f boost_install.tgz
    ln -s boost_1_66_0/ ${BOOST_DIR}

    #build boost
    cd ${BOOST_DIR}
    ./bootstrap.sh
    ./b2 --build-dir=/tmp/build-boost toolset=gcc stage
fi

#return to the initial place.
cd ${CURRENT_DIR}


