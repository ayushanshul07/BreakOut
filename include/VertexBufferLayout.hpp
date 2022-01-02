//
//  VertexBufferLayout.h
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <vector>

#include "VertexBufferElement.hpp"

class VertexBufferLayout{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout();
    
    void Push(unsigned int type, unsigned int count);
    
    inline const std::vector<VertexBufferElement> GetElements() const{ return m_Elements;}
    inline unsigned int GetStride() const{ return m_Stride;}
};

#endif /* VertexBufferLayout_h */
