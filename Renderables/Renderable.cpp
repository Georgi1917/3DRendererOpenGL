#include "Renderable.h"

Renderable::Renderable(unsigned int _id, glm::vec3 _color) : id(_id), color(_color) 
{

    pickingColor = IdToColor();

}

glm::vec3 Renderable::IdToColor()
{

    return glm::vec3(
        (id & 0x000000FF) / 255.0f,
        ((id & 0x0000FF00) >> 8) / 255.0f,
        ((id & 0x00FF0000) >> 16) / 255.0f
    );

}

unsigned int Renderable::ColorToId(unsigned char r, unsigned char g, unsigned char b)
{

    return r + (g << 8) + (b << 16);

}

bool Renderable::CompareColorAndId(unsigned char r, unsigned char g, unsigned char b)
{

    unsigned int idToBeCompared = ColorToId(r, g, b);

    if (idToBeCompared == id) return true;
    else return false;

}

glm::vec3& Renderable::GetColor()
{

    return color;

}

glm::vec3& Renderable::GetPickingColor()
{

    return pickingColor;

}
