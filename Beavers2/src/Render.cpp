#include "Render.h"
#include "Components.h"
#include "ECSManager.h"

const char* glsl_version = "#version 330";

ImGuiIO* io;
GLFWwindow* window;

//ECS Fles//

//ECS Fles//


bool RenderInit()
{
    //set glfw,  glew, imgui
    if (!glfwInit())
        return false;

    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Can't set proparly GLFW";

        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

   
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Can't set proparly GLEW";
        return false;
    }

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io = &ImGui::GetIO(); (void)io;
    (*io).ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    ImGui::StyleColorsDark();

    std::cout << glGetString(GL_VERSION) << std::endl;

    return true;
}

float r = 0.0f;
float inc = 0.05f;

bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

bool Render()
{
    if (glfwWindowShouldClose(window))
        return false;

    
    glClear(GL_COLOR_BUFFER_BIT);
    
    ////////////////////actual prog//////////////////////////
    manager.draw();
    ////////////////////actual prog//////////////////////////

     
    ///////////////////// some ImGUI//////////////////////
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    /*{
        ImGui::SliderFloat3("Translation", &transA.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / (*io).Framerate, (*io).Framerate);
    }*/
    ///////////////////// some ImGUI//////////////////////


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    

    return true;
}

void RenderStop()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
       

    glfwDestroyWindow(window);
    glfwTerminate();
}