#pragma once

typedef struct VB_std
{
    unsigned int m_RendererID; 
}VertexBuffer;

void VertexBufferInit(VertexBuffer *vb,const void* data, unsigned int size);
void VertexBufferDelete(VertexBuffer* v_buffer);
void VertexBufferBind(VertexBuffer* v_buffer);
void VertexBufferUnBind();