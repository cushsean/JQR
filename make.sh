#!/bin/bash

if [ -e build ] && [ $1 == 'clean' ]
then
	rm -rf build && \
	mkdir build
fi

cd build && \
cmake ../ && \
make && \
cd ..

if [ ! -e bin ]
then
	ln -s build/bin ./bin
fi
