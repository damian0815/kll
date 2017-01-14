--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 31/12/16
-- Time: 09:46
-- To change this template use File | Settings | File Templates.
--

Behaviours = {}

function Behaviours:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    self.mBehaviours = {}
    return o
end


function Behaviours:Update(dt)

    local environment = kll.Environment.GetInstance()
    local behavioursToDestroy = {}
    for index, behaviour in ipairs(self.mBehaviours) do

        if environment:HasObject(behaviour:GetTarget()) then
            behaviour:Update(dt)
            if behaviour:ShouldObjectBeDestroyed() then
                environment:RemoveObject(behaviour:GetTarget())
            end
        else
            table.insert(behavioursToDestroy, 1, index)
        end
    end

    for k, behaviourIndex in ipairs(behavioursToDestroy) do
        table.remove(self.mBehaviours, behaviourIndex)
    end

end

function Behaviours:AddBehaviour(b)
    table.insert(self.mBehaviours, b)
end



