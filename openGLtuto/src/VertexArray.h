#ifndef _VERTEXARRAY_
#define _VERTEXARRAY_

#include "GLDebug.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public: 
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};

#endif // !_VERTEXARRAY_
