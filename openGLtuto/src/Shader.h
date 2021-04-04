#ifndef _SHADER_
#define _SHADER_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "GLDebug.h"
#include <mat4x4.hpp>

struct ShaderProgramSource
{
    std::string VextexSource;
    std::string FragmentSource;
};
class Shader
{
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniformi(const std::string& name, int value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4by4(const std::string& name, glm::mat4x4& mat);
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreatShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
    std::unordered_map<std::string, int> m_UniformLocationCache;
};
#endif // !_SHADER_