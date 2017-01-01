--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 31/12/16
-- Time: 13:48
-- To change this template use File | Settings | File Templates.
--


FallBehaviour = {}

function FallBehaviour:new(target, gravity)
    o = {mTarget=target, gravity=gravity}
    setmetatable(o, self)
    self.__index = self
    return o
end

function FallBehaviour:Update(dt)

    local velocity = self.mTarget:GetVelocity()
    local acceleration = self.gravity * dt
    velocity = velocity + acceleration

    self.mTarget:SetVelocity(velocity)

end

function FallBehaviour:ShouldObjectBeDestroyed()
    return false
end

function FallBehaviour:GetTarget()
    return self.mTarget
end

