#ifndef _SHADER_
#define _SHADER_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GLDebug.h"

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

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreatShader(const std::string& vertexShader, const std::string& fragmentShader);
    int GetUniformLocation(const std::string& name);
};
#endif // !_SHADER_