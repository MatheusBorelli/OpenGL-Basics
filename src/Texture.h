#pragma once

#include "Renderer.h"

typedef struct textureClass{
    unsigned int m_RendererID;
    char* m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
}Texture;

void TextureInit(Texture *tx,char* path);
void TextureBind(Texture *tx,unsigned int slot);
void TextureUnbind();
void TextureDelete(Texture *tx);
