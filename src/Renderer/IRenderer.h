#ifndef IRENDERER_H
#define IRENDERER_H

#include "glad/glad.h"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

namespace amc
{
	// Purpose: Renderer interface 
	class IRenderer
	{
	protected:
		virtual void Init() = 0;
		virtual void RenderLoop() = 0;
	};
}

#endif