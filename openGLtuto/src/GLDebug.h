#ifndef _GLDebug_
#define _GLDebug_

#include <iostream>
#include <GL/glew.h>

/////////////////////////////////////ERROR HANDLING///////////////////////////////////////

#define ASSERT(x) if(!(x)) __debugbreak(); //this macro only works for vs compiler
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{

	if (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << std::hex << error << ")"
			<< std::dec << function << " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////
#endif // !_GLDebug_
