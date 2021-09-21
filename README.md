# Ray Tracing

<img src="https://github.com/TwentyFiveSoftware/ray-tracing/blob/master/sceneRender.png">

## Overview

This is my take on [Peter Shirley's Ray Tracing in One Weekend](https://github.com/RayTracing/raytracing.github.io) book
series.

This repository contains all the topics covered in the three books. On top of the presented ray tracing code, I added
some enhancements like multi-threading and a window to display the rendering process.

## My Ray Tracing series

This is the first part of my 3 project series. After this ray tracing implementation using the CPU to render the image,
I created another one using the [Vulkan API](https://vulkan.org/) to dispatch a compute shader on the GPU to render the
image. The third version is the continuation of the second one, but using the
dedicated [Vulkan Ray Tracing](https://www.khronos.org/blog/vulkan-ray-tracing-final-specification-release) extension
instead of a compute shader, to speed up the rendering process even further. The extension allows accessing the
dedicated [Ray Accelerators](https://www.amd.com/de/technologies/rdna-2) in the new AMD RDNA 2 GPUs or the
dedicated [RT Cores](https://www.nvidia.com/en-us/design-visualization/technologies/turing-architecture/) in NVIDIA's
RTX graphics cards. The performance differences are compared below.

- [CPU Ray Tracing](https://github.com/TwentyFiveSoftware/ray-tracing)
- [GPU Ray Tracing (Compute Shader)](https://github.com/TwentyFiveSoftware/ray-tracing-gpu)
- [GPU Ray Tracing (Vulkan Ray Tracing extension)](https://github.com/TwentyFiveSoftware/ray-tracing-gpu-vulkan)

## Performance

The performance was measured on the same scene (see image above) with the same amount of objects, the same recursive
depth, the same resolution (1920 x 1080). The measured times are averaged over multiple runs.

*Reference system: AMD Ryzen 9 5900X (12 Cores / 24 Threads) | AMD Radeon RX 6800 XT*

| | [CPU Ray Tracing](https://github.com/TwentyFiveSoftware/ray-tracing) | [GPU Ray Tracing (Compute Shader)](https://github.com/TwentyFiveSoftware/ray-tracing-gpu) | [GPU Ray Tracing (Vulkan RT extension)](https://github.com/TwentyFiveSoftware/ray-tracing-gpu-vulkan) |
| --- | --- | --- | --- |
| 1 sample / pixel | ~ 18.000 ms | 21.5 ms | 1.25 ms |
| 10,000 samples / pixel | ~ 50 h (extrapolated) | 215 s | 12.5 s |
