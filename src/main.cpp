#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image_write.h>
#include <cstdint>

const uint64_t WIDTH = 1920;
const uint64_t HEIGHT = 1080;

int main(int argc, char *argv[]) {
    auto *pixels = new uint8_t[WIDTH * HEIGHT * 3];

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double r = double(x) / WIDTH;
            double g = double(y) / HEIGHT;
            double b = 0.25;

            uint64_t index = (y * WIDTH + x) * 3;
            pixels[index] = static_cast<uint8_t>(r * 0xFF);
            pixels[index + 1] = static_cast<uint8_t>(g * 0xFF);
            pixels[index + 2] = static_cast<uint8_t>(b * 0xFF);
        }
    }

    stbi_write_png("render.png", WIDTH, HEIGHT, 3, pixels, WIDTH * 3);

    delete[] (pixels);
    return 0;
}
