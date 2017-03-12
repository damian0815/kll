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
    params.mNeighboursToConsider = 7
    params.mLocalCohesion = 1
    params.mGlobalCohesion = 0.0
    params.mSeparation = 0.001
    params.mSeparationThreshold = 0.01
    params.mMatchVelocity = 1
    params.mStayInOnePlace = 0.2
    params.mDampingFactor = 0.0
    params.mMinSpeed = 1.6
    params.mMaxSpeed = 1.8
    params.mFlockCenter = kll.gvec3(0, 0.0, -6)
    local flock = gEnvironment:AddFlock(1000, params)

    o = {flock=flock}
    setmetatable(o, self)
    self.__index = self
    return o
end


