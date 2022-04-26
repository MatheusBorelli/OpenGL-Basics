#pragma once

#include "Renderer.h"

typedef struct m_TestTranslation TestTranslation;

TestTranslation *TestTranslation_Init();
void TestTranslation_Delete(TestTranslation** test);
void TestTranslation_OnUpdate(TestTranslation** test,float deltaTime);
void TestTranslation_OnRender(TestTranslation *test);
void TestTranslation_OnImGuiRender(TestTranslation** test);