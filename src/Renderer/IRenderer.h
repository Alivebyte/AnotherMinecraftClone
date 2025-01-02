#ifndef IRENDERER_H
#define IRENDERER_H

#include "glad/glad.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Shader.hpp>


// Renderer interface 

class IRenderer
{
	virtual void Init() = 0;
	virtual void RenderLoop() = 0;
};

#endif