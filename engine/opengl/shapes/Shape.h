#pragma once

namespace xengine {

    struct Point {
        float x;
        float y;
    };

    struct Vertex {
        float positions[2];
        float color[4];
        float textureCoord[2];
        float textureId[1];
    };

    struct Color {
        float r;
        float g;
        float b;
        float alpha;
    };

    struct TextureCoord {
        float coord_1;
        float coord_2;
    };

}
