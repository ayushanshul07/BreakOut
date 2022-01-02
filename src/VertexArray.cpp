//
//  VertexArray.cpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"

VertexArray::VertexArray(){
    GlCall(glGenVertexArrays(1, &m_RendererId));
};

VertexArray::~VertexArray(){
    GlCall(glDeleteVertexArrays(1,&m_RendererId));
};

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout){
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); ++i){
        const auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (const void*)offset);
        glEnableVertexAttribArray(i);
        offset += VertexBufferElement::GetSizeOfType(element.type) *element.count;
    }
}

void VertexArray::Bind() const{
    GlCall(glBindVertexArray(m_RendererId));
}

void VertexArray::UnBind() const{
    GlCall(glBindVertexArray(0));
}
