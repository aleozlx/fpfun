.PHONY: clean all

all: build/intro

clean:
	rm -rf build

build/intro: intro.cpp
	mkdir -pv build
	g++ -std=c++14 -O2 -o $@ $<
	objdump -d -M intel $@ > build/intro.hex
