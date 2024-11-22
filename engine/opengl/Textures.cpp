#include "Textures.h"

/* Glew provides OpenGL APIs */
#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STB_IMAGE/stb_image.h>

#include <common/Log.h>

namespace xengine {

Textures::Textures(const std::string& filePath): m_FilePath(filePath) {
    logInfo("Textures::Textures() File path: '{}'", filePath);
    // Load our image
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(filePath.c_str(), &m_Width,
        &m_Height, &m_BytesPerPixel, 4 /* equals to RGBA or 4 channels*/);

    // Gen texture name
    glGenTextures(1, &m_RendererID);
    // Bind our texture
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Set configs for our texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Load the texture into OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, m_LocalBuffer);
    // Unbind our texture
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_LocalBuffer) {
        stbi_image_free(m_LocalBuffer);
    }
}

Textures::~Textures() {
    // Delete the texture from GPU
    glDeleteTextures(1, &m_RendererID);
}

void Textures::bind(uint32_t slot) const {
    // Bind to a specific slot
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Textures::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
