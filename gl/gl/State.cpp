#include "State.hpp"
#include "Triangle.hpp"
#include "Rectangle.hpp"
#include "Prism.hpp"

#include <array>
#include <cmath>
#include <iostream>

const glm::vec3 State::UP = glm::vec3(0.0f, 1.0f, 0.0f);
std::random_device State::rd{};

State::State(InputManager* input) : camera(input)
{
    constructScene();
}

void State::constructScene()
{
    std::mt19937 gen(rd());
    std::exponential_distribution<float> dist(1.5);
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            grid[i][j] = dist(gen);
        }
    }

    using glm::vec3;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            double r = std::generate_canonical<double, 10>(gen);
            double g = std::generate_canonical<double, 10>(gen);
            double b = std::generate_canonical<double, 10>(gen);
            vec3 color = { r, g, b };

            entities.emplace_back(std::make_shared<Prism>(vec3{ i, 0.0f, j }, 0.8f, grid[i][j], color));
        }
    }
}

void State::drawScene(double delta)
{
    camera.update(delta);
    animate(delta);

    for (auto &e : entities)
    {
        e->draw(camera.getView());
    }
}

void State::animate(double delta)
{
    for (int i = 0; i < entities.size(); i++)
    {
        auto &e = entities[i];

        e->transform(glm::translate(glm::mat4(), glm::vec3{ 0, 0.0005 * glm::sin(glfwGetTime() + i), 0 }));
    }
}