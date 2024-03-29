#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <Renderer.h>

VertexArray::VertexArray()
	: m_VerticesNumber(0)
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();     // bind va
    vb.Bind();  // bind buffer

    // set the layout
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), reinterpret_cast<const void*>(offset)));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

    m_VerticesNumber = vb.GetBufferSize() / layout.GetElements().size();
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

unsigned int VertexArray::GetVerticesNumber() const
{
    return m_VerticesNumber;
}
