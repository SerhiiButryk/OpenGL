#include "Cube.h"

namespace xengine {

    Cube::Cube() {
        updateBuffer();
    }

    void Cube::updateBuffer() {

        //     // Position         // Color           // Texture Coords
        //    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // 0
        //     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // 1
        //     0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, // 2
        //    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, // 3
        //    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f, // 4
        //     0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, // 5
        //     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // 6
        //    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f  // 7

        // Default texture coordinates
        glm::vec2 t1 = {0.0f, 0.0f};
        glm::vec2 t2 = {1.0f, 0.0f};
        glm::vec2 t3 = {1.0f, 1.0f};
        glm::vec2 t4 = {0.0f, 1.0f};
        glm::vec2 t5 = {0.0f, 0.0f};
        glm::vec2 t6 = {1.0f, 0.0f};
        glm::vec2 t7 = {1.0f, 1.0f};
        glm::vec2 t8 = {0.0f, 1.0f};

        glm::vec2 textureCoords[] = { t1, t2, t3, t4, t5, t6, t7, t8 };

        // Default coordinates
        glm::vec3 c1 = {-0.5f, -0.5f, -0.5f};
        glm::vec3 c2 = {0.5f, -0.5f, -0.5f};
        glm::vec3 c3 = {0.5f,  0.5f, -0.5f};
        glm::vec3 c4 = {-0.5f,  0.5f, -0.5f};
        glm::vec3 c5 = {-0.5f, -0.5f,  0.5f};
        glm::vec3 c6 = {0.5f, -0.5f,  0.5f};
        glm::vec3 c7 = {0.5f,  0.5f,  0.5f};
        glm::vec3 c8 = {-0.5f,  0.5f,  0.5f};

        glm::vec3 coords[] = { c1, c2, c3, c4, c5, c6, c7, c8 };

        // Default color
        glm::vec4 col1 = {-0.5f, -0.5f, -0.5f, 1.0f};
        glm::vec4 col2 = {0.5f, -0.5f, -0.5f, 1.0f};
        glm::vec4 col3 = {0.5f,  0.5f, -0.5f, 1.0f};
        glm::vec4 col4 = {-0.5f,  0.5f, -0.5f, 1.0f};
        glm::vec4 col5 = {-0.5f, -0.5f,  0.5f, 1.0f};
        glm::vec4 col6 = {0.5f, -0.5f,  0.5f, 1.0f};
        glm::vec4 col7 = {0.5f,  0.5f,  0.5f, 1.0f};
        glm::vec4 col8 = {-0.5f,  0.5f,  0.5f, 1.0f};

        glm::vec4 colors[] = { col1, col2, col3, col4, col5, col6, col7, col8 };

        for (int i = 0; i < getVertexCount(); i++) {
            m_dataBuffer[i] = { coords[i], colors[i], textureCoords[i], -1 };
        }

    }

    void Cube::setIndicies(uint32_t *indices, uint32_t maxSize) {
        // Back face
        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 2;
        indices[3] = 2;
        indices[4] = 3;
        indices[5] = 0;

        // Front face
        indices[6] = 4;
        indices[7] = 5;
        indices[8] = 6;
        indices[9] = 6;
        indices[10] = 7;
        indices[11] = 4;

        // Left face
        indices[12] = 0;
        indices[13] = 4;
        indices[14] = 7;
        indices[15] = 7;
        indices[16] = 3;
        indices[17] = 0;

        // Right face
        indices[18] = 1;
        indices[19] = 5;
        indices[20] = 6;
        indices[21] = 6;
        indices[22] = 2;
        indices[23] = 1;

        // Bottom face
        indices[24] = 0;
        indices[25] = 1;
        indices[26] = 5;
        indices[27] = 5;
        indices[28] = 4;
        indices[29] = 0;

        // Top face
        indices[30] = 3;
        indices[31] = 2;
        indices[32] = 6;
        indices[33] = 6;
        indices[34] = 7;
        indices[35] = 3;
    }
}
