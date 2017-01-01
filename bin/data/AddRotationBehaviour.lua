--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 01/01/17
-- Time: 13:50
-- To change this template use File | Settings | File Templates.
--

require "Math"
require "Vector3"
require "Quaternion"
require "GLMUtils"

AddRotationBehaviour = {}

function AddRotationBehaviour:new(target, angularVelocity)
    o = {target=target, angularVelocity=angularVelocity}
    setmetatable(o, self)
    self.__index = self
    return o
end

function AddRotationBehaviour:Update(dt)

    local deltaRotation = kll.gquat(self.angularVelocity * dt)

    local newRotation = self.target:GetOrientation() * deltaRotation

    self.target:SetOrientation(newRotation)

end

function AddRotationBehaviour:ShouldObjectBeDestroyed()
    return false
end

function AddRotationBehaviour:GetTarget()
    return self.target
end


