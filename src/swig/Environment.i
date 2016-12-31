
%module kll
%{
    #include "../kll/Block.h"
    #include "../kll/Object.h"
    #include "../kll/Engine/Environment.h"
    #include "../kll/Behaviours/ImplodeBehaviour.h"
    #include "../kll/Behaviours/Behaviour.h"
    #include "../kll/Engine/BehaviourPool.h"
    #include "../kll/Engine/gvec3.h"

    using namespace kll;
%}

%include <stl.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>

%include "../kll/Object.h"
%include "../kll/Block.h"
%include "../kll/Engine/Environment.h"
%include "../kll/Behaviours/Behaviour.h"
%include "../kll/Behaviours/ImplodeBehaviour.h"
%include "../kll/Engine/BehaviourPool.h"
%include "../kll/Engine/gvec3.h"

