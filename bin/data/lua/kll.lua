
require "Lighting"
require "Behaviours"
require "Midi"
require "Camera"
require "Scenes"

print("hello from inside lua")

gEnvironment = kll.Environment.GetInstance()
gEnvironment:PrintHello()


gBehaviours = Behaviours:new()
gLighting = Lighting:new()
gMidi = Midi:new()
gCamera = Camera:new()
gScenes = Scenes:new()

gLighting:SetLightPosition(kll.gvec3(1,10,1))

function setup()
end

function update(dt)
    gBehaviours:Update(dt)
    gLighting:Update(dt)
    gCamera:Update(dt)
    gScenes:Update(dt)
end

function OnMidiNoteOn(channel, pitch, velocity)
    gMidi:OnMidiNoteOn(channel, pitch, velocity)
end

function OnMidiNoteOff(channel, pitch, velocity)
    gMidi:OnMidiNoteOff(channel, pitch, velocity)
end



