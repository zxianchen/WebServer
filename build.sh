#!/bin/sh

SOURCE_DIR=`pwd`

if [ ! -d "${SOURCE_DIR}/build" ]; then
  mkdir ${SOURCE_DIR}/build
fi

cd ${SOURCE_DIR}/build
# rm -rf * 
cmake .. && make