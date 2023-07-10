#include <Renderer.h>
#include <iostream>
#ifndef __gl_h_
#include <glad/glad.h>
#endif

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {
    }
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
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const ElementBuffer& ib, const Shader& shader) const
{
    shader.Bind();  // This bind might be redundant, we should implement a caching system
    va.Bind();
    ib.Bind();

    if (ib.GetCount() > 0)
    {
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
    else
    {
        GLCall(glDrawArrays(GL_TRIANGLES, 0, va.GetVerticesNumber()));
    }
    //! Unbinding is just a waste of resources !
}

void Renderer::SetBackgroundColor(const Color& color)
{
    auto [r, g, b] = color;
    glClearColor(r, g, b, 1.0f);
}
