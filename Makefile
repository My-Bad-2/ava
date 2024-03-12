ARCH := x86_64

all:
	@rm -rf build
	$(info Building the project for system architecture $(ARCH))
	@CC=clang CXX=clang++ cmake -B build -S . -DAva_ARCHITECTURE=$(ARCH)
	@make -C build

update-git-submodules:
	@git submodule update --recursive

init-git-submodules:
	@git submodule update --init --recursive

qemu-run-uefi:
	@make -C build qemu-run-uefi

help:
	@make -C build help

clean:
	@make -C build clean