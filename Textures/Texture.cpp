#include "Texture.h"
#include <iostream>

Texture::Texture(const char* loc)
{

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::cout << 1 << "\n";

    int width, height, nChannels;

    unsigned char *data = stbi_load(loc, &width, &height, &nChannels, 0);
    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << 2 << "\n";

    }
    else std::cout << "Failed to create texture!" << "\n";

    std::cout << 3 << "\n";

    stbi_image_free(data);

    std::cout << 4 << "\n";

}

Texture::~Texture()
{

    glDeleteTextures(1, &textureID);

}

void Texture::Bind()
{

    glBindTexture(GL_TEXTURE_2D, textureID);

}

void Texture::Unbind()
{

    glBindTexture(GL_TEXTURE_2D, 0);

}