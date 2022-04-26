#pragma once

typedef struct IB_std
{
    unsigned int m_RendererID; 
    unsigned int m_Count;
}IndexBuffer;

IndexBuffer IndexBufferInit(const unsigned int* data, unsigned int count);
void IndexBufferDelete(IndexBuffer* i_buffer);
void IndexBind(IndexBuffer* i_buffer);
void IndexUnbind();