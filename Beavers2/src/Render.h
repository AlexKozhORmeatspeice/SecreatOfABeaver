#pragma once
#include "Renderer.h"
#include "Components.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

bool RenderInit();
bool Render(std::unique_ptr<Manager> & manager);

void RenderStop();
int GLFWGetKeyState(int code);
float GetHeight();
float GetWeidth();