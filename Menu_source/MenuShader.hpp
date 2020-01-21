#pragma once
#include "main.hpp"

class MenuShader
{
public:
	MenuShader();
	MenuShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	MenuShader(MenuShader const &) = default;
	
	~MenuShader();
public:
	// Идентификатор программы
	GLuint Program;
	// Использование программы
	void Use();
};


