//
//  VertexBuffer.cpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#include "VertexBuffer.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, size_t size){
    GlCall(glGenBuffers(1, &m_RendererId));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
    GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
};

VertexBuffer::~VertexBuffer(){
    GlCall(glDeleteBuffers(1, &m_RendererId));
};

void VertexBuffer::Bind() const{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
};

void VertexBuffer::UnBind() const{
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
};
