--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 12/03/2017
-- Time: 16:05
-- To change this template use File | Settings | File Templates.
--


Boids = {}


function Boids:new()
    local params = kll.FlockParams()
    params.mNeighboursToConsider = 30
    params.mLocalCohesion = 1
    params.mGlobalCohesion = 0.0
    params.mSeparation = 0.001
    params.mSeparationThreshold = 0.01
    params.mMatchVelocity = 0
    params.mStayInOnePlace = 0.2
    params.mDampingFactor = 0.0
    params.mMinSpeed = 0.4
    params.mMaxSpeed = 4
    params.mFlockCenter = kll.gvec3(0, 0.0, -6)
    local flock = gEnvironment:AddFlock(2000, params)

    local o = {flock=flock, params=params}
    setmetatable(o, self)
    self.__index = self
    return o
end

function Boids:SetFlockCenter(c, amount)
    self.params.mFlockCenter = c
    self.params.mStayInOnePlace = amount
    self.flock:SetParameters(self.params)
end

function Boids:SetCohesion(globalCohesion, localCohesion)
    self.params.mGlobalCohesion = globalCohesion
    self.params.mLocalCohesion = localCohesion
    self.flock:SetParameters(self.params)
end

