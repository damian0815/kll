
print("hello from inside lua")

environment = kll.Environment.GetInstance()
environment:PrintHello()

require "Behaviours"
require "FallBehaviour"
require "AddRotationBehaviour"
gBehaviours = Behaviours:new();

function setup()
end

function update(dt)
    gBehaviours:Update(dt)
end

function OnMidiNote(channel, pitch, velocity)
    print(string.format("lua midi 3 note on ch %i: pitch %i, velocity %i", channel, pitch, velocity));


    if channel == 2 then
        if pitch == 60 then
            local block = environment:AddBlock(kll.gvec3(0,0.5,0), kll.gvec3(1,0.03,0.03))

            local fall = FallBehaviour:new(block, kll.gvec3(0, 3, 0))
            gBehaviours:AddBehaviour(fall)

            local addRotation = AddRotationBehaviour:new(block, kll.gvec3(0, 3*kll.RandomNormal(), 2*kll.RandomNormal()))
            gBehaviours:AddBehaviour(addRotation)
        end
    end

end



