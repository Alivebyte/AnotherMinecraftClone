#include "app.h"
using namespace amc;

App::App()
{

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

	// Test draw

	Shader basic;

	basic.loadFromFile();

	glBegin(GL_TRIANGLES);
	//glColor3f(0.5f, 0.0f, 0.6f);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, -0.5f);
	glEnd();
}

bool App::Construct(unsigned int width, unsigned int height, const char* title)
{
	m_Window.create(VideoMode(width, height),title);

	return true;
}

