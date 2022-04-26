#include "TestTranslation.h"
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "Texture.h"

#include "vendor/cglm/cglm.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

typedef struct m_TestTranslation
{
    VertexArray va;
    unsigned int vao;

    VertexBuffer vb;
    VertexBufferLayout layout;

    IndexBuffer ib;

    Shader shader;
    Texture texture;

    mat4 proj;
    mat4 view;
    vec3 viewMove;

    mat4 modelA;
    mat4 modelB;

    vec3 translationA;
    vec3 translationB;

    mat4 mvpA;
    mat4 mvpB;
    
    float objectColor[4];
    float backgroundColor[4];
}TestTranslation;


TestTranslation *TestTranslation_Init(){
    
    TestTranslation *test =(TestTranslation*) malloc(sizeof(TestTranslation));
    if(test == NULL) return NULL;
    
    float positions[] = { 
          -50.0f, -50.0f, 0.0f , 0.0f,  // 0
           50.0f, -50.0f, 1.0f , 0.0f,  // 1
           50.0f,  50.0f, 1.0f , 1.0f,  // 2
          -50.0f,  50.0f, 0.0f , 1.0f   // 3
    };
    unsigned indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    //VertexArray
    VxArrayInit(&(test->va));

    //vertex buffer
    VertexBufferInit(&(test->vb),positions, sizeof(positions));
    
    //Vertex buffer Layout
    VertexBufferLayoutInit(&(test->layout));
    VertexBufferLayoutPush(&(test->layout),GL_FLOAT,2);
    VertexBufferLayoutPush(&(test->layout),GL_FLOAT,2);
    VxBufferAdd(&(test->va),&(test->vb),&(test->layout));
    
    //index buffer object
    test->ib = IndexBufferInit(indices, 6 );
    
    //MVP stuff
    glm_ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f , 1.0f, test->proj);
    
    glm_mat4_identity(test->view);

    vec3 dummy = {0,0,0};
    glm_vec3_copy(dummy,test->viewMove);
    glm_translate(test->view, test->viewMove);
    
    //Shader 
    char pathShader[] = "asset/shaders/Basic.shader";
    ShaderInit(&(test->shader), pathShader);
    ShaderBind(&(test->shader));
    
    //Textures
    char pathTexture[] = "asset/texture/Texture.png";
    TextureInit(&(test->texture), pathTexture);
    TextureBind(&(test->texture), 0);

    //Uniforms
    SetUniform4f(&(test->shader),"u_Color", 0.2f, 0.3f, 0.8f, 0.0f);
    SetUniform1i(&(test->shader),"u_Texture", 0);
    
    //DESELECT EVERY BUFFER
    VxArrayUnBind(&(test->va));
    VertexBufferUnBind();
    IndexUnbind();
    ShaderUnbind(&(test->shader));

    //Set Color if texture is disabled    
    test->objectColor[0] = 1.0f;
    test->objectColor[1] = 1.0f;
    test->objectColor[2] = 1.0f;
    test->objectColor[3] = 1.0f;

    test->backgroundColor[0] = 0.2f;
    test->backgroundColor[1] = 0.3f;
    test->backgroundColor[2] = 0.8f;
    test->backgroundColor[3] = 1.00f;
    // Set startup Translation positions for both objects
    dummy[0] = 200;
    dummy[1] = 200;
    glm_vec3_copy(dummy ,test->translationA);
    dummy[0] = 400;
    glm_vec3_copy(dummy ,test->translationB);

    //glm_translate(model, translation);
    //Para multiplicar tudo em uma funcao: glm_mat4_mulN((mat4 *[]){&proj, &view, &model}, 3 , mvp);
    return test;
}

void TestTranslation_Delete(TestTranslation** test){
    GLCall(glDisable(GL_BLEND));
    VxArrayDelete(&((*test)->va));
    VertexBufferDelete(&((*test)->vb));
    IndexBufferDelete(&((*test)->ib));
    ShaderDelete(&((*test)->shader));
    TextureDelete(&((*test)->texture));
    free((*test));
}

void TestTranslation_OnUpdate(TestTranslation** test,float deltaTime){
    //Object A
    glm_mat4_identity((*test)->modelA);
    glm_mat4_identity((*test)->modelB);

    glm_translate((*test)->modelA, (*test)->translationA);

    glm_mat4_mul((*test)->proj,(*test)->view,(*test)->mvpA);
    glm_mat4_mul((*test)->mvpA,(*test)->modelA,(*test)->mvpA);

    //object B
    glm_translate((*test)->modelB, (*test)->translationB);
    
    glm_mat4_mul((*test)->proj,(*test)->view,(*test)->mvpB);
    glm_mat4_mul((*test)->mvpB,(*test)->modelB,(*test)->mvpB);
}

void TestTranslation_OnRender(TestTranslation *test){
    
    //Object A
    ShaderBind(&(test->shader));
    SetUniform4f(&(test->shader),"u_Color", test->objectColor[0], test->objectColor[1], test->objectColor[2], test->objectColor[3]);
    SetUniformMat4f(&(test->shader),"u_MVP",&(test->mvpA));
    Draw(&(test->va) , &(test->ib) , &(test->shader));

    //Object B
    ShaderBind(&(test->shader));
    SetUniformMat4f(&(test->shader),"u_MVP",&(test->mvpB));
    Draw(&(test->va) , &(test->ib) , &(test->shader));

    GLCall(glClearColor(test->backgroundColor[0],test->backgroundColor[1],test->backgroundColor[2],test->backgroundColor[3]));
}

void TestTranslation_OnImGuiRender(TestTranslation** test){
    igSliderFloat3("Translation A", (*test)->translationA, 0.0f, 960.0f, "%.3f", 0);
    igSliderFloat3("Translation B", (*test)->translationB, 0.0f, 960.0f, "%.3f", 0);
    igNewLine();
    igNewLine();
    igNewLine();
    igColorEdit4("Background Color", (*test)->backgroundColor , 0);
    igColorEdit4("Object Color", (*test)->objectColor , 0);
}