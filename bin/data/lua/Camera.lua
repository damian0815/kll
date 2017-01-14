--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 13/01/2017
-- Time: 19:43
-- To change this template use File | Settings | File Templates.
--

Camera = {}

function Camera:new()
    o = {angle=0, targetAngle=0, rotationStartAngle=0}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Camera:Update(dt)

    if self.targetAngle ~= self.angle then
        local phase = kll.Clock.Get():GetPhase(self.beatCount)
        local span = self.targetAngle - self.rotationStartAngle
        self.angle = self.rotationStartAngle + phase * span
        --print("interpolated rotation to " .. self.angle)
    end

    local q = kll.gquat(self.angle, kll.gvec3(0, 0, 1))
    gEnvironment:GetCamera():SetOrientation(q)
end


function Camera:SetAngle(angle)
    self.angle = angle
    self.targetAngle = angle
end

function Camera:StartRotationToAngle(targetAngle, beatCount)
    self.rotationStartAngle = self.angle
    self.targetAngle = targetAngle
    self.beatCount = beatCount
end

