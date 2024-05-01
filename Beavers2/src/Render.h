#pragma once
#include "ECS.h"

#include "stb_image.h"
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "GLErrors.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

bool RenderInit();
bool Render(std::unique_ptr<Manager> & manager);
void RenderStop();

int GLFWGetKeyState(int code);
float GLFWGetHeight();
float GLFWGetWeidth();
void GLFWSetMousePos(double& xpos, double& ypos);
int GLFWGetKeyMouseState(int state);
float GLFWGetScrool();