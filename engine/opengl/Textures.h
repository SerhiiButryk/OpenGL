#pragma once

#include <cstdint>
#include <string>

/**
* A class which represents a texture in OpenGL
*
* A texture is a bitmap image that is applied to the surface
* of a 3D or 2D object to give it color, detail, and realism.
*/

namespace xengine {

    class Texture
    {
    public:
        explicit Texture(const std::string& filePath);
        ~Texture();

        void bind(uint32_t slot) const;
        void unbind() const;

        static Texture* createTexture(const std::string& texturePath) {
            auto texture = new Texture(texturePath);
            texture->bind(0);
            return texture;
        }

    private:
        uint32_t m_RendererID {};
        std::string m_FilePath;
        int m_Width {}, m_Height {}, m_BytesPerPixel {};
        // A buffer which will contain the pixel data of our texture
        unsigned char* m_LocalBuffer = nullptr;
    };

}
