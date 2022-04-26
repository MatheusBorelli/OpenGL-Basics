#include <stdio.h>

#include "Renderer.h"

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file,int line)
{
    GLenum error;
    while((error = glGetError()))
    {
        printf("[OpenGL Error] - (%d - 0x%04x): %s %s:%d\n", error, error, function, file, line);
        return false;
    }
    return true;
}

void RendererClear(){
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Draw(VertexArray *va,IndexBuffer *ib,Shader *shader)
{
    ShaderBind(shader);
    VxArrayBind(va);
    IndexBind(ib);
    GLCall(glDrawElements(GL_TRIANGLES, ib->m_Count , GL_UNSIGNED_INT, NULL));
}