#include "Shader.h"

Shader::Shader(const std::string& filepath) : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSourse sourse = ParseShader(filepath);
    m_RendererID = CreateShader(sourse.VertexSourse, sourse.FragmentSourse);
    Bind();
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniLocatinCache.find(name) != m_UniLocatinCache.end())
        return m_UniLocatinCache[name];

    GLCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));

    if (loc == -1)
        std::cout << "Warning: unifrom " << name << " doesn't existd" << std::endl;

    m_UniLocatinCache[name] = loc;
    return loc;
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}
void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}


ShaderProgramSourse Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        None = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::None;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int res;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &res));

    if (res == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

int Shader::CreateShader(const std::string& vertShader, const std::string& fragShader)
{
    unsigned int prog = glCreateProgram();
    unsigned int vs = CompileShader(vertShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(prog, vs));
    GLCall(glAttachShader(prog, fs));
    GLCall(glLinkProgram(prog));
    GLCall(glValidateProgram(prog));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return prog;
}

///a lot of shader functions could be here (but maybe just a few im not soure for now)

void Shader::SetUniform1i(const std::string& name, int v0)
{
    int loc = GetUniformLocation(name);
    GLCall(glUniform1i(loc, v0));
}

void Shader::SetUniform1f(const std::string& name, float v0)
{
    int loc = GetUniformLocation(name);
    GLCall(glUniform1f(loc, v0));
}
void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    int loc = GetUniformLocation(name);
    GLCall(glUniform4f(loc, v0, v1, v2, v3));
}
void Shader::SetUniform2f(const std::string& name, GLfloat v0, GLfloat v1)
{
    int loc = GetUniformLocation(name);
    GLCall(glUniform2f(loc, v0, v1));
}
void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix)
{
    int loc = GetUniformLocation(name);
    GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]));
}