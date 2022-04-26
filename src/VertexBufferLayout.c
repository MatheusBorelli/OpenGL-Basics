#include "VertexBufferLayout.h"
#include "Renderer.h"

void VertexBufferLayoutInit(VertexBufferLayout *vxBL){
    vxBL->m_Elements = InitVector(sizeof(VertexBufferElements));
    vxBL->m_Stride = 0;
}

void VertexBufferLayoutPush(VertexBufferLayout *vxBL, unsigned int type,unsigned int count){
    VertexBufferElements temp = { 
        type,
        count,
        GL_FALSE,
        0
    };
    switch (type)
    {
        case GL_FLOAT:
            vxBL->m_Stride += count * sizeof(GLfloat);
            temp.sizeOfType += sizeof(GLfloat);
            break;
        
        case GL_UNSIGNED_INT:
            vxBL->m_Stride += count * sizeof(GLuint);
            temp.sizeOfType += sizeof(GLuint);
            break;
        
        case GL_INT:
            vxBL->m_Stride += count * sizeof(GLint);
            temp.sizeOfType += sizeof(GLint);
            break;

        case GL_UNSIGNED_BYTE:
            vxBL->m_Stride += count * sizeof(GLbyte);
            temp.sizeOfType += sizeof(GLbyte);
            temp.normalized = GL_TRUE;
            break;
        
        default:
            ASSERT(false);
            return;
            break;
    }
    VectorPushBack(vxBL->m_Elements,&temp,sizeof(VertexBufferElements));
}

unsigned int GetStride(const VertexBufferLayout *layout){
    return layout->m_Stride;
}