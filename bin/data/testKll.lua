
print("hello from inside lua")

environment = kll.Environment.GetInstance()
environment:PrintHello()

function setup()
end

function update()
end


function OnMidiNote(channel, pitch, velocity)
    print(string.format("lua midi 3 note on ch %i: pitch %i, velocity %i", channel, pitch, velocity));
end

