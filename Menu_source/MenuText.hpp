#pragma once
#include "main.hpp"
#include "MenuShader.hpp"
struct Character {
	GLuint     TextureID; // ID текстуры глифа
	glm::ivec2 Size;      // Размеры глифа
	glm::ivec2 Bearing;   // Смещение верхней левой точки глифа
	GLuint     Advance;   // Горизонтальное смещение до начала следующего глифа
};

class MenuText
{
public:
	MenuText();
	void terminateFreeType();
	void bindText();
	void unbindText();
	void displayMessage(std::string const &message, Rect rect, glm::vec3 const  &color, float const & scale);
	void loadCharacters();
	MenuText(MenuText const &);
	virtual ~MenuText();

public:
	std::map<GLchar, Character>	Characters;
	MenuShader						shader;
	FT_Face						face;
	FT_Library					ft;
	int 						font_size;
	GLuint						VBO;
	GLuint						VAO;
public:

	int getFontSize() const;

	void setFontSize(int fontSize);
};

