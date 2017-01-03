
print("hello from inside lua")

environment = kll.Environment.GetInstance()
environment:PrintHello()

require "Behaviours"
require "FallBehaviour"
require "FadeBehaviour"
require "AddRotationBehaviour"
gBehaviours = Behaviours:new();

function setup()
end

function update(dt)
    gBehaviours:Update(dt)
end

function OnMidiNote(channel, pitch, velocity)


    if channel == 2 then
        HandleDrumNote(pitch, velocity)
    elseif channel == 3 then
        HandleBassNote(pitch, velocity)
    else
        print(string.format("lua unhandled midi note on ch %i: pitch %i, velocity %i", channel, pitch, velocity));
    end


end


function HandleDrumNote(pitch, velocity)

    if pitch == 60 then
        -- kick
        local block = environment:AddBlock(kll.gvec3(0,0.2,0), kll.gvec3(1.2,0.03,0.03))
        block:SetVelocity(kll.gvec3(0,0,0))

        local fall = FallBehaviour:new(block, kll.gvec3(0, 3, 0))
        gBehaviours:AddBehaviour(fall)

        local addRotation = AddRotationBehaviour:new(block, kll.gvec3(0, 3*kll.RandomNormal(), 2*kll.RandomNormal()))
        gBehaviours:AddBehaviour(addRotation)
    elseif pitch == 71 then
        -- hihat

        local phase = kll.Clock.Get():GetPhase(8)

        local center = kll.gvec3(0.5 * math.cos(phase*math.pi*2), 0.5, 0.0)
        local block = environment:AddBlock(center, kll.gvec3(0.1,0.01, 0.01))
        block:SetVelocity(kll.gvec3(0,0,1))

        --local screenCenter = kll.gvec3(0,0,0)
        --local towardsCenter = kll.Normalize(screenCenter - center)
        local flyAway = FallBehaviour:new(block, kll.gvec3(0,-4,0))
        gBehaviours:AddBehaviour(flyAway)


    elseif pitch == 64 then
        -- snare

        local size = kll.RandomNormal(0.6, 0.8);
        local section = environment:AddTunnelSection(0.3, size, 10, 3)

        local fade = FadeBehaviour:new(section, 0.00001)
        gBehaviours:AddBehaviour(fade)

    end
end

function HandleBassNote(pitch, velocity)

    local height = kll.RandomNormal(0.02, 0.03);
    local width = kll.RandomNormal(0.05, 0.1);
    local depth = 0.4

    local y = 1-((pitch-30)/20)

    print("p " .. pitch .. "  v " .. velocity)
    local block = environment:AddBlock(kll.gvec3(0,y,0), kll.gvec3(width, height, depth))
    block:SetVelocity(kll.gvec3(0,0,1))

    gBehaviours:AddBehaviour(fade)


end
