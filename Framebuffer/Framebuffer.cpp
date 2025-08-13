#include "Framebuffer.h"
#include <iostream>

Framebuffer::Framebuffer()
{

    glGenFramebuffers(1, &rendererId);
    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);

}

Framebuffer::~Framebuffer()
{

    glDeleteFramebuffers(1, &rendererId);

}

void Framebuffer::Bind()
{

    glBindFramebuffer(GL_FRAMEBUFFER, rendererId);

}   

void Framebuffer::Unbind()
{

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Framebuffer::CheckStatus()
{

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "Framebuffer incomplete!" << "\n";

}