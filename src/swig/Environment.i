
%module kll
%{
    #include "../kll/kll.h"
    #include "../kll/Objects/Block.h"
    #include "../kll/Objects/Flock.h"
    #include "../kll/Objects/Object.h"
    #include "../kll/Objects/TunnelSection.h"
    #include "../kll/Engine/Light.h"
    #include "../kll/Engine/KllCamera.h"
    #include "../kll/Engine/Environment.h"
    #include "../kll/Engine/gvec3.h"
    #include "../kll/Engine/Clock.h"

    using namespace kll;
%}

%include <stl.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>

%include "../kll/kll.h"
%include "../kll/Objects/Object.h"
%include "../kll/Objects/Block.h"
%include "../kll/Objects/Flock.h"
%include "../kll/Objects/TunnelSection.h"
%include "../kll/Engine/Light.h"
%include "../kll/Engine/KllCamera.h"
%include "../kll/Engine/Environment.h"
%include "../kll/Engine/gvec3.h"
%include "../kll/Engine/Clock.h"

