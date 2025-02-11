#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "Shader.h"
#include "../glad/glad.h"
#include "../stb/stb_image.h"

class Texture {
  public:
    unsigned int ID;
    GLenum type;

    // Constructor for the Texture.
    Texture(const char *image, GLenum textureType, GLenum slot, GLenum format,
            GLenum pixelType);

    // Assigns a texture unit to a texture.
    void textureUnit(Shader &shader, const char *uniform, unsigned int unit);

    // Binds a texture.
    void Bind();

    // Unbinds a texture.
    void Unbind();

    // Deletes a texture.
    void Delete();
};

#endif
