--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 13/01/2017
-- Time: 23:51
-- To change this template use File | Settings | File Templates.
--

require "FallBehaviour"
require "FadeBehaviour"

SectionA = {}

function SectionA:new()
    o = {activeBassBlocks = {}}
    setmetatable(o, self)
    self.__index = self
    return o
end


function SectionA:HandleKick()

    local pos = kll.gvec3(0,0.1,0)
    local block = gEnvironment:AddBlock(pos, kll.gvec3(0.5,0.05,0.05))
    block:SetVelocity(kll.gvec3(0,0,0))
    block:SetShininess(1)

    --local fall = FallBehaviour:new(block, kll.gvec3(0, 3, 0))
    --gBehaviours:AddBehaviour(fall)
    local towardScreen = FallBehaviour:new(block, kll.gvec3(0,0,5))
    gBehaviours:AddBehaviour(towardScreen)

    --local addRotation = AddRotationBehaviour:new(block, kll.gvec3(0, 3*kll.RandomNormal(), 2*kll.RandomNormal()))
    --gBehaviours:AddBehaviour(addRotation)
end

gHihatToggle = 1

function SectionA:HandleHiHat()

    local phase = kll.Clock.Get():GetPhase(8)

    local x = 0.2 * gHihatToggle;
    gHihatToggle = gHihatToggle * -1
    --local x = 0
    --local center = kll.gvec3(x, 0.5, 0.0)
    --local block = gEnvironment:AddBlock(center, kll.gvec3(0.1,0.001, 0.01))
    local pos = kll.gvec3(x, 0, -5)
    local size = kll.gvec3(0.001, 4, 0.01)
    local block = gEnvironment:AddBlock(pos, size)
    block:SetLightingEnabled(false)
    block:SetVelocity(kll.gvec3(0,0,0))

    --local screenCenter = kll.gvec3(0,0,0)
    --local towardsCenter = kll.Normalize(screenCenter - center)
    local flyAway = FallBehaviour:new(block, kll.gvec3(0,0,10))
    gBehaviours:AddBehaviour(flyAway)
end

function SectionA:HandleSnare()

    --local size = kll.RandomNormal(0.6, 0.8);
    --local length = 10
    --local section = gEnvironment:AddTunnelSection(length, size, 32, 5)
    --section:SetPosition(kll.gvec3(0,0,-1))

    --section:SetAlpha(0.5)

    local pos = kll.gvec3(0,0,-1)
    local size = kll.gvec3(1.0, 8, 0.01)
    local block = gEnvironment:AddBlock(pos, size)
    block:SetLightingEnabled(false)
    block:SetShininess(0)

    if gScenes:GetSceneIndex()==5 then
        local phase = kll.Clock.Get():GetPhase(16)
        local angle = -phase*math.pi
        local q = kll.gquat(angle, kll.gvec3(0,0,1))
        block:SetOrientation(q)
    end

    local fade = FadeBehaviour:new(block, 0.0001)
    gBehaviours:AddBehaviour(fade)

    gLighting:InjectEnergy(1)
end

function SectionA:HandleBassNoteOn(pitch, velocity)

    local height = 0.01*(velocity/100)
    local depth = kll.RandomNormal(0.02, 0.05)
    local width = 0.02
    if gScenes:GetSceneIndex() >= 3 then
        width = (velocity/100)*0.1
        height = 0.005
    end
    local size = kll.gvec3(width, height, depth)
    size = size*4;

    local startPitch = 50
    local pitchYScale = 1/100
    local y = ((pitch-startPitch)*pitchYScale)
    local z = 0

    --print("p " .. pitch .. "  v " .. velocity)
    local block = gEnvironment:AddBlock(kll.gvec3(0,y,z), size)
    block:SetAlpha(velocity/100)
    --block:SetVelocity(kll.gvec3(0,0,1))

    local fall = FallBehaviour:new(block, kll.gvec3(0,0,4))
    gBehaviours:AddBehaviour(fall)

    --local rotate = AddRotationBehaviour:new(block, kll.gvec3(0, 10*kll.RandomNormal(), 0))
    --gBehaviours:AddBehaviour(rotate)

    local fade = FadeBehaviour:new(block, 0.02)
    gBehaviours:AddBehaviour(fade)

    self.activeBassBlocks[pitch] = block

end

function SectionA:Update(dt)
    for index,block in pairs(self.activeBassBlocks) do
        if gEnvironment:HasObject(block) then
            local d = block:GetScaledDimensions()
            local GROW_SPEED = 2
            d.z = d.z + dt * GROW_SPEED
            block:SetScaledDimensions(d)
        end
    end
end

function SectionA:HandleBassNoteOff(pitch, velocity)
    self.activeBassBlocks[pitch] = nil
end

