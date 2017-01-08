
require "Lighting"
require "Behaviours"
require "Midi"

print("hello from inside lua")

gEnvironment = kll.Environment.GetInstance()
gEnvironment:PrintHello()


gBehaviours = Behaviours:new()
gLighting = Lighting:new()

gLighting:SetLightPosition(kll.gvec3(1,10,1))

function setup()
end

function update(dt)
    gBehaviours:Update(dt)
    gLighting:Update(dt)
end



