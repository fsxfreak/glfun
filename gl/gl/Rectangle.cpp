#include "Rectangle.hpp"
#include "Engine.hpp"
#include <iostream>

Rectangle::Rectangle(const glm::vec3& p1
                   , const glm::vec3& p2
                   , const glm::vec3& p3
                   , const glm::vec3& p4, const glm::vec3& rgb = { 1.0f, 1.0f, 1.0f })
    : Rectangle({ p1, p2, p3, p4 }, rgb)
{
}

Rectangle::Rectangle(const std::array<glm::vec3, NUM_VERTS>& pos, glm::vec3 rgb)
    : Primitive(NUM_VERTS, STRIDE, SIZE)
{
    for (unsigned int i = 0; i < pos.size(); i++)
    {
        vertData[STRIDE * i] = pos[i].x;
        vertData[STRIDE * i + 1] = pos[i].y;
        vertData[STRIDE * i + 2] = pos[i].z;

        vertData[STRIDE * i + 3] = rgb.x;
        vertData[STRIDE * i + 4] = rgb.y;
        vertData[STRIDE * i + 5] = rgb.z;
    }
    indices = { 0, 1, 2, 2, 3, 0 };

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertData.size(), vertData.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, STRIDE * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    modelUniform = glGetUniformLocation(program.getID(), "model");
    viewUniform = glGetUniformLocation(program.getID(), "view");
    projectionUniform = glGetUniformLocation(program.getID(), "projection");
}

Rectangle::~Rectangle()
{
    glDeleteBuffers(1, &eboID);
    glDeleteBuffers(1, &vboID);
    glDeleteVertexArrays(1, &vaoID);
}

void Rectangle::draw(glm::mat4 view) const
{
    glm::mat4 projection;
    projection = glm::perspective(60.0f, static_cast<float>(Engine::width) / Engine::height, 0.1f, 100.0f);

    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

    program.use();
    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Rectangle::translate(const glm::vec3& amount)
{
    for (int i = 0; i < NUM_VERTS; i++)
    {
        glm::vec3 offsetPosition{
            vertData[STRIDE * i + 0] + amount.x
          , vertData[STRIDE * i + 1] + amount.y
          , vertData[STRIDE * i + 2] + amount.z
        };
        setPosition(offsetPosition, i);
    }
}