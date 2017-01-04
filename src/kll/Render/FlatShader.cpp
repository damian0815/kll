//
// Created by Damian Stewart on 04/01/17.
//

#include <fmt/format.h>
#include "FlatShader.h"

void kll::FlatShader::Reload()
{
    mShader.unload();

    const string SHADER_NAME = "shaders/flat";
    bool loaded = mShader.load(SHADER_NAME);
}

void kll::FlatShader::Begin()
{
    mShader.begin();
}

void kll::FlatShader::End()
{
    mShader.end();
}
