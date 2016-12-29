
%module kll
%{
    #include "../kll/Engine/Environment.h"
    #include "../kll/Behaviours/ImplodeBehaviour.h"
    #include "../kll/Behaviours/Behaviour.h"
    #include "../kll/Engine/gvec3.h"

    using kll::Block;
%}

%include <stl.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>

%include "../kll/Engine/Environment.h"
%include "../kll/Behaviours/Behaviour.h"
%include "../kll/Behaviours/ImplodeBehaviour.h"
%include "../kll/Engine/gvec3.h"
