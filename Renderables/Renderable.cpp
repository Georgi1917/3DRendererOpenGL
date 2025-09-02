#include "Renderable.h"

unsigned int Renderable::staticId = 1;
glm::vec3 Renderable::staticTranslation = glm::vec3(0.0f, 0.0f, 0.0f);

Renderable::Renderable()
{

    id = staticId;
    staticId++;

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    pickingColor = IdToColor();

    model = glm::mat4(1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);

    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

Renderable::Renderable(Texture *t) : tex(t)
{

    id = staticId;
    staticId++;

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    pickingColor = IdToColor();

    model = glm::mat4(1.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);

    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

Renderable::Renderable(glm::vec3 _color) : color(_color) 
{
  
    id = staticId;
    staticId++;

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    pickingColor = IdToColor();

    model = glm::mat4(1.0f);
    translation = staticTranslation;
    staticTranslation.x += 2.0f;
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);

    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

Renderable::Renderable(glm::vec3 _color, Texture *t) : color(_color), tex(t) 
{
  
    id = staticId;
    staticId++;

    lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    pickingColor = IdToColor();

    model = glm::mat4(1.0f);
    translation = staticTranslation;
    staticTranslation.x += 2.0f;
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

void Renderable::ResetModelMatrix()
{

    model = glm::mat4(1.0f);
    model = glm::translate(model, translation);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);

}

glm::vec3& Renderable::GetTranslation()
{

    return translation;

}

glm::vec3& Renderable::GetRotation()
{

    return rotation;

}

glm::vec3& Renderable::GetScale()
{

    return scale;

}

void Renderable::SetTranslation(glm::vec3 worldRay)
{

    translation = worldRay;

}

glm::vec3& Renderable::GetLightColor()
{

    return lightColor;

}

void Renderable::Draw()
{

    

}

Texture *Renderable::GetTexture()
{

    return tex;

}

void Renderable::RemoveTexture()
{

    tex = nullptr;

}
