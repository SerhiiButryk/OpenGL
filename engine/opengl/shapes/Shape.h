#pragma once

namespace xengine {

    struct Point {
        float x;
        float y;
    };

    // Update the layout if you add/modify this vertex
    struct Vertex {
        float positions[2];
        float color[4];
        float textureCoord[2];
        float textureId[1];
    };

// Number of floats we have for an element
#define VERTEX_ELEMENT_SIZE_FLOAT(ELEM) (sizeof(ELEM) / 4)
// Size in bytes for N vertices
#define SHAPE_BUFFER_SIZE(VERTEX_COUNT) (sizeof(Vertex) * VERTEX_COUNT)

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
