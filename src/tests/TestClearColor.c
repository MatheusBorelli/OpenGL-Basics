#include "TestClearColor.h"

#include "Renderer.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

typedef struct m_TestClearColor
{
    float m_Color[4];
}TestClearColor;

TestClearColor *TestClearColor_Init(){
    TestClearColor* test = (TestClearColor*) malloc(sizeof(TestClearColor));
    if(test != NULL){
        test->m_Color[0] = 0.2f;
        test->m_Color[1] = 0.3f;
        test->m_Color[2] = 0.8f;
        test->m_Color[3] = 1.0f;
    }
    return test;
}

void TestClearColor_Delete(TestClearColor** test){
    free((*test));
}

void TestClearColor_OnUpdate(void** test,float deltaTime){
}

void TestClearColor_OnRender(TestClearColor *test){
    GLCall(glClearColor(test->m_Color[0],test->m_Color[1],test->m_Color[2],test->m_Color[3]));
}

void TestClearColor_OnImGuiRender(TestClearColor** test){
    igColorEdit4("Clear Color",(*test)->m_Color,0);
}
