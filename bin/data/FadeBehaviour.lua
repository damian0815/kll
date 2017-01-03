--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 03/01/17
-- Time: 11:21
-- To change this template use File | Settings | File Templates.
--

FadeBehaviour = {}

function FadeBehaviour:new(target, speed)
    o = {target=target, speed=speed, finished=false}
    setmetatable(o, self)
    self.__index = self
    return o
end

function FadeBehaviour:Update(dt)

    local newAlpha = self.target:GetAlpha() * (self.speed ^ dt)
    self.target:SetAlpha(newAlpha)

    local MIN_ALPHA = 0.001
    if newAlpha < MIN_ALPHA then
        self.finished = true
    end

end

function FadeBehaviour:ShouldObjectBeDestroyed()
    return self.finished
end

function FadeBehaviour:GetTarget()
    return self.target
end


