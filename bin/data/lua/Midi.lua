--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 08/01/2017
-- Time: 14:13
-- To change this template use File | Settings | File Templates.
--

Midi = {}

function Midi:new()
    o = {}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Midi:OnMidiNoteOn(channel, pitch, velocity)
    if channel == 1 then
        self:HandleSyncNote(pitch, velocity)
    elseif channel == 2 then
        self:HandleDrumNote(pitch, velocity)
    elseif channel == 3 then
        self:HandleBassNoteOn(pitch, velocity)
    elseif channel == 4 then
        self:HandleVocalNoteOn(pitch, velocity)
     else
        print(string.format("lua unhandled midi note on ch %i: pitch %i, velocity %i", channel, pitch, velocity));
    end

end

function Midi:OnMidiNoteOff(channel, pitch, velocity)
    if channel == 3 then
        self:HandleBassNoteOff(pitch, velocity)
    elseif channel == 4 then
        self:HandleVocalNoteOff(pitch, velocity)
    end
end


function Midi:HandleSyncNote(pitch, velocity)
    if (pitch < 71) then
        gScenes:SetSceneIndex(pitch)

    end
end

function Midi:HandleDrumNote (pitch, velocity)
    local scene = gScenes:GetScene()
    if pitch == 60 then
        scene:HandleKick()
    elseif pitch == 71 then
        scene:HandleHiHat()
    elseif pitch == 64 then
        scene:HandleSnare()
    end
end

function Midi:HandleBassNoteOn(pitch, velocity)
    local scene = gScenes:GetScene()
    scene:HandleBassNoteOn(pitch, velocity)
end

function Midi:HandleBassNoteOff(pitch, velocity)
    local scene = gScenes:GetScene()
    scene:HandleBassNoteOff(pitch, velocity)
end

function Midi:HandleVocalNoteOn(pitch, velocity)
    local scene = gScenes:GetScene()
    scene:HandleVocalNoteOn(pitch, velocity)
end

function Midi:HandleVocalNoteOff(pitch, velocity)
    local scene = gScenes:GetScene()
    scene:HandleVocalNoteOff(pitch, velocity)
end

