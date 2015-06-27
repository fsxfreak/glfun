#include "Triangle.hpp"

#include <iostream>

Triangle::Triangle(const std::array<Vector3, NUM_VERTS>& pos, Vector3 rgb)
	: Triangle(pos, { rgb, rgb, rgb })
{

}

Triangle::Triangle(const std::array<Vector3, NUM_VERTS>& pos, const std::array<Vector3, NUM_VERTS>& rgb)
	: Primitive()
{
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
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE * sizeof(float), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, STRIDE * sizeof(float), (GLvoid*)(3 * sizeof(GLfloat)));
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

void Triangle::setColor(Vector3 rgb, unsigned int index)
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

void Triangle::setPosition(Vector3 pos, unsigned int index)
{
	if (index > NUM_VERTS) return;

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

Vector3 Triangle::getColor(unsigned int index) const
{
	if (index > NUM_VERTS) return{ 0.0f, 0.0f, 0.0f };
	
	return {
		vertData[STRIDE * index + 3],
		vertData[STRIDE * index + 4],
		vertData[STRIDE * index + 5]
	};
}

Vector3 Triangle::getPosition(unsigned int index) const
{
	if (index > NUM_VERTS) return{ 0.0f, 0.0f, 0.0f };

	return{
		vertData[STRIDE * index + 0],
		vertData[STRIDE * index + 1],
		vertData[STRIDE * index + 2]
	};
}