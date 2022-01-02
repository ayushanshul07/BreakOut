//
//  IndexBuffer.hpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

class IndexBuffer{
private:
    unsigned int m_RendererId;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();
    
    void Bind() const;
    void UnBind() const;
    
    inline unsigned int GetCount() const{ return m_Count;}
};


#endif /* IndexBuffer_hpp */
