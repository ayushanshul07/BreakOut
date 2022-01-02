//
//  VertexBufferLayout.cpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"


VertexBufferLayout::VertexBufferLayout(): m_Stride(0){};

void VertexBufferLayout::Push(unsigned int type, unsigned int count){
    m_Elements.push_back({type, count, GL_FALSE});
    m_Stride += count*VertexBufferElement::GetSizeOfType(type);
}


