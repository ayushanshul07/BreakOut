//
//  Shader.cpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Shader.hpp"
#include "Renderer.hpp"


Shader::Shader(const std::string& filePath): m_FilePath(filePath){
    ShaderSource source = GetShaderSource(m_FilePath);
    m_RendererId = CreateShader(source.vertexShaderSource, source.fragmentShaderSource);
    
}

Shader::~Shader(){
    GlCall(glDeleteProgram(m_RendererId));
}

ShaderSource Shader::GetShaderSource(std::string& filePath){
    
    std::ifstream stream(filePath);
    std::stringstream ss[2];
     
    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    
    std::string line;
    ShaderType type = ShaderType::NONE;
    while(getline(stream,line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            }
            if(line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int)type] << line << "\n";
        }
    }
    return {ss[0].str(),ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char *message = (char*)alloca(sizeof(char)*length);
        glGetShaderInfoLog(id,length,&length,message);
        std::cout << "Failed to compile "
        << (type == GL_VERTEX_SHADER ? "vertex ": "fragment ")
        << "shader\n";
        std::cout << message << "\n";
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    if(vs == 0 || fs == 0) return 0;
    
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

void Shader::Bind() const{
    GlCall(glUseProgram(m_RendererId));
}

void Shader::UnBind() const{
    GlCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3){
    GlCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniform3f(const std::string& name, float f0, float f1, float f2){
    GlCall(glUniform3f(GetUniformLocation(name), f0, f1, f2));
}

void Shader::SetUniformMatrix4fv(const std::string& name, const float* value){
    GlCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value));
}

void Shader::SetUniform1i(const std::string& name, int value){
    GlCall(glUniform1i(GetUniformLocation(name), value));
}

int Shader::GetUniformLocation(const std::string& name){
    
    if(m_cache.find(name) != m_cache.end()) return m_cache[name];
    
    GlCall(int location = glGetUniformLocation(m_RendererId, name.c_str()));
    if(location == -1){
        std::cout << "Warning: uniform " << name << " doesn't exist\n";
    }
    m_cache[name] = location;
    return location;
}



