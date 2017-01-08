//
// Created by Damian Stewart on 10/12/2016.
//

#ifndef OFAPP_OBJECT_H
#define OFAPP_OBJECT_H

#include <glm/gtc/quaternion.hpp>
#include "../kll.h"
#include "../Engine/gvec3.h"

using glm::quat;

namespace kll {

    class Object
    {
    public:
        Object();
        Object(vec3 initialPos): Object() { mPosition = initialPos; }

        virtual ~Object() {};

        void Draw();
        void Update(float dt);

        const vec3& GetScale() const { return mScale; }
        void SetScale(vec3 scale) { mScale = scale; }

        // explict namespace is required for Lua bindings
        const kll::gvec3 GetVelocity() const { return mVelocity; }
        void SetVelocity(const kll::gvec3 &velocity) { mVelocity = velocity; }

        const kll::gquat GetOrientation() const { return mOrientation; }
        void SetOrientation(const kll::gquat &q) { mOrientation = q; }

        float GetAlpha() const { return mAlpha; }
        void SetAlpha(float alpha) { mAlpha = alpha; }

    protected:

        virtual void DrawImpl() = 0;
        virtual void UpdateImpl(float dt) = 0;

        virtual bool GetShouldUseMaterial() { return true; }

    private:
        ofMaterial mMaterial;

        float mAlpha = 1;

        vec3 mPosition;
        vec3 mVelocity;
        quat mOrientation;
        vec3 mScale;

    };

}

#endif //OFAPP_OBJECT_H
