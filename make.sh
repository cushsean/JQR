#!/bin/bash

if [ $1 == 'clean' ]
then
	rm -rf build
else
	if [ ! -d build ]
	then
		mkdir build
	fi

	cd build && \
	cmake ../ && \
	make && \
	cd ..

	if [ ! -d bin ] && [ -d build/bin ]
	then
		ln -s build/bin ./bin
	fi
fi
