#include "Shader.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <sstream>

//parses our shader file and creates a new OpenGL shader program
Shader::Shader(const std::string& filePath) : m_filePath(filePath), m_rendererID(0)
{
    ShaderProgramSource source = parseShader(filePath);

    m_rendererID = createShader(source.VertexSource, source.FragmentSource);
}

//deletes our shader program
Shader::~Shader()
{
    glDeleteProgram(m_rendererID);
}

//tells OpenGL to use this shader program
void Shader::bind() const
{
    glUseProgram(m_rendererID);
}

//sets shader program to null
void Shader::unbind() const
{
    glUseProgram(0);
}

//sets an integer value in shader code
void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniformLocation(name), value);
}
//sets a float value in shader code
void Shader::setUniform1f(const std::string& name, float value)
{
    glUniform1f(getUniformLocation(name), value);
}
//sets a float4 value in shader code
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

//get the index of a uniform in m_uniformLocationCache
int Shader::getUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];
    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1) std::cout << "Warning: uniform " << name << " doesnt exist!\n";

    m_uniformLocationCache[name] = location;
    return location;
}

//seperates the vertex and fragment shaders into seperate strings
ShaderProgramSource Shader::parseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

//creates a new shader and compiles shader code
unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    //ensure source exists
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

//creates a new shader program and attaches our compiled vertex and fragment shaders
unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    //delete no longer needed shader slot
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
