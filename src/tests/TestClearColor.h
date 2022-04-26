#pragma once

typedef struct m_TestClearColor TestClearColor;

TestClearColor *TestClearColor_Init();
void TestClearColor_Delete(TestClearColor** test);
void TestClearColor_OnUpdate(void** test,float deltaTime);
void TestClearColor_OnRender(TestClearColor *test);
void TestClearColor_OnImGuiRender(TestClearColor** test);