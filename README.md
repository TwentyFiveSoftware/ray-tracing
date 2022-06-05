# Ray Tracing

<img src="https://github.com/TwentyFiveSoftware/ray-tracing-gpu/blob/master/sceneRender.png">

## Overview

This is my take on [Peter Shirley's Ray Tracing in One Weekend](https://github.com/RayTracing/raytracing.github.io) book
series.

The **main** branch contains all the topics covered in the three books. On top of the presented ray tracing code, I
added some enhancements like multi-threading and a window to display the rendering process.

The **benchmark** branch contains an optimized version of the first book, which I use to compare the render time to 
my ray tracing implementations in other languages (see below).


## Build & Run this project

1. Install [CMake](https://cmake.org/download/)
2. Clone the repository
3. Optional: Change sample and thead count in `src/constants.h`
4. Build and run the project
   ```sh
   make
   ```


## Performance

I've already implemented Peter Shirley's ray tracing in various programming languages running on CPU & GPU and compared their performance.

The performance was measured on the same scene (see image above) with the same amount of objects, the same recursive
depth, the same resolution (1920 x 1080). The measured times are averaged over multiple runs.

*Reference system: AMD Ryzen 9 5900X (12 Cores / 24 Threads) | AMD Radeon RX 6800 XT*

|                                                                                                    | 1 sample / pixel | 100 samples / pixel |     10,000 samples / pixel | 
|----------------------------------------------------------------------------------------------------|-----------------:|--------------------:|---------------------------:|
| [Go](https://github.com/TwentyFiveSoftware/go-ray-tracing)                                         |       4,150.0 ms |             428.5 s |  ~ 11.9 h _(extrapolated)_ |
| [C++](https://github.com/TwentyFiveSoftware/ray-tracing)                                           |         685.0 ms |              70.1 s |   ~ 1.9 h _(extrapolated)_ |
| [Rust](https://github.com/TwentyFiveSoftware/rust-ray-tracing)                                     |         640.0 ms |              66.1 s |   ~ 1.8 h _(extrapolated)_ |
| [C](https://github.com/TwentyFiveSoftware/c-ray-tracing)                                           |         329.0 ms |              32.8 s |   ~ 0.9 h _(extrapolated)_ |
| [GPU - Compute Shader](https://github.com/TwentyFiveSoftware/ray-tracing-gpu)                      |          21.5 ms |               2.1 s |                    215.0 s |
| [GPU - Vulkan Ray Tracing extension](https://github.com/TwentyFiveSoftware/ray-tracing-gpu-vulkan) |           1.2 ms |               0.1 s |                     12.5 s |
