--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 31/12/16
-- Time: 13:48
-- To change this template use File | Settings | File Templates.
--


FallBehaviour = {}

function FallBehaviour:new(target, gravity)
    o = {target=target, gravity=gravity, timer=0}
    setmetatable(o, self)
    self.__index = self
    return o
end

function FallBehaviour:Update(dt)
    self.timer = self.timer + dt

    local velocity = self.target:GetVelocity()
    local acceleration = self.gravity * dt
    velocity = velocity + acceleration

    self.target:SetVelocity(velocity)

end

function FallBehaviour:ShouldObjectBeDestroyed()
    local LIFETIME = 10
    return (self.timer > LIFETIME)
end

function FallBehaviour:GetTarget()
    return self.target
end

