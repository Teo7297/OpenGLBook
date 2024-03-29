#include <ElementBuffer.h>
#include <Renderer.h>

ElementBuffer::ElementBuffer(const unsigned int *data, unsigned int count)
:
    m_Count(count)
{
    
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}
ElementBuffer::~ElementBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void ElementBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}
void ElementBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}