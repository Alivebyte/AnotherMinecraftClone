#ifndef APP_H
#define APP_H
#include "Renderer/IRenderer.h"
#include <SFML/Window.hpp>
#include "Shader/Shader.h"



using namespace sf;

namespace amc
{
	class App
	{
	public:
		App();
		~App() {};
		//void CreateContext();
		bool Construct(unsigned int width, unsigned int height, const char* title);
		bool Init();
		void Render();
		void InitRender();
		void Run();
	private:
		Window m_Window;
		ContextSettings m_ContextSettings;
		GLuint m_EBO;
		GLuint m_VBO;
		GLuint m_VAO;
		Shader basic;
	};
}

#endif