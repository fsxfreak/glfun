#include "Primitive.hpp"

Primitive::Primitive() 
    : program()
{}

void Primitive::setProgram(const std::string& vertex, const std::string& fragment)
{
    program = Program(vertex, fragment);
}