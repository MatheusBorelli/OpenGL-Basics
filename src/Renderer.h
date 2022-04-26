#pragma once

#include <GL/glew.h>
#include <stdbool.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file,int line);

//Renderer functions
void Draw(VertexArray *va,IndexBuffer *ib,Shader *shader);
void RendererClear();