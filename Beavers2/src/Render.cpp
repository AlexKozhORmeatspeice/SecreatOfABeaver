#include "Render.h"

int windowW = 1000;
int windowH = 800;

const char* glsl_version = "#version 330";

ImGuiIO* io;
GLFWwindow* window;

static float scroll = 0.0f;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    scroll = yoffset;
}


bool RenderInit()
{
    //set glfw,  glew, imgui
    if (!glfwInit())
        return false;

    window = glfwCreateWindow(windowW, windowH, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Can't set proparly GLFW";

        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetScrollCallback(window, scroll_callback);


    if (glewInit() != GLEW_OK)
    {
        std::cout << "Can't set proparly GLEW";
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stbi_set_flip_vertically_on_load(1);

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


bool Render(std::unique_ptr<Manager> & manager)
{
    if (glfwWindowShouldClose(window))
        return false;


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ////////////////////actual prog//////////////////////////
    manager->draw();
    ////////////////////actual prog//////////////////////////

     
    ///////////////////// some ImGUI//////////////////////
    /*ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();*/

    /*{
        ImGui::SliderFloat3("Translation", &transA.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / (*io).Framerate, (*io).Framerate);
    }*/
    ///////////////////// some ImGUI//////////////////////


    /*ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/

    glfwSwapBuffers(window);
    glfwPollEvents();

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

int GLFWGetKeyState(int code)
{
    return glfwGetKey(window, code);
}
int GLFWGetKeyMouseState(int state)
{
    return glfwGetMouseButton(window, state);
}
float GLFWGetHeight()
{
    return (float)windowH;
}

float GLFWGetWeidth()
{
    return (float)windowW;
}

void GLFWSetMousePos(double &xpos, double& ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
}

float GLFWGetScrool()
{
    float val = scroll;
    scroll = 0.0f;
    return val;
}