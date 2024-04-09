#include "ECSManager.h"

bool ECSInit()
{
    cam.AddComponent<PostitionComponent>();
    cam.AddComponent<CameraComponent>();
    
    beaver.AddComponent<PostitionComponent>();
    beaver.AddComponent<SpriteComponent>("res/Textures/Beaver1.jpg", 
                                         "res/Shaders/Basic.shader", 
                                         glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
                                         );

    return true;
}

void ECSStop()
{
    //
}