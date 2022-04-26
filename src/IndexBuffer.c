#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer IndexBufferInit(const unsigned int* data, unsigned int count){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint)); // make sure that unsigned int is same size of OpenGl unsigned int(4 bytes)
    
    IndexBuffer i_buffer;
    i_buffer.m_Count = count;
    GLCall(glGenBuffers(1, &(i_buffer.m_RendererID)));//create id of generated buffer(vertex,texture,shader,anything)
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer.m_RendererID));//select buffer
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (i_buffer.m_Count * sizeof(unsigned int)) , data, GL_STATIC_DRAW));//Create a new data store fo a buffer object
    return i_buffer;
}
void IndexBufferDelete(IndexBuffer* i_buffer){
    GLCall(glDeleteBuffers(1, &(i_buffer->m_RendererID)));
}

void IndexBind(IndexBuffer* i_buffer){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, i_buffer->m_RendererID));//select buffer
}
void IndexUnbind(){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));//select buffer
}

