clear
CLANG_PATH="$HOME/Development/tools/clang/bin/clang++"
OUTPUT_FILE="bin/main"

[ -d bin ] || mkdir bin
[ -d logs ] || mkdir logs

${CLANG_PATH}  -std=c++14 \
-O3 -lboost_system -lboost_thread-mt -stdlib=libc++  \
-I./include/ \
-I./include/app/ \
-I/usr/local/Cellar/boost/1.64.0_1/include/ \
-I./include/spdlog/include/ \
-L/usr/local/Cellar/boost/1.64.0_1/lib/ \
-L./include/app/ \
-L./include/ \
main.cpp \
-o ${OUTPUT_FILE}

if [ $? -eq 0 ]
then
    echo "Compiled successfuly. Run:: ${OUTPUT_FILE}"
    #./main
else
  echo "Found error compiling"
fi

#./hello
#-I/usr/local/Cellar/boost/1.63.0/include/ \
#-L/usr/local/Cellar/boost/1.63.0/lib/ \
