//
//  VertexBuffer.hpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include <cstddef>

class VertexBuffer{
private:
    unsigned int m_RendererId;
public:
    VertexBuffer(const void* data, size_t size);
    ~VertexBuffer();
    
    void Bind() const;
    void UnBind() const;
};


#endif /* VertexBuffer_hpp */
