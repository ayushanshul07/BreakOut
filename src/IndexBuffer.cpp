//
//  IndexBuffer.cpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#include "IndexBuffer.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):m_Count(count){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GlCall(glGenBuffers(1, &m_RendererId));
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW));
};

IndexBuffer::~IndexBuffer(){
    GlCall(glDeleteBuffers(1, &m_RendererId));
};

void IndexBuffer::Bind() const{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
};

void IndexBuffer::UnBind() const{
    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};
