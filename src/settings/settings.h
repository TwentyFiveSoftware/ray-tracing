#pragma once

struct Settings {
    constexpr static const float ASPECT_RATIO = 16.0f / 9.0f;

    static const uint16_t WIDTH = 1000;
    static const uint16_t HEIGHT = static_cast<uint16_t>(WIDTH / ASPECT_RATIO);

    static const uint16_t FPS = 100;
    static const uint16_t RENDER_THREAD_COUNT = 4;

    static const uint16_t SAMPLES_PER_PIXEL = 4;
};
