//
// Created by Damian Stewart on 04/01/17.
//

#ifndef OFAPP_FLATSHADER_H
#define OFAPP_FLATSHADER_H


#include <gl/ofShader.h>
#include "Shader.h"

namespace kll
{

    class FlatShader : public Shader
    {
    public:
        void Reload() override;

        void Begin() override;
        void End() override;

    private:

        ofShader mShader;
    };

}

#endif //OFAPP_FLATSHADER_H
