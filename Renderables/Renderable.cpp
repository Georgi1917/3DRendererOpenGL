#include "Renderable.h"

Renderable::Renderable(unsigned int _id, glm::vec3 _color) : id(_id), color(_color) 
{

    pickingColor = IdToColor();

    model = glm::mat4(1.0f);
    translation = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);

    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

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

glm::mat4& Renderable::GetModelMatrix()
{

    return model;

}

std::string Renderable::GetClassName()
{

    return "Renderable";

}
