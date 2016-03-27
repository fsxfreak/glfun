#ifndef STATE_HPP
#define STATE_HPP

#include "Camera.hpp"
#include "InputManager.hpp"
#include "Primitive.hpp"

#include <memory>
#include <random>
#include <vector>

class State
{
public:
    State(InputManager* input);

    static const glm::vec3 UP;

    void constructScene();
    void drawScene(double delta);
    void animate(double delta);
private:
    std::vector<std::shared_ptr<Entity>> entities;

    template <class T, size_t ROWS, size_t COLS>
    using Grid = std::array<std::array<T, COLS>, ROWS>;
    Grid<float, 8, 4> grid;

    static std::random_device rd;

    Camera camera;
};

#endif