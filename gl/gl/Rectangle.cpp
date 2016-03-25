#include "Rectangle.hpp"

Rectangle::Rectangle(const std::array<glm::vec3, NUM_VERTS>& pos, glm::vec3 rgb)
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

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferData(GL_ARRAY_BUFFER, vertData.size(), vertData.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, STRIDE * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);


    // bottom left, bottom right, top right, top left.
    std::array<unsigned int, 6> indices = { 0, 1, 3, 3, 1, 2 };

    // indices for drawing 6 vertices from 4.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Rectangle::~Rectangle()
{
    glDeleteBuffers(1, &eboID);
    glDeleteBuffers(1, &vboID);
    glDeleteVertexArrays(1, &vaoID);
}

void Rectangle::draw(glm::mat4 view) const
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Rectangle::setColor(glm::vec3 rgb, unsigned int index)
{
    if (index > NUM_VERTS) return;

    vertData[STRIDE * index + 3] = rgb.x;
    vertData[STRIDE * index + 4] = rgb.y;
    vertData[STRIDE * index + 5] = rgb.z;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER
        , sizeof(GLfloat) * (STRIDE * index + 3)
        , sizeof(GLfloat) * 3
        , &vertData[STRIDE * index + 3]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Rectangle::setPosition(glm::vec3 pos, unsigned int index)
{
    if (index >= NUM_VERTS) return;

    glm::vec3 aboutVertex { vertData[STRIDE * index]
                          , vertData[STRIDE * index + 1]
                          , vertData[STRIDE * index + 2] };
    glm::vec3 offset = pos - aboutVertex;

    for (int i = 0; i < NUM_VERTS; i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferSubData(GL_ARRAY_BUFFER
            , sizeof(GLfloat) * (STRIDE * index + 0)
            , sizeof(GLfloat) * 3
            , &vertData[STRIDE * index + 0]
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

glm::vec3 Rectangle::getColor(unsigned int index) const
{
    if (index > NUM_VERTS) { return glm::vec3(); }

    return {
        vertData[index * STRIDE + 3],
        vertData[index * STRIDE + 4],
        vertData[index * STRIDE + 5]
    };
}

glm::vec3 Rectangle::getPosition(unsigned int index) const
{
    if (index > NUM_VERTS) { return glm::vec3(); }

    return{
        vertData[index * STRIDE + 0],
        vertData[index * STRIDE + 1],
        vertData[index * STRIDE + 2]
    };
}
