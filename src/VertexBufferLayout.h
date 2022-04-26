#pragma once

#include <stdbool.h>


#include "utility/Vector.h"

typedef struct vxb_elements
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    unsigned int sizeOfType;
}VertexBufferElements;

typedef struct vxb_layout
{
    Vector *m_Elements;
    unsigned int m_Stride;
}VertexBufferLayout;

void VertexBufferLayoutInit(VertexBufferLayout *vxBL);

void VertexBufferLayoutPush(VertexBufferLayout *vxBL, unsigned int type,unsigned int count);

unsigned int GetStride(const VertexBufferLayout *layout);