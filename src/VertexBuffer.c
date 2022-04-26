#include "VertexBuffer.h"

#include "Renderer.h"

void VertexBufferInit(VertexBuffer *vb, const void* data, unsigned int size){
    GLCall(glCreateBuffers(1, &(vb->m_RendererID)));//create id of generated buffer(vertex,texture,shader,anything)
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb->m_RendererID));//select buffer
    GLCall(glBufferData(GL_ARRAY_BUFFER, size , data, GL_STATIC_DRAW));//Create a new data store to a buffer object
}
void VertexBufferDelete(VertexBuffer* v_buffer){
    GLCall(glDeleteBuffers(1, &(v_buffer->m_RendererID)));
}

void VertexBufferBind(VertexBuffer* v_buffer){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, v_buffer->m_RendererID));//select buffer
}
void VertexBufferUnBind(){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));//select buffer
}