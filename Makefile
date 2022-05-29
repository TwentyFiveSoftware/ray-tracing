all: submodules build_release run

submodules:
	git submodule update --init

build_release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build

run:
	./build/RayTracing
