#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Primitive.hpp"
#include "Program.hpp"

#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Triangle : public Primitive
{
public:
	static const unsigned int NUM_VERTS = 3;
	static const int STRIDE = 6;
	static const int SIZE = STRIDE * NUM_VERTS;

	Triangle(const std::array<Vector3, NUM_VERTS>& pos, Vector3 rgb);
	Triangle(const std::array<Vector3, NUM_VERTS>& pos, const std::array<Vector3, NUM_VERTS>& rgb);

	virtual void draw();

	void setColor(Vector3 rgb, unsigned int index);
	void setPosition(Vector3 pos, unsigned int index);
	Vector3 getColor(unsigned int index) const;
	Vector3 getPosition(unsigned int index) const;
private:
	GLfloat vertData[SIZE];

};

#endif
