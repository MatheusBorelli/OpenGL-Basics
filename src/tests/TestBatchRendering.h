#pragma once

typedef struct m_TestBatchRendering TestBatchRendering;

TestBatchRendering *TestBatchRendering_Init();
void TestBatchRendering_Delete(TestBatchRendering** test);
void TestBatchRendering_OnUpdate(TestBatchRendering** test,float deltaTime);
void TestBatchRendering_OnRender(TestBatchRendering *test);
void TestBatchRendering_OnImGuiRender(TestBatchRendering** test);