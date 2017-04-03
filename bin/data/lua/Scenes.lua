--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 13/01/2017
-- Time: 21:04
-- To change this template use File | Settings | File Templates.
--

require "Scenes/SectionA"
require "Scenes/SectionB"

Scenes = {}

function Scenes:new()
    o = {sceneIndex=-1, sectionA = SectionA:new(), sectionB = SectionB:new()}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Scenes:SetSceneIndex(s)
    local oldSceneIndex = self.sceneIndex
    self.sceneIndex = s
    print("scene " .. s .. " (old " .. oldSceneIndex)

    if s <= 4 then
        gCamera:SetAngle(0)
    elseif s == 5 then
        gCamera:StartRotationToAngle(math.pi/2, 16)
    else
        gCamera:SetAngle(math.pi/2)
    end

    if oldSceneIndex ~= self.sceneIndex then
        if s == 0 then
            self:GetScene():Enter()
        elseif s == 6 then
            self:GetScene():Enter()
        end
    end
end

function Scenes:GetSceneIndex()
    return self.sceneIndex
end


function Scenes:GetScene()
    if self.sceneIndex <= 5 then
        return self.sectionA
    else
        return self.sectionB
    end
end

function Scenes:Update(dt)
    self.sectionA:Update(dt)
    self.sectionB:Update(dt)
end


