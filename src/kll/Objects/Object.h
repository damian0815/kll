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

    const float MAX_LIFETIME = 30.0f;

    class Object
    {
    public:
        Object();
        Object(vec3 initialPos): Object() { mPosition = initialPos; }

        virtual ~Object() {};

        void Draw();
        virtual void Update(float dt);

        ofMatrix4x4 GetTransformMatrix() const;

        const vec3& GetScale() const { return mScale; }
        void SetScale(vec3 scale) { mScale = scale; }

        // explict namespace is required for Lua bindings
        const kll::gvec3 GetVelocity() const { return mVelocity; }
        void SetVelocity(const kll::gvec3 &velocity) { mVelocity = velocity; }

        const kll::gquat GetOrientation() const { return mOrientation; }
        void SetOrientation(const kll::gquat &q) { mOrientation = q; }

        const kll::gvec3 GetPosition() const { return mPosition; }
        void SetPosition(const kll::gvec3 &p) { mPosition = p; }

        float GetAlpha() const { return mAlpha; }
        void SetAlpha(float alpha) { mAlpha = alpha; }

        float GetShininess() const { return mMaterial.getShininess(); }
        void SetShininess(float s) { mMaterial.setShininess(s); }

        bool GetLightingEnabled() { return mLightingEnabled; }
        void SetLightingEnabled(bool tf) { mLightingEnabled = tf; }

        virtual float GetRemainingLifetime() { return mRemainingLifetime; }

    protected:

        virtual void DrawImpl() = 0;
        virtual void UpdateImpl(float dt) = 0;

        virtual bool GetShouldUseMaterial() { return false; }

    private:
        ofMaterial mMaterial;

        bool mLightingEnabled = true;
        float mAlpha = 1;

        vec3 mPosition;
        vec3 mVelocity;
        quat mOrientation;
        vec3 mScale;

        ofMatrix4x4 mModelViewMatrix, mPreviousModelViewMatrix;

        float mRemainingLifetime = MAX_LIFETIME;
    };

}

#endif //OFAPP_OBJECT_H
