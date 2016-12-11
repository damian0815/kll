//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_OBJECT_H
#define OFAPP_OBJECT_H

#include <glm/gtc/quaternion.hpp>
#include "kll.h"
using glm::quat;

namespace kll {

    class Object
    {
    public:
        Object(): mScale(1,1,1) {}
        Object(vec3 initialPos): Object() { mPosition = initialPos; }

        virtual ~Object() {};

        void Draw();
        void Update(float dt);

        const vec3& GetScale() const { return mScale; }
        void SetScale(vec3 scale) { mScale = scale; }

        const vec3& GetVelocity() const { return mVelocity; }
        void SetVelocity(const vec3 &velocity) { mVelocity = velocity; }

        void SetOrientation(const quat &q) { mOrientation = q; }
        const quat &GetOrientation() const { return mOrientation; }

    protected:
        virtual void DrawImpl() = 0;
        virtual void UpdateImpl(float dt) = 0;


    private:

        vec3 mPosition;
        vec3 mVelocity;
        quat mOrientation;
        vec3 mScale;
    };

}

#endif //OFAPP_OBJECT_H
