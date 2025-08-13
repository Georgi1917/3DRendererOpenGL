#include "Renderbuffer.h"

Renderbuffer::Renderbuffer()
{

    glGenRenderbuffers(1, &rendererId);
    glBindRenderbuffer(GL_RENDERBUFFER, rendererId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1280, 720);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rendererId);

}

Renderbuffer::~Renderbuffer()
{

    glDeleteRenderbuffers(1, &rendererId);

}

void Renderbuffer::Bind()
{

    glBindRenderbuffer(GL_RENDERBUFFER, rendererId);

}

void Renderbuffer::Unbind()
{

    glBindRenderbuffer(GL_RENDERBUFFER, 0);

}