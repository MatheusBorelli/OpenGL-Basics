#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

//typedef struct vxb_layout VertexBufferLayout;

typedef struct vx_Array
{
    unsigned int m_RendererID; 
}VertexArray;

void VxArrayInit(VertexArray *va);
void VxArrayDelete(VertexArray *va);
void VxBufferAdd(VertexArray *va,VertexBuffer *vb, const VertexBufferLayout *layout);
void VxArrayBind(VertexArray *va);
void VxArrayUnBind();