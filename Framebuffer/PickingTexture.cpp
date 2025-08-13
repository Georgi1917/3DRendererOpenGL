#include "PickingTexture.h"

PickingTexture::PickingTexture()
{

    glGenTextures(1, &rendererId);
    glBindTexture(GL_TEXTURE_2D, rendererId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rendererId, 0);

}

PickingTexture::~PickingTexture()
{

    glDeleteTextures(1, &rendererId);

}

void PickingTexture::Bind()
{

    glBindTexture(GL_TEXTURE_2D, rendererId);

}

void PickingTexture::Unbind()
{

    glBindTexture(GL_TEXTURE_2D, 0);

}