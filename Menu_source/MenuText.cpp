#include "MenuText.hpp"

MenuText::MenuText()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader = MenuShader("../shaders/vertex_shader_text", "../shaders/fragment_shader_text");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1024), 0.0f, static_cast<GLfloat>(768));
	shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	if (FT_New_Face(ft, "../fonts/game_font.TTF", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	font_size = 48;
	FT_Set_Pixel_Sizes(face, 0, font_size);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	loadCharacters();
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	unbindText();
}

void MenuText::loadCharacters()
{
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(GLuint)face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

MenuText::~MenuText()
{
	terminateFreeType();
}

void MenuText::bindText()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	shader.Use();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
}

void MenuText::unbindText()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void MenuText::displayMessage(std::string const &message, Rect rect, glm::vec3 const &color, float const & scale)
{
	bindText();
	glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	
	// Iterate through all characters
	std::string::const_iterator c;
	for (c = message.begin(); c != message.end(); c++)
	{
		Character ch = Characters[*c];
		
		GLfloat xpos = rect.x0 + ch.Bearing.x * scale;
		GLfloat ypos = rect.y0 - (ch.Size.y - ch.Bearing.y) * scale;
		
		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		rect.x0 += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	unbindText();
}

void MenuText::terminateFreeType()
{
	for (auto elem : Characters)
	{
		glDeleteTextures(1, &elem.second.TextureID);
	}
	glDisable(GL_BLEND);
}

int MenuText::getFontSize() const
{
	return font_size;
}

void MenuText::setFontSize(int fontSize)
{
	font_size = fontSize;
	FT_Set_Pixel_Sizes(face, 0, font_size);
}
