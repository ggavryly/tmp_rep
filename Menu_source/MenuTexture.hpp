#pragma once
#include "main.hpp"
#include "MenuShader.hpp"

class MenuTexture
{
public:
	MenuTexture(std::string const & path, Rect const &rect);
	MenuTexture();

	MenuTexture(MenuTexture const &);

	void loadTexture(std::string const & path, Rect const &rect);
	void unloadTexture();
	void changePosition(Rect const &);

	void bindTexture();
	void unbindTexture();
	void drawTexture();

	~MenuTexture();
public:
	const Rect &getTextureRect() const;

	void setTextureRect(const Rect &textureRect);

	GLuint getVbo() const;

	GLuint getVao() const;

	GLuint getEbo() const;

private:

	Rect			texture_rect;
	MenuShader			shader;
	int				width;
	int 			height;
	unsigned char*	image;
	GLuint			VBO;
	GLuint			VAO;
	GLuint			EBO;
	GLuint			texture = -1;
public:
	GLuint getTexture() const;
};


