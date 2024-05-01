#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLErrors.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <unordered_map>


struct ShaderProgramSourse
{
    std::string VertexSourse;
    std::string FragmentSourse;
};

class Shader
{
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniLocatinCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int v0);
    void SetUniform1f(const std::string& name, float v0);
    void SetUniformMat4f(const std::string& name, glm::mat4 matrix);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform2f(const std::string& name, float v0, float v1);
private:
    ShaderProgramSourse ParseShader(const std::string& filepath);
    unsigned int CompileShader(const std::string& source, unsigned int type);
    int CreateShader(const std::string& vertShader, const std::string& fragShader);
    int GetUniformLocation(const std::string& name);
};