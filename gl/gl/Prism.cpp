#include "Prism.hpp"
#include <iostream>

Prism::Prism(const glm::vec3& b // unshortened variable names in .hpp
           , const float s
           , const float h
           , const glm::vec3& color)
{
    glm::vec3 v1{b};
    glm::vec3 v2{ b.x, b.y, b.z + s };
    glm::vec3 v3{ b.x + s, b.y, b.z + s };
    glm::vec3 v4{ b.x + s, b.y, b.z };
    glm::vec3 v5{ v4 };
    glm::vec3 v6{ v3 };
    glm::vec3 v7{ v2 };
    glm::vec3 v8{ v1 };
    v5.y += h;
    v6.y += h;
    v7.y += h;
    v8.y += h;

    sides[BASE] = std::make_unique<Rectangle>(v1, v2, v3, v4, color);
    sides[LEFT] = std::make_unique<Rectangle>(v1, v4, v5, v8, color);
    sides[FRONT] = std::make_unique<Rectangle>(v4, v3, v6, v5, color);
    sides[RIGHT] = std::make_unique<Rectangle>(v3, v2, v7, v6, color);
    sides[BACK] = std::make_unique<Rectangle>(v2, v1, v8, v7, color);
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
