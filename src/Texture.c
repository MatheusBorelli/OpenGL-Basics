#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"

void TextureInit(Texture *tx,char* path){
    tx->m_FilePath = path;
    tx->m_RendererID = 0;
    tx->m_Height = 0;
    tx->m_Width = 0;
    tx->m_LocalBuffer = NULL;
    tx->m_BPP = 0;

    GLubyte texData[] = { 255, 255, 255, 255 };

    if(path != NULL){
        stbi_set_flip_vertically_on_load(1);
        tx->m_LocalBuffer = stbi_load(path, &(tx->m_Width), &(tx->m_Height), &(tx->m_BPP), 4);
    }
    else{
        tx->m_LocalBuffer = texData;
    }

    GLCall(glGenTextures(1, &(tx->m_RendererID)));
    GLCall(glBindTexture(GL_TEXTURE_2D, tx->m_RendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    if(path != NULL){
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tx->m_Width, tx->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tx->m_LocalBuffer));
    }
    else{
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, tx->m_LocalBuffer));
    }
    
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(tx->m_LocalBuffer && path != NULL)
        stbi_image_free(tx->m_LocalBuffer);
    else
        tx->m_LocalBuffer = NULL;
}

void TextureBind(Texture *tx, unsigned int slot){
    if(slot < 0 || slot > 32)
        slot = 0;
    
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, tx->m_RendererID));
}

void TextureUnbind(){
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void TextureDelete(Texture *tx){
    GLCall(glDeleteTextures(1, &(tx->m_RendererID)));
}

////////////////////////////////////////// 2D ARRAY TEXTURES ////////////////////////////////
/*void TextureArrayInit(Texture *tx,char* path, char* path2){
    tx->m_FilePath = path;
    tx->m_RendererID = 0;
    tx->m_Height = 0;
    tx->m_Width = 0;
    tx->m_LocalBuffer = NULL;
    tx->m_BPP = 0;
    Texture *tx_2 =(Texture*)malloc(sizeof(Texture));
    tx_2->m_FilePath = path2;
    tx_2->m_RendererID = 0;
    tx_2->m_Height = 0;
    tx_2->m_Width = 0;
    tx_2->m_LocalBuffer = NULL;
    tx_2->m_BPP = 0;
    int layer = 2;
    
    stbi_set_flip_vertically_on_load(1);

    tx->m_LocalBuffer = stbi_load(tx->m_FilePath, &(tx->m_Width), &(tx->m_Height), &(tx->m_BPP), 4);
    
    tx_2->m_LocalBuffer = stbi_load(tx_2->m_FilePath, &(tx->m_Width), &(tx->m_Height), &(tx->m_BPP), 4);
    
    GLCall(glCreateTextures(GL_TEXTURE_2D_ARRAY,1, &(tx->m_RendererID)));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, tx->m_RendererID));
    GLCall(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1 , GL_RGBA8, tx->m_Width, tx->m_Height, layer));

    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, tx->m_Width, tx->m_Height, 1, GL_RGB, GL_UNSIGNED_BYTE, tx->m_LocalBuffer);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 1, tx_2->m_Width, tx_2->m_Height, 1, GL_RGB, GL_UNSIGNED_BYTE, tx_2->m_LocalBuffer);
    
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

    if(tx->m_LocalBuffer && tx_2->m_LocalBuffer){
        stbi_image_free(tx->m_LocalBuffer);
        stbi_image_free(tx_2->m_LocalBuffer);
    }
}

void TextureArrayBind(Texture *tx, unsigned int slot){
    if(slot < 0 || slot > 32)
        slot = 0;
    
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, tx->m_RendererID));
    glEnable(GL_TEXTURE_2D_ARRAY);
    glBindTexture(GL_TEXTURE_2D_ARRAY, tx->m_RendererID);
}

void TextureArrayUnbind(){
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));
    glDisable(GL_TEXTURE_2D_ARRAY);
}
*/