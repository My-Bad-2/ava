ARCH := x86_64

all:
	CC=clang CXX=clang++ cmake -B build -S . -DAva_ARCHITECTURE=$(ARCH)