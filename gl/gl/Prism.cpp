#include "Prism.hpp"
#include <iostream>

Prism::Prism(const glm::vec3& b // unshortened variable names in .hpp
           , const float s
           , const float h
           , const glm::vec3& color)
{
    using glm::vec3;

    vec3 v1{b};
    vec3 v2{ b.x, b.y, b.z + s };
    vec3 v3{ b.x + s, b.y, b.z + s };
    vec3 v4{ b.x + s, b.y, b.z };
    
    vec3 v5{ v4 };
    vec3 v6{ v3 };
    vec3 v7{ v2 };
    vec3 v8{ v1 };

    v5.y += h;
    v6.y += h;
    v7.y += h;
    v8.y += h;

    vec3 sideColor1{ color }; sideColor1 *= 0.8f;
    vec3 sideColor2{ color }; sideColor2 *= 0.6f;
    vec3 baseColor { color };  baseColor *= 0.2f;

    sides[BASE] = std::make_unique<Rectangle>(v1, v2, v3, v4, baseColor);
    sides[LEFT] = std::make_unique<Rectangle>(v1, v4, v5, v8, sideColor1);
    sides[FRONT] = std::make_unique<Rectangle>(v4, v3, v6, v5, sideColor2);
    sides[RIGHT] = std::make_unique<Rectangle>(v3, v2, v7, v6, sideColor1);
    sides[BACK] = std::make_unique<Rectangle>(v2, v1, v8, v7, sideColor2);
    sides[TOP] = std::make_unique<Rectangle>(v5, v6, v7, v8, color);
}

void Prism::draw(glm::mat4 view) const
{
    for (auto &e : sides)
    {
        e->draw(view);
    }
}

void Prism::setColor(glm::vec3 rgb, unsigned int index)
{
    if (index >= Indices::NUM_SIDES) return;
    
    sides[index]->setColor(rgb, 0);
    sides[index]->setColor(rgb, 1);
    sides[index]->setColor(rgb, 2);
    sides[index]->setColor(rgb, 3);
}

void Prism::setPosition(glm::vec3 pos, unsigned int index)
{
    glm::vec3 currentPos = sides[BASE]->getPosition(0);
    translate(pos - currentPos);
}

void Prism::translate(const glm::vec3& amount)
{
    for (auto &e : sides)
    {
        e->translate(amount);
    }
}

void Prism::transform(const glm::mat4& amount)
{
    for (auto &e : sides)
    {
        e->transform(amount);
    }
}

glm::vec3 Prism::getColor(unsigned int index) const
{
    return sides[index]->getColor(0);
}

glm::vec3 Prism::getPosition(unsigned int index) const
{  
    return sides[index]->getPosition(0);
}
