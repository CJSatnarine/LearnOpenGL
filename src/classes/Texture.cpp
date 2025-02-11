#include "Texture.h"
#include "Shader.h"

Texture::Texture(const char *image, GLenum textureType, GLenum slot,
                 GLenum format, GLenum pixelType) {
    type = textureType;

    int imageWidth;
    int imageHeight;
    int numberOfColourChannels;

    // Flips the image so it appears right side up.
    stbi_set_flip_vertically_on_load(true);

    // Reads the image from a file and stores it in bytes.
    unsigned char *bytes =
        stbi_load(image, &imageWidth, &imageHeight, &numberOfColourChannels, 0);

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(textureType, ID);

    // Set the texture wrapping/filtering options.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Assigns the image to the OpenGL Texture object.
    glTexImage2D(textureType, 0, GL_RGBA, imageWidth, imageHeight, 0, format,
                 pixelType, bytes);
    glGenerateMipmap(textureType);

    // Delete the image data because it is already in the OpenGL Texture object.
    stbi_image_free(bytes);

    // Unbinds the OpenGL Texture object so that it can't be modified
    // accidentally.
    glBindTexture(textureType, 0);
}

void Texture::textureUnit(Shader &shader, const char *uniform,
                          unsigned int unit) {
    unsigned int textureUnit = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(textureUnit, unit);
}

void Texture::Bind() { glBindTexture(type, ID); }

void Texture::Unbind() { glBindTexture(type, 0); }

void Texture::Delete() { glDeleteTextures(1, &ID); }
