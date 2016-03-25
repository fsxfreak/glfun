#include "State.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"

#include <cmath>

const glm::vec3 State::UP = glm::vec3(0.0f, 1.0f, 0.0f);

State::State(InputManager* input) : camera(input)
{
    constructScene();
}

void State::constructScene()
{
    std::shared_ptr<Triangle> tri = std::make_shared<Triangle>(Triangle(
        {
            { glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }
            , { 0.0f, 0.0f, 0.0f }
        })
    );
    primitives.push_back(tri);
    tri = std::make_shared<Triangle>(Triangle(
        {
            { glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f) }
            , { 0.0f, 0.0f, 0.0f }
        })
    );

    std::array<glm::vec3, 4> rectangleVertices = { {
            glm::vec3(-1.0f, -1.0f, 0.0f)
          , glm::vec3(1.0f, -1.0f, 0.0f)
          , glm::vec3(1.0f, 1.0f, 0.0f)
          , glm::vec3(-1.0f, 1.0f, 0.0f)
        } };
    std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(Rectangle({
        {{ 
            glm::vec3(-1.0f, -1.0f, 0.0f)
          , glm::vec3(1.0f, -1.0f, 0.0f)
          , glm::vec3(1.0f, 1.0f, 0.0f)
          , glm::vec3(-1.0f, 1.0f, 0.0f) 
        }}
      , { 1.0f, 1.0f, 1.0f }
    }));
    primitives.push_back(tri);
}

void State::drawScene(double delta)
{
    camera.update(delta);

    for (auto &e : primitives)
    {
        GLfloat blue = static_cast<float>(sin(glfwGetTime() + 3.1415f / 2)) / 2 + 0.5f;
        GLfloat green = static_cast<float>(sin(glfwGetTime())) / 2 + 0.5f;
        GLfloat red = static_cast<float>(sin(glfwGetTime() - 3.1415f / 2)) / 2 + 0.5f;
        e->setColor({ 0.1f, 0.2f, blue }, 0);
        e->setColor({ 0.2f, green, 0.1f }, 1);
        e->setColor({ red, 0.1f, 0.2f }, 2); 

        e->draw(camera.getView());
    }
}