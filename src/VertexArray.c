#include "VertexArray.h"

#include "Renderer.h" 

void VxArrayInit(VertexArray *va){
    GLCall(glCreateVertexArrays(1, &(va->m_RendererID)));
}

void VxArrayDelete(VertexArray *va)
{
    GLCall(glDeleteVertexArrays(1,&(va->m_RendererID)));
}

void VxArrayBind(VertexArray *va){
    GLCall(glBindVertexArray(va->m_RendererID));
}
void VxArrayUnBind(){
    GLCall(glBindVertexArray(0));
}

void VxBufferAdd(VertexArray *va,VertexBuffer *vb, const VertexBufferLayout *layout){
    VxArrayBind(va);
    VertexBufferBind(vb);
    uint32_t offset = 0;

    for(unsigned int i = 0 ; i < VectorLength(layout->m_Elements); i++)
    {    
        VertexBufferElements element;
        CopyValueVector(layout->m_Elements, &element ,i);
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i , element.count, element.type , element.normalized, layout->m_Stride, (const void*)offset)); //Defines how should interpretate the values from positions
        offset += element.count * element.sizeOfType;
    }
}
