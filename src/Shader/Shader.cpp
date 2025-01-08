#include "glad/glad.h"
#include "IShader.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace amc
{
	Shader::Shader() : m_sFragmentSource(""), m_sVertexSource(""), m_iShaderProgram(0), m_iVertexShader(0), m_iFragmentShader(0)
	{

	}

	Shader::~Shader()
	{
		
	}

	Shader::Shader(std::string vertex, std::string fragment)
	{
		LoadFromFile(vertex, fragment);
	}

	void Shader::LoadFromFile(std::string vertex, std::string fragment)
	{
		std::ifstream vertexFileStream(vertex, std::ios::in);
		std::ifstream fragmentFileStream(fragment, std::ios::in);

		std::stringstream vertexSourceStream;
		std::stringstream fragmentSourceStream;

		if (vertexFileStream.is_open())
		{
			std::string line;

			while (std::getline(vertexFileStream, line))
			{
				vertexSourceStream << line << std::endl;
			}
		}
		else
		{
			std::cout << "[" << __FUNCTION__ << "] Couldn't open vertex shader!";
			return;
		}

		if (fragmentFileStream.is_open())
		{
			std::string line;

			while (std::getline(fragmentFileStream, line))
			{
				fragmentSourceStream << line << std::endl;
			}
		}
		else
		{
			std::cout << "[" << __FUNCTION__ << "] Couldn't open fragment shader";
			return;
		}

		
		m_sVertexSource = vertexSourceStream.str();
		m_sFragmentSource = fragmentSourceStream.str();
		

		vertexFileStream.close();
		fragmentFileStream.close();

		const char* vertexSource = m_sVertexSource.c_str();
		const char* fragmentSource = m_sFragmentSource.c_str();

		// Create vertex shader
		if (CompileShader(VERTEX, vertexSource) == GL_FALSE)
		{
			char buffer[512];
			glGetShaderInfoLog(m_iVertexShader, 512, NULL, buffer);
			std::cout << "[" << __FUNCTION__ << "]: Vertex Shader Error: " << buffer;
		}

		// Create fragment shader
		if (CompileShader(FRAGMENT, fragmentSource) == GL_FALSE)
		{
			char buffer[512];
			glGetShaderInfoLog(m_iFragmentShader, 512, NULL, buffer);
			std::cout << "[" << __FUNCTION__ << "]: Fragment Shader Error: " << buffer;
		}

		// Create shader program
		m_iShaderProgram = glCreateProgram();
		glAttachShader(m_iShaderProgram, m_iVertexShader); // Attaching vertex shader
		glAttachShader(m_iShaderProgram, m_iFragmentShader); // Attaching fragment shader

		glLinkProgram(m_iShaderProgram);

		glDeleteShader(m_iVertexShader);
		glDeleteShader(m_iFragmentShader);

	}

	int Shader::CompileShader(ShaderType type, const char* source)
	{
		
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, NULL);

		// Compile vertex shader
		glCompileShader(shader);

		switch (type)
		{
		case FRAGMENT:
			m_iFragmentShader = shader;
			break;
		case VERTEX:
			m_iVertexShader = shader;
			break;
		}

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		return status;
	}

	void Shader::Use()
	{
		glUseProgram(m_iShaderProgram);
	}

	std::string Shader::GetSource(ShaderType type)
	{
		return (type == VERTEX ? m_sVertexSource : m_sFragmentSource);
	}

	void Shader::DeleteProgram()
	{
		glDeleteProgram(m_iShaderProgram);
	}

	void Shader::UniformBool(const char* name, bool value)
	{
		glUniform1i(glGetUniformLocation(m_iShaderProgram, name), (int)value);
	}

	void Shader::UniformInt(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(m_iShaderProgram, name), value);
	}

	void Shader::UniformFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(m_iShaderProgram, name), value);
	}

	void Shader::UniformVector4f(const char* name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(m_iShaderProgram, name), x,y,z,w);
	}

	void Shader::UniformVector4f(const char* name, glm::vec4 &vec)
	{
		glUniform4f(glGetUniformLocation(m_iShaderProgram, name), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::UniformMatrix4f(const char* name, glm::mat4& mat)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_iShaderProgram, name), 1, GL_FALSE, glm::value_ptr(mat));
	}
}

