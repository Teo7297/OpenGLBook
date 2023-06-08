#pragma once

class VertexBuffer
{
private:
    // openGL uses ids for every object.
    // we will use this in the same way openGL does (??)
    unsigned int m_RendererID;
    unsigned int m_BufferSize;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    unsigned int GetBufferSize() const;
};