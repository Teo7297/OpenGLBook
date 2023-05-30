#pragma once

class ElementBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;

public:
    ElementBuffer(const unsigned int* data, unsigned int count); // data > 32 bit index, sometimes its better to go 16
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};