#include "Triangle.hpp"

#include <iostream>

Triangle::Triangle(const std::array<Vector3, 3>& pos, Vector3 rgb)
	: Triangle(pos, { rgb, rgb, rgb })
{

}

Triangle::Triangle(const std::array<Vector3, 3>& pos, const std::array<Vector3, 3>& rgb)
	: Primitive()
{
	const int size = 6 * 3;
	GLfloat vertData[size];
	for (unsigned int i = 0; i < pos.size(); i++)
	{
		vertData[6*i]     = pos[i].x;
		vertData[6*i + 1] = pos[i].y;
		vertData[6*i + 2] = pos[i].z;

		vertData[6*i + 3] = rgb[i].x;
		vertData[6*i + 4] = rgb[i].y;
		vertData[6*i + 5] = rgb[i].z;
	}

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);

	glBindVertexArray(vaoID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertData), vertData, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Triangle::draw()
{
	program.use();
	glBindVertexArray(vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}