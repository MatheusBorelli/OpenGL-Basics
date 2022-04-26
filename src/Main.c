#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#include "tests/Tests.h"

int main(int argc, char *argv[])
{
    GLFWwindow* window;
    
    // Initialize the library
    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Make the window's context current
    glfwMakeContextCurrent(window);

    //lock framerate to current frequency of monitor
    //glfwSwapInterval(1);

    //Iniciando glew para pegar as funções mais recentes do opengl pelo driver da gpu 
    if(glewInit() != GLEW_OK)
        printf("Init Glew Error");

    //Versao do OpenGl
    printf("%s\n",glGetString(GL_VERSION));
    
    const char* glsl_version = "#version 330";
    igCreateContext(NULL);
    ImGuiIO *ioptr = igGetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    igStyleColorsDark(NULL);

    Tests* tests = Tests_Init(BatchRenderingTest);

    while(!glfwWindowShouldClose(window))
    {
        RendererClear();
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        igNewFrame();

        Tests_OnRender(&tests);
        igText("Application average %3.f ms/frame (%.1f FPS)", 1000.0f / ioptr->Framerate, ioptr->Framerate);
    
        igEndFrame();
        igRender();
        ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    Tests_Delete(&tests);
    igDestroyContext(NULL);
    glfwTerminate();
    return 0;
}