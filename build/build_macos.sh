## MACOS
OUT_FOLDER=/Users/luisnuxx/Development/C++/formiga/build/out
BASE_PATH=/Users/luisnuxx/Development/C++/formiga

V8_BASE_PATH=${BASE_PATH}/dependencies/libv8
V8_INC_PATH=${V8_BASE_PATH}/include
V8_LIB_PATH=${V8_BASE_PATH}/lib

CROW_INC_PATH=${BASE_PATH}/dependencies/crow/include
JSON_INC_PATH=${BASE_PATH}/dependencies/json/include
SPDLOG_INC_PATH=${BASE_PATH}/dependencies/spdlog/include
BOOST_INC_PATH=${BASE_PATH}/dependencies/boost
BOOST_LIB_PATH=${BOOST_INC_PATH}/stage/lib

if [ ! -d ${OUT_FOLDER} ] 
then
    mkdir -p ${OUT_FOLDER}
    mkdir -p ${OUT_FOLDER}/log
    mkdir -p ${OUT_FOLDER}/v8
    cp -r deps/* ${OUT_FOLDER}
    cp ${V8_BASE_PATH}/natives_blob.bin ${V8_BASE_PATH}/snapshot_blob.bin ${V8_BASE_PATH}/icudtl.dat ${OUT_FOLDER}/v8
fi

clang++ -c -static -std=c++14 -Wall -I ${BASE_PATH}/include -I ${BASE_PATH}/dependencies/spdlog/include ${BASE_PATH}/src/logger.cpp -o ${OUT_FOLDER}/logger.o
clang++ -c -static -std=c++14 -Wall -I ${BASE_PATH}/include  ${BASE_PATH}/src/utils.cpp -o ${OUT_FOLDER}/utils.o
clang++ -c -static -std=c++14 -Wall -I ${BASE_PATH}/include -I${V8_INC_PATH} ${BASE_PATH}/src/v8_engine.cpp -o ${OUT_FOLDER}/v8_engine.o
clang++ -c -static -std=c++14 -Wall -I ${BASE_PATH}/include -I${V8_INC_PATH} -I${CROW_INC_PATH} -I${JSON_INC_PATH} -I${SPDLOG_INC_PATH} ${BASE_PATH}/src/main.cpp -o ${OUT_FOLDER}/main.o

clang++ -std=c++14 -Wall -L${BOOST_LIB_PATH} -lboost_system -lboost_filesystem -lpthread \
    ${BOOST_LIB_PATH}/libboost_system.a ${BOOST_LIB_PATH}/libboost_iostreams.a \
    ${BOOST_LIB_PATH}/libboost_thread.a ${BOOST_LIB_PATH}/libboost_filesystem.a \
    ${V8_LIB_PATH}/*.a -L. -I. \
    ${OUT_FOLDER}/logger.o ${OUT_FOLDER}/utils.o ${OUT_FOLDER}/v8_engine.o ${OUT_FOLDER}/main.o -o ${OUT_FOLDER}/formiga

#if [[ ! -f /usr/local/lib/natives_blob.bin || ! -f /usr/local/lib/snapshot_blob.bin ]]; then
#    cp ${V8_LIB_PATH}/natives_blob.bin ${V8_LIB_PATH}/snapshot_blob.bin ${V8_LIB_PATH}/icudtl.dat ${OUT_FOLDER}/v8
#fi

#V8_INC_PATH=${HOME}/Development/C++/V8/v8/include
#V8_LIB_PATH=${HOME}/Development/C++/V8/v8/out/x64.release
