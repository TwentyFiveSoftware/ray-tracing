build_release:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build

run: build_release
	./build/RayTracing
