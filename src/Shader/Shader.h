#ifndef SHADER_H
#define SHADER_H
#include "IShader.h"
namespace amc
{
	// Shader class defining the shaders

	
	class Shader : public IShader
	{
	public:
		Shader();
		Shader(std::string vertex, std::string fragment);
		void LoadFromFile(std::string vertex, std::string fragment) override;
		int CompileShader(ShaderType type, const char* source) override;
		std::string GetSource(ShaderType type) override;
		unsigned int GetProgram() { return m_iShaderProgram; };
		void Use() override;
		void DeleteProgram() override;
		void UniformVector4f(const char* name, float x, float y, float z, float w) override;
		void UniformBool(const char* name, bool value) override;
		void UniformFloat(const char* name, float value) override;
		void UniformInt(const char* name, int value) override;
		void UniformVector4f(const char* name, glm::vec4& vec) override;
		//virtual void UniformVector3x4f(const char* name, float x, float y, float z, float w) = 0;
		void UniformMatrix4f(const char* name, glm::mat4& mat) override;
		~Shader();

	private:
		std::string m_sVertexSource;
		std::string m_sFragmentSource;

		unsigned int m_iVertexShader;
		unsigned int m_iFragmentShader;
		
		unsigned int m_iShaderProgram;
	};
}
#endif // !SHADER_H
