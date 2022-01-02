//
//  Shader.hpp
//  OpenGL
//
//  Created by Ayush Anshul on 24/12/21.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <unordered_map>
#include <string>

struct ShaderSource{
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
};

class Shader{
private:
    unsigned int m_RendererId;
    std::string m_FilePath;
    //caching
    std::unordered_map<std::string, int> m_cache;
public:
    Shader(const std::string& filePath);
    ~Shader();
    
    void Bind() const;
    void UnBind() const;
    
    //Set uniforms
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
    void SetUniform3f(const std::string& name, float f0, float f1, float f2);
    void SetUniformMatrix4fv(const std::string& name, const float* value);
    void SetUniform1i(const std::string& name, int value);

private:
    int GetUniformLocation(const std::string& name);
    ShaderSource GetShaderSource(std::string& filePath);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    
};

#endif /* Shader_hpp */
