#include "MenuShader.hpp"

MenuShader::MenuShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	try
	{
		// Открываем файлы
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Считываем данные в потоки
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// Закрываем файлы
		vShaderFile.close();
		fShaderFile.close();
		// Преобразовываем потоки в массив GLchar
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
	GLuint vertexShader, fragmentShader;
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
	glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	Program = glCreateProgram();
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragmentShader);
	glLinkProgram(Program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

MenuShader::~MenuShader()
{}

MenuShader::MenuShader()
{}

void MenuShader::Use()
{
	glUseProgram(this->Program);
}