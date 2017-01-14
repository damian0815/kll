--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 13/01/2017
-- Time: 23:54
-- To change this template use File | Settings | File Templates.
--

SectionB = {}

function SectionB:new()
    o = {activeBassBlocks={}}
    setmetatable(o, self)
    self.__index = self
    return o
end

function SectionB:HandleKick()
end

function SectionB:HandleHiHat()
end

function SectionB:HandleSnare()

    --local size = kll.RandomNormal(0.6, 0.8);
    --local length = 10
    --local section = gEnvironment:AddTunnelSection(length, size, 32, 5)
    --section:SetPosition(kll.gvec3(0,0,-1))

    --section:SetAlpha(0.5)

    local pos = kll.gvec3(-0.6,0,-1)
    local size = kll.gvec3(0.2, 8, 0.01)
    local block = gEnvironment:AddBlock(pos, size)
    block:SetLightingEnabled(false)
    block:SetShininess(0)
    --block:SetAlpha(0.5)

    local fade = FadeBehaviour:new(block, 0.0001)
    gBehaviours:AddBehaviour(fade)

    gLighting:InjectEnergy(1)
end

function SectionB:HandleBassNoteOn(pitch, velocity)
    local height = 0.01
    local depth = 0.03
    local width = kll.RandomNormal(0.3, 0.33);
    local size = kll.gvec3(height, width, depth)
    size = size*4;

    local startPitch = 55
    local pitchYScale = -1/70
    local x = ((pitch-startPitch)*pitchYScale)
    local z = 0

    --print("p " .. pitch .. "  v " .. velocity)
    local block = gEnvironment:AddBlock(kll.gvec3(x,0,z), size)
    --block:SetVelocity(kll.gvec3(0,0,1))

    local fall = FallBehaviour:new(block, kll.gvec3(0,0,4))
    gBehaviours:AddBehaviour(fall)

    --local rotate = AddRotationBehaviour:new(block, kll.gvec3(0, 10*kll.RandomNormal(), 0))
    --gBehaviours:AddBehaviour(rotate)

    local fade = FadeBehaviour:new(block, 0.02)
    gBehaviours:AddBehaviour(fade)

    self.activeBassBlocks[pitch] = block

end

function SectionB:Update(dt)
    for index,block in pairs(self.activeBassBlocks) do
        if gEnvironment:HasObject(block) then
            local d = block:GetScaledDimensions()
            local GROW_SPEED = 3
            d.z = d.z + dt * GROW_SPEED
            block:SetScaledDimensions(d)
        end
    end
end

function SectionB:HandleBassNoteOff(pitch, velocity)
    self.activeBassBlocks[pitch] = nil
end