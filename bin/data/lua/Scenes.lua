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
    o = {sceneIndex=0, sectionA = SectionA:new(), sectionB = SectionB:new()}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Scenes:SetSceneIndex(s)
    self.sceneIndex = s
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


