--
-- Created by IntelliJ IDEA.
-- User: damian
-- Date: 01/01/17
-- Time: 13:59
-- To change this template use File | Settings | File Templates.
--

require "Quaternion"

function GLMQuatFromLuaQuat(luaQuat)
    return kll.gquat(luaQuat.x, luaQuat.y, luaQuat.z, luaQuat.w)
end

function LuaQuatFromGLMQuat(glmQuat)
    return Quaternion(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w)
end

function GLMVec3FromLuaVec3(luaVec3)
    return kll.gvec(luaVec3.x, luaVec3.y, luaVec3.z)
end

function LuaVec3FromGLMVec3(glmVec3)
    return Vector3(glmVec3.x, glmVec3.y, glmVec3.z)
end
