//
//  Renderer.cpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#include <iostream>
#include "Renderer.hpp"

void GlClearError(){
    while(glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* file, int line){
    while(int error = glGetError()){
        std::cout << "[OpenGL Error] ( " << error << " ): " << function << " " <<
        file << " : " << line << "\n";
        return false;
    }
    return true;
}

void Renderer::Clear() const{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{
    shader.Bind();
    va.Bind();
    ib.Bind();
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
