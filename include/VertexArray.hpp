//
//  VertexArray.hpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#ifndef VertexArray_hpp
#define VertexArray_hpp

#include "VertexBuffer.hpp"
class VertexBufferLayout;

class VertexArray{
private:
    unsigned int m_RendererId;
public:
    VertexArray();
    ~VertexArray();
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    
    void Bind() const;
    void UnBind() const;
};

#endif /* VertexArray_hpp */
