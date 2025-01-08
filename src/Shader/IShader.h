#ifndef ISHADER_H
#define ISHADER_H
#include <string>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
// Purpose: Basic shader interface that represents the shader description

namespace amc
{
	enum ShaderType
	{
		FRAGMENT = GL_FRAGMENT_SHADER,
		VERTEX = GL_VERTEX_SHADER,
	};

	class IShader
	{
	protected:
		virtual void LoadFromFile(std::string vertex, std::string fragment) = 0;
		virtual int CompileShader(ShaderType type, const char* source) = 0;
		virtual std::string GetSource(ShaderType type) = 0;
		virtual void Use() = 0;
		virtual void DeleteProgram() = 0;
		virtual void UniformBool(const char* name, bool value) = 0;
		virtual void UniformFloat(const char* name, float value) = 0;
		virtual void UniformInt(const char* name, int value) = 0;
		virtual void UniformVector4f(const char* name, float x, float y, float z, float w) = 0;
		virtual void UniformVector4f(const char* name, glm::vec4 &vec) = 0;
		//virtual void UniformVector3x4f(const char* name, float x, float y, float z, float w) = 0;
		virtual void UniformMatrix4f(const char* name, glm::mat4 &mat) = 0;
		virtual ~IShader() {};
	};
}

#endif