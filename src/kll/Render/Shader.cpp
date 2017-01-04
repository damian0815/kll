//
// Created by Damian Stewart on 04/01/17.
//

#include "Shader.h"
#include "../Engine/Engine.h"

void kll::Shader::Register()
{
    kll::Engine::GetInstance()->RegisterShader(this);
}

void kll::Shader::Unregister()
{
    kll::Engine::GetInstance()->UnregisterShader(this);
}
