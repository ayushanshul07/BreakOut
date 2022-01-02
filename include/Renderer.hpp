//
//  Renderer.hpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <GL/glew.h>

#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"


#define ASSERT(x)   if(!(x)) __builtin_trap();
#define GlCall(x)   GlClearError();\
                    x;\
                    ASSERT(GlLogCall(#x,__FILE__,__LINE__))

void GlClearError();

bool GlLogCall(const char* function, const char* file, int line);

class Renderer{
    
private:
public:
    void Clear() const;
    void Draw(const VertexArray&, const IndexBuffer& ib, const Shader& shader) const;
    
};

#endif /* Renderer_hpp */
