#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "utility/HashTable.h"

#include "vendor/cglm/cglm.h"

typedef struct SH_std
{
    unsigned int m_RendererID;
    char* m_filepath;
    HashTable cacheLocation;
}Shader;

void ShaderInit(Shader *shader,char* filepath);
void ShaderDelete(Shader *shader);
void ShaderBind(Shader *shader);
void ShaderUnbind();

//Set Uniforms
void SetUniform1i(Shader *shader,char* name, int value);
void SetUniform1iv(Shader *shader,char* name, int* values, int count);

void SetUniform1f(Shader *shader,char* name, float value);
void SetUniform4f(Shader *shader,char* name, float v0,float v1,float v2,float v3);

void SetUniformMat4f(Shader *shader,char* name,mat4* matrix);