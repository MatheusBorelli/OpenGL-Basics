#pragma once

#include "TestTranslation.h"
#include "TestClearColor.h"
#include "TestBatchRendering.h"

#define MAXTESTS 4

typedef struct mFuncs{
    void* (*TestInit[MAXTESTS])          ();
    void  (*TestDelete[MAXTESTS])        (void**);
    void  (*TestOnUpdate[MAXTESTS])      (void**,float);
    void  (*TestOnRender[MAXTESTS])      (void*);
    void  (*TestOnImGuiRender[MAXTESTS]) (void**);
}TestFuncs;

enum m_EnumeratedFunctions{
    MenuTest,
    TranslationTest,
    ClearColorTest,
    BatchRenderingTest
}EnumeratedFunctions;

typedef struct m_TestMenu
{
    char*       currentTestName;
    char*       ListTestsNames[MAXTESTS-1];
    void*       currentTestPointer;
    TestFuncs   TestFunctions;
    enum m_EnumeratedFunctions enumerator;
}Tests;

void TestMenu_OnImguiRender(Tests **test);
Tests* Tests_Init(enum m_EnumeratedFunctions selectTest);
void Tests_Delete(Tests** tests);
void Tests_OnRender(Tests** test);
