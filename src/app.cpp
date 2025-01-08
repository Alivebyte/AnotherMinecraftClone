#include "app.h"
#include <iostream>
using namespace amc;

App::App()
{
	m_ContextSettings.majorVersion = 2;
	m_ContextSettings.minorVersion = 1;
}


void App::Run()
{

	InitRender();

	while (m_Window.isOpen())
	{
		Render();

		m_Window.display();

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

		//Render();
		
	}
}


void App::InitRender()
{
	/*// Basic shader 
	const char* vertexSource = R"glsl(
		#version 120

		attribute vec3 position;

		void main()
		{
			gl_Position = vec4(position, 1.0);
		}
	)glsl";

	const char* fragSource = R"glsl(
		#version 120


		void main()
		{
			gl_FragColor = vec4(0.2, 0.9, 0.1, 1.0);
		}
	)glsl";*/

	//Shader basic;
	basic.LoadFromFile("content/shaders/basic.vert", "content/shaders/basic.frag");

	basic.Use();

	float verts[] =
	{
		  0.5f,  0.5f, 0.0f,  // top right
		  0.5f, -0.5f, 0.0f,  // bottom right
		  -0.5f, -0.5f, 0.0f,  // bottom left
		  -0.5f,  0.5f, 0.0f   // top left
	};

	unsigned int indices[] =
	{
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	// Test draw

	// Generate Vertex Buffer Object(VBO)
	// Generate vertex array object
	//GLuint VBO, EBO, VAO;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glBindVertexArray(m_VAO);
	// Bind VBO to the Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);


	// Push vertex data do Array Buffer using Static Draw
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Add vertex array attribute to the position in the shader
	GLint posAttrib = glGetAttribLocation(basic.GetProgram(), "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Enable vertex attribute
	glEnableVertexAttribArray(posAttrib);
	//glUseProgram(shaderProgram);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);

	

}
void App::Render()
{
	glClearColor(0.1f, 0.5f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::vec3 pos(0.0f, 0.0f, -2.0f);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 1000.0f);

	basic.UniformMatrix4f("model", model);
	basic.UniformMatrix4f("view", view);
	basic.UniformMatrix4f("projection", projection);
	basic.Use();


	glBindVertexArray(m_VAO);

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

bool App::Init()
{
	sf::Context context;

	if (!gladLoadGLLoader((GLADloadproc)context.getFunction))//GetAnyGLFuncAddress))
	{
		std::cout << "GLAD did not initialize" << std::endl;	

		return false;
	}

	return true;
}


bool App::Construct(unsigned int width, unsigned int height, const char* title)
{
	if (!Init())
	{
		std::cout << "[" << __FUNCTION__ << "]: Couldn't init!" << std::endl;
		return false;
	}
	
	m_Window.create(VideoMode(width, height),title, sf::Style::Default, m_ContextSettings);

	

	return true;
}

