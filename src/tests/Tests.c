#include "Tests.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

void InitTestFunctions(Tests** test){
    //Init Functions
    void*(*funcInit[])()                 = {NULL,\
                                            &TestTranslation_Init,\
                                            &TestClearColor_Init,\
                                            &TestBatchRendering_Init};
    //Delete Functions
    void(*funcDelete[])(void**)          = {NULL,\
                                            &TestTranslation_Delete,\
                                            &TestClearColor_Delete,\
                                            &TestBatchRendering_Delete};
    //OnUpdate Function
    void(*funcOnUpdate[])(void**,float)  = {NULL,\
                                            &TestTranslation_OnUpdate,\
                                            &TestClearColor_OnUpdate,\
                                            &TestBatchRendering_OnUpdate};
    //OnRender Functions
    void(*funcOnRender[])(void*)         = {NULL,\
                                            &TestTranslation_OnRender,\
                                            &TestClearColor_OnRender,\
                                            &TestBatchRendering_OnRender};
    
    //OnImguiRender Functions
    void(*funcOnImguiRender[])(void**)   = {&TestMenu_OnImguiRender,\
                                            &TestTranslation_OnImGuiRender,\
                                            &TestClearColor_OnImGuiRender,\
                                            &TestBatchRendering_OnImGuiRender};

    for(unsigned i = 0; i < MAXTESTS; i++){
        (*test)->TestFunctions.TestInit[i]     = funcInit[i];
        (*test)->TestFunctions.TestDelete[i]   = funcDelete[i];
        (*test)->TestFunctions.TestOnUpdate[i] = funcOnUpdate[i];
        (*test)->TestFunctions.TestOnRender[i] = funcOnRender[i];
        (*test)->TestFunctions.TestOnImGuiRender[i] = funcOnImguiRender[i];
    }
}

void TestSelector(Tests** test){
    switch ((*test)->enumerator)
    {
    case MenuTest:
        (*test)->currentTestName = "Menu";
        (*test)->enumerator = MenuTest;
        (*test)->currentTestPointer = (*test);
        break;
    
    case TranslationTest:
        (*test)->currentTestName = "Translation Test";
        (*test)->enumerator = TranslationTest;
        (*test)->currentTestPointer = (*test)->TestFunctions.TestInit[TranslationTest]();
        break;

    case ClearColorTest:
        (*test)->currentTestName = "Clear Color";
        (*test)->enumerator = ClearColorTest;
        (*test)->currentTestPointer = (*test)->TestFunctions.TestInit[ClearColorTest]();
        break;
    
    case BatchRenderingTest:
        (*test)->currentTestName = "Batch Render";
        (*test)->enumerator = BatchRenderingTest;
        (*test)->currentTestPointer = (*test)->TestFunctions.TestInit[BatchRenderingTest]();
        break;
    
    default:
        (*test)->currentTestName = "Menu";
        (*test)->enumerator = MenuTest;
        (*test)->currentTestPointer = (*test);
        break;
    }
}

Tests* Tests_Init(enum m_EnumeratedFunctions selectTest){
    Tests* test = (Tests*) malloc(sizeof(Tests));
    if(test == NULL) return NULL;
    
    //Setup functions
    InitTestFunctions(&test);

    //Set enum if passed
    test->enumerator = selectTest;

    //Set current test pointer, name and enumerator 
    TestSelector(&test);

    //Set all tests names
    test->ListTestsNames[0] = "Translation Test";
    test->ListTestsNames[1] = "Clear Color Test";
    test->ListTestsNames[2] = "Batch Render Test";
    return test;
}

void Tests_Delete(Tests** test){
    free(*test);
}

void TestMenu_OnImguiRender(Tests **test){
    GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
    igBegin((*test)->currentTestName,0,0);
        for(unsigned i = 0 ; i < (MAXTESTS-1); i++)
            if(igButton((*test)->ListTestsNames[i],(ImVec2){0,0})){
                (*test)->enumerator = i + 1;
                TestSelector(&(*test));
        }
    igEnd();
}

void Tests_OnRender(Tests** test){
    //In case the default value is different than Menu Test
    if((*test)->enumerator != MenuTest)
    {
        (*test)->TestFunctions.TestOnUpdate[(*test)->enumerator]( &((*test)->currentTestPointer),0);
        (*test)->TestFunctions.TestOnRender[(*test)->enumerator]((*test)->currentTestPointer);
        igBegin((*test)->currentTestName,0,0);
        if((*test)->enumerator != MenuTest && igButton("<--",(ImVec2){0,0})){
            (*test)->TestFunctions.TestDelete[(*test)->enumerator](&((*test)->currentTestPointer));
            (*test)->enumerator = MenuTest;
            TestSelector(&(*test));
        }
        (*test)->TestFunctions.TestOnImGuiRender[(*test)->enumerator](&((*test)->currentTestPointer));
        igEnd();
    }
    else{
        igBegin((*test)->currentTestName,0,0);
        for(unsigned i = 0 ; i < (MAXTESTS-1); i++)
            if(igButton((*test)->ListTestsNames[i],(ImVec2){0,0})){
                (*test)->enumerator = i + 1;
                TestSelector(&(*test));
        }
        igEnd();
    }
}