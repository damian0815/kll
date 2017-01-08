
%module kll
%{
    #include "../kll/kll.h"
    #include "../kll/Objects/Block.h"
    #include "../kll/Objects/Object.h"
    #include "../kll/Objects/TunnelSection.h"
    #include "../kll/Engine/Environment.h"
    #include "../kll/Behaviours/ImplodeBehaviour.h"
    #include "../kll/Behaviours/Behaviour.h"
    #include "../kll/Engine/BehaviourPool.h"
    #include "../kll/Engine/gvec3.h"
    #include "../kll/Engine/Clock.h"
    #include "../kll/Engine/Light.h"

    using namespace kll;
%}

%include <stl.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>

%include "../kll/kll.h"
%include "../kll/Objects/Object.h"
%include "../kll/Objects/Block.h"
%include "../kll/Objects/TunnelSection.h"
%include "../kll/Engine/Environment.h"
%include "../kll/Behaviours/Behaviour.h"
%include "../kll/Behaviours/ImplodeBehaviour.h"
%include "../kll/Engine/BehaviourPool.h"
%include "../kll/Engine/gvec3.h"
%include "../kll/Engine/Clock.h"
%include "../kll/Engine/Light.h"

