#include "app.h"
#include <iostream>
using namespace amc;

App::App()
{

}

typedef void(*amcProc) (void);

static PROC amcGetProcAddress(LPCSTR procname)
{
	return wglGetProcAddress(procname);
}


void App::Run()
{
	while (m_Window.isOpen())
	{
		Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				m_Window.close();
			}

			if (event.type == Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}

		Render();

		m_Window.display();
	}
}

void App::Render()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float verts[] =
	{
		-1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	// Test draw

	// Generate Vertex Buffer Object(VBO)
	GLuint VBO;
	glGenBuffers(1, &VBO);
	
	// Bind VBO to the Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Push vertex data do Array Buffer using Static Draw
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	

	// Basic shader 
	const char* vertexSource = R"glsl(
		#version 150 core

		in vec2 position;

		void main()
		{
			glPosition = vec4(position, 1.0);
		}
	)glsl";

	const char* fragSource = R"glsl(
		#version 150 core

		out vec4 outColor;

		void main()
		{
			outColor = vec4(0.5, 0.0, 0.6, 1.0);
		}
	)glsl";

	// Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	// Compile vertex shader
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
	}


	// Create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		char buffer[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
	}

	// Create shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader); // Attaching vertex shader
	glAttachShader(shaderProgram, fragmentShader); // Attaching fragment shader

	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	// Delete the shaders as we do not require them anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Add vertex array attribute to the position in the shader
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable vertex attribute
	glEnableVertexAttribArray(posAttrib);

	// Generate vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

bool App::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)amcGetProcAddress))
	{
		std::cout << "GLAD did not initialize" << std::endl;
		return false;
	}

	return true;
}


bool App::Construct(unsigned int width, unsigned int height, const char* title)
{
	m_Window.create(VideoMode(width, height),title);

	if (Init())
		return true;

	return false;
}

