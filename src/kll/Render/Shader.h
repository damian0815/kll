//
// Created by Damian Stewart on 04/01/17.
//

#ifndef OFAPP_SHADER_H
#define OFAPP_SHADER_H

namespace kll {

    class Shader
    {
    public:
        Shader() { Register(); }
        virtual ~Shader() { Unregister(); }

        virtual void Reload() = 0;
        virtual void Begin() = 0;
        virtual void End() = 0;

    private:
        void Register();
        void Unregister();

    };

}

#endif //OFAPP_SHADER_H
