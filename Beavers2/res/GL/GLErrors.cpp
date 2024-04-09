#include <GLErrors.h>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "):" << function << " " << file << " AT LINE: " << line << std::endl;
        return false;
    }

    return true;
}