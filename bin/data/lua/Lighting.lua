--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 08/01/2017
-- Time: 14:23
-- To change this template use File | Settings | File Templates.
--

Lighting = {}

function Lighting:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.intensity = 1
    return o
end

function Lighting:InjectEnergy(amount)
    self.intensity = math.max(self.intensity + amount, 1)

    local light = gEnvironment:GetLight()
    light:SetIntensity(self.intensity)
end

function Lighting:SetLightPosition(p)
    local light = gEnvironment:GetLight()
    light:SetPosition(p)
end

function Lighting:Update(dt)
    fade = 0.001
    self.intensity = math.max(0.3, self.intensity * (fade ^ dt))

    local light = gEnvironment:GetLight()
    light:SetIntensity(self.intensity)
end
