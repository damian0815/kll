
print("hello from inside lua")

environment = kll.Environment.GetInstance()
environment:PrintHello()

function setup()
end

function update()
end


function OnMidiNote(channel, pitch, velocity)
    print(string.format("lua midi 3 note on ch %i: pitch %i, velocity %i", channel, pitch, velocity));


    if channel == 2 then
        if pitch == 60 then
            local block = environment:AddBlock(kll.gvec3(0,0.5,0), kll.gvec3(1,0.03,0.03))
            environment:AttachBehaviour(block, kll.ImplodeBehaviour(block, kll.gvec3(1,0,0)))
        end
    end

end

