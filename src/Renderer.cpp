#include <Renderer.h>
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout
            << "[OpenGL Error] ("
            << error
            << "): "
            << function
            << " "
            << file
            << ":"
            << line
            << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const ElementBuffer& ib, const Shader& shader) const
{
    shader.Bind();  // This bind might be redundant, we should implement a caching system
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

    //! Unbinding is just a waste of resources !
}