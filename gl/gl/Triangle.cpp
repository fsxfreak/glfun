#include "Triangle.hpp"
#include "Engine.hpp"

Triangle::Triangle(const std::array<glm::vec3, NUM_VERTS>& pos, glm::vec3 rgb)
    : Triangle(pos, std::array<glm::vec3, 3>({ rgb, rgb, rgb }))
{

}

Triangle::Triangle(const std::array<glm::vec3, NUM_VERTS>& pos, const std::array<glm::vec3, NUM_VERTS>& rgb)
    : Primitive()
{
    for (unsigned int i = 0; i < pos.size(); i++)
    {
        vertData[STRIDE * i]     = pos[i].x;
        vertData[STRIDE * i + 1] = pos[i].y;
        vertData[STRIDE * i + 2] = pos[i].z;

        vertData[STRIDE * i + 3] = rgb[i].x;
        vertData[STRIDE * i + 4] = rgb[i].y;
        vertData[STRIDE * i + 5] = rgb[i].z;
    }

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);

    glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (GLvoid*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, STRIDE * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
    glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    modelUniform = glGetUniformLocation(program.getID(), "model");
    viewUniform = glGetUniformLocation(program.getID(), "view");
    projectionUniform = glGetUniformLocation(program.getID(), "projection");
}

Triangle::~Triangle()
{
    glDeleteBuffers(1, &vboID);
    glDeleteVertexArrays(1, &vaoID);
}

void Triangle::draw(glm::mat4 view) const
{
    glm::mat4 model;
    //model = glm::rotate(model, 45.0f * static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 projection;
    projection = glm::perspective(60.0f, static_cast<float>(Engine::width) / Engine::height, 0.1f, 100.0f);

    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

    program.use();
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Triangle::setColor(glm::vec3 rgb, unsigned int index)
{
    if (index >= NUM_VERTS) return;

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

void Triangle::setPosition(glm::vec3 pos, unsigned int index)
{
    if (index >= NUM_VERTS) return;

    vertData[STRIDE * index + 0] = pos.x;
    vertData[STRIDE * index + 1] = pos.y;
    vertData[STRIDE * index + 2] = pos.z;

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferSubData(GL_ARRAY_BUFFER
        , sizeof(GLfloat) * (STRIDE * index + 0)
        , sizeof(GLfloat) * 3
        , &vertData[STRIDE * index + 0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::vec3 Triangle::getColor(unsigned int index) const
{
    if (index >= NUM_VERTS) return{ 0.0f, 0.0f, 0.0f };
    
    return {
        vertData[STRIDE * index + 3],
        vertData[STRIDE * index + 4],
        vertData[STRIDE * index + 5]
    };
}

glm::vec3 Triangle::getPosition(unsigned int index) const
{
    if (index >= NUM_VERTS) return{ 0.0f, 0.0f, 0.0f };

    return{
        vertData[STRIDE * index + 0],
        vertData[STRIDE * index + 1],
        vertData[STRIDE * index + 2]
    };
}
