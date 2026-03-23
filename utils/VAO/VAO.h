#pragma once
#include <glad/glad.h>

class VAO {
public:
	unsigned int ID;

	VAO();

	void Bind();
	void Unbind();
	void Delete();
};