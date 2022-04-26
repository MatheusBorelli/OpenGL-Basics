#include "TestBatchRendering.h"

#include "Renderer.h"
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "Texture.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

#include "vendor/cglm/cglm.h"

#include <math.h>

#define MAXTEXTURES 3

typedef struct m_TestBatchRendering
{
    VertexArray va;
    unsigned int vao;

    VertexBuffer vb;
    VertexBufferLayout layout;

    IndexBuffer ib;

    Texture textureWhite;
    Texture textureWood;
    Texture textureLogo;

    Shader shader;

    mat4 proj;
    mat4 view;
    vec3 viewMove;

    mat4 model;

    vec3 translation;

    mat4 mvp;
    float tilingFactor;
    vec4 color;
}TestBatchRendering;

typedef struct m_Quad{
    float positions[2],
          colors[4],
          TexCoord[2],
          TexIndex;
}VertexData;

TestBatchRendering *TestBatchRendering_Init(){
    TestBatchRendering* test = (TestBatchRendering*) malloc(sizeof(TestBatchRendering));
    if(test == NULL) 
        return NULL;

    VertexData vertices[] = {
        //    Positions                   Color                Texture Coord/index 
          {{150.0f, 150.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {0.0f, 0.0f}, {0.0f}},// 0
          {{250.0f, 150.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {1.0f, 0.0f}, {0.0f}},// 1
          {{250.0f, 250.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {1.0f, 1.0f}, {0.0f}},// 2
          {{150.0f, 250.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {0.0f, 1.0f}, {0.0f}},// 3

          {{350.0f, 150.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {0.0f, 0.0f}, {1.0f}},// 4
          {{450.0f, 150.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {1.0f, 0.0f}, {1.0f}},// 5
          {{450.0f, 250.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {1.0f, 1.0f}, {1.0f}},// 6
          {{350.0f, 250.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {0.0f, 1.0f}, {1.0f}},// 7

          {{250.0f, 350.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {0.0f, 0.0f}, {2.0f}},// 8
          {{350.0f, 350.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {1.0f, 0.0f}, {2.0f}},// 9
          {{350.0f, 450.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {1.0f, 1.0f}, {2.0f}},// 10
          {{250.0f, 450.0f},     {1.0f, 1.0f, 1.0f, 1.0f},     {0.0f, 1.0f}, {2.0f}} // 11
    };
/*
    {150.0f, 150.0f} {0.0f, 0.0f}    
    {250.0f, 150.0f} {50.0f, 0.0f}   
    {250.0f, 250.0f} {50.0f, 50.0f}  
    {150.0f, 250.0f} {0.0f, 50.0f}   
    
    {350.0f, 150.0f} {55.0f, 55.0f}  
    {450.0f, 150.0f} {105.0f, 55.0f} 
    {450.0f, 250.0f} {105.0f, 105.0f}
    {350.0f, 250.0f} {55.0f, 105.0f} 

    {250.0f, 350.0f}{110.0f, 110.0f}
    {350.0f, 350.0f}{160.0f, 110.0f}
    {350.0f, 450.0f}{160.0f, 160.0f}
    {250.0f, 450.0f}{110.0f, 160.0f}

    float vertices[] = { 
          150.0f, 150.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0,// 0
          250.0f, 150.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 0.0f, 0,// 1
          250.0f, 250.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 0,// 2
          150.0f, 250.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 0,// 3

          350.0f, 150.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 1,// 4
          450.0f, 150.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 0.0f, 1,// 5
          450.0f, 250.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f, 1,// 6
          350.0f, 250.0f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f, 1// 7
    };
*/
    unsigned indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,
        
        8, 9, 10,
        10, 11, 8
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    

    //VertexArray
    VxArrayInit(&(test->va));
    VxArrayBind(&(test->va));
    
    //vertex buffer
    VertexBufferInit(&(test->vb), vertices, sizeof(vertices));

    //Vertex buffer Layout
    
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glEnableVertexAttribArray(2));
    GLCall(glEnableVertexAttribArray(3));
    
    //This code is what the below code does but using only OpenGL functions 
    GLCall(glVertexAttribPointer(0 , 2, GL_FLOAT , GL_FALSE, sizeof(VertexData), NULL));
    GLCall(glVertexAttribPointer(1 , 4, GL_FLOAT , GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData,colors)));
    GLCall(glVertexAttribPointer(2 , 2, GL_FLOAT , GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData,TexCoord)));
    GLCall(glVertexAttribPointer(3 , 1, GL_FLOAT , GL_FALSE, sizeof(VertexData), (const void*)offsetof(VertexData,TexIndex)));
    //GLCall(glVertexAttribIPointer(3 , 1, GL_INT , sizeof(VertexData), (const void*)offsetof(VertexData,TexIndex)));
    
    //This code Attribuites in a more easy way the organization of Vertex Buffer Layout
    //VertexBufferLayoutInit(&(test->layout));
    //VertexBufferLayoutPush(&(test->layout),GL_FLOAT,2);
    //VertexBufferLayoutPush(&(test->layout),GL_FLOAT,4);
    //VertexBufferLayoutPush(&(test->layout),GL_FLOAT,2);
    //VertexBufferLayoutPush(&(test->layout),GL_FLOAT,1);
    //VxBufferAdd(&(test->va),&(test->vb),&(test->layout));

    
    //index buffer object
    test->ib = IndexBufferInit(indices, 12+6);

    //MVP stuff
    glm_ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f , 1.0f, test->proj);
    
    glm_mat4_identity(test->view);

    vec3 dummy = {0,0,0};
    glm_vec3_copy(dummy,test->viewMove);
    glm_translate(test->view, test->viewMove);
    glm_mat4_identity(test->model);

    glm_vec3_copy(dummy,test->translation);
    glm_translate(test->model, test->translation);

    glm_mat4_mul( test->proj, test->view, test->mvp);
    glm_mat4_mul( test->mvp, test->model, test->mvp);

    
    //Texture
    //TextureArrayInit(&(test->textureLogo),"asset/texture/Texture.png","asset/texture/Texture2.png");
    
    TextureInit(&(test->textureWhite),NULL);
    TextureInit(&(test->textureLogo),"asset/texture/Texture.png");
    TextureInit(&(test->textureWood),"asset/texture/wood.png");
    
    TextureBind(&(test->textureWhite),0);
    TextureBind(&(test->textureLogo),1);
    TextureBind(&(test->textureWood),2);

    //Shader 
    char pathShader[] = "asset/shaders/BasicBatchRender.glsl";
    ShaderInit(&(test->shader), pathShader);
    ShaderBind(&(test->shader));
    
    //Uniforms
    int samplers[MAXTEXTURES];
    for(int i = 0; i < MAXTEXTURES; i++) samplers[i] = i;
    SetUniform1iv(&(test->shader), "u_Textures", samplers, 3);
    
    test->tilingFactor = 1.0f;
    SetUniform1f(&(test->shader), "u_TilingFactor",test->tilingFactor); 
    
    SetUniformMat4f(&(test->shader),"u_MVP",&(test->mvp));

    //SetUniform4f(&(test->shader),"u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    
    //UNBIND EVERY BUFFER
    VxArrayUnBind();
    VertexBufferUnBind();
    IndexUnbind();
    ShaderUnbind();
    //TextureUnbind();

    test->color[0] = 0.0f;
    test->color[1] = 0.0f;
    test->color[2] = 0.0f;
    test->color[3] = 1.0f;
    return test;
}

void TestBatchRendering_Delete(TestBatchRendering** test){
    GLCall(glDisable(GL_BLEND));
    VxArrayDelete(&((*test)->va));
    VertexBufferDelete(&((*test)->vb));
    IndexBufferDelete(&((*test)->ib));
    ShaderDelete(&((*test)->shader));
    
    TextureDelete(&(*test)->textureLogo);
    TextureDelete(&(*test)->textureWood);
    
    free(*test);
}

void TestBatchRendering_OnUpdate(TestBatchRendering** test,float deltaTime){
    glm_mat4_identity((*test)->model);

    glm_translate((*test)->model , (*test)->translation );

    glm_mat4_mul( (*test)->proj,(*test)->view, (*test)->mvp);
    glm_mat4_mul( (*test)->mvp, (*test)->model, (*test)->mvp);

}

void TestBatchRendering_OnRender(TestBatchRendering *test){
    GLCall(glClearColor(test->color[0], test->color[1], test->color[2],test->color[3]));
    ShaderBind(&(test->shader));
    //SetUniform4f(&(test->shader),"u_Color",0.2f, 0.3f, 0.8f, 1.0f);

    SetUniform1f(&(test->shader), "u_TilingFactor",test->tilingFactor);
    SetUniformMat4f(&(test->shader),"u_MVP",&(test->mvp));
    Draw(&(test->va),&(test->ib),&(test->shader));
}

void TestBatchRendering_OnImGuiRender(TestBatchRendering** test){
    //double x = floor((*test)->translation[0]);
    //double y = floor((*test)->translation[1]);
    //double z = 0;
//
    //int pos[2];
    //pos[0] = (int) x;
    //pos[1] = (int) y;
//
    //igSliderInt2("Translation", pos,-960.0f, 960.0f,"%d",0);
    igSliderFloat2("Translation", (*test)->translation, -960.0f, 960.0f, "%.3f", 0);
    igSliderFloat("Tiling Factor", &((*test)->tilingFactor), 0.0f, 1.0f, "%.3f", 0);
    igColorEdit4("Background Color", (*test)->color ,0);
    igNewLine();

    //(*test)->translation[0] = (float)pos[0];
    //(*test)->translation[1] = (float)pos[1];
    //(*test)->translation[2] = (float)z;
}
