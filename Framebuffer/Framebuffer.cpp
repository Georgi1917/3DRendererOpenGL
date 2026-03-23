#include "Framebuffer.h"

static bool CheckFramebufferStatus()
{
    return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

Framebuffer::Framebuffer(int width, int height)
{

    glGenFramebuffers(1, &framebufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);

    glGenTextures(1, &pickingTexId);
    glBindTexture(GL_TEXTURE_2D, pickingTexId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexId, 0);

    glGenRenderbuffers(1, &renderBuffId);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffId);

    f_width = width; f_height = height;

    if (!CheckFramebufferStatus()) std::cout << "Framebuffer incomplete!" << "\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

Framebuffer::~Framebuffer()
{

    glDeleteFramebuffers(1, &framebufferId);
    glDeleteTextures(1, &pickingTexId);
    glDeleteRenderbuffers(1, &renderBuffId);

}

void Framebuffer::Bind()
{

    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);

}

void Framebuffer::Unbind()
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Framebuffer::ResizeFramebuffer(int width, int height)
{

    glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);

    glBindTexture(GL_TEXTURE_2D, pickingTexId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

    f_width = width; f_height = height;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


