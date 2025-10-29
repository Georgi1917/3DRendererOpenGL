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

    int width, height, nChannels;

    unsigned char *data = stbi_load(loc, &width, &height, &nChannels, 0);
    stbi_set_flip_vertically_on_load(true);

    if (data)
    {

        std::cout << nChannels << "\n";
        
        if (nChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

    }
    else std::cout << "Failed to create texture!" << "\n";

    stbi_image_free(data);

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