
print("hello from inside lua")

environment = kll.Environment.GetInstance()
environment:PrintHello()


function update()
end


function OnMidiNote(channel, pitch, velocity)
    print(string.format("lua midi note on ch %i: pitch %i, velocity %i", channel, pitch, velocity));
end

