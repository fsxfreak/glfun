#include "Triangle.hpp"
#include "Engine.hpp"

Triangle::Triangle(const std::array<glm::vec3, NUM_VERTS>& pos, glm::vec3 rgb)
    : Triangle(pos, std::array<glm::vec3, 3>({ rgb, rgb, rgb }))
{

}

Triangle::Triangle(const std::array<glm::vec3, NUM_VERTS>& pos, const std::array<glm::vec3, NUM_VERTS>& rgb)
    : Primitive(NUM_VERTS, STRIDE, SIZE)
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
            glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * vertData.size(), vertData.data(), GL_STATIC_DRAW);

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
    glm::mat4 projection;
    projection = glm::perspective(60.0f, static_cast<float>(Engine::width) / Engine::height, 0.1f, 100.0f);

    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));

    program.use();
    glBindVertexArray(vaoID);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Triangle::translate(const glm::vec3& amount)
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
