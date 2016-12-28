
%module kll
%{
    #include "../kll/Environment.h"

    using kll::Block;
%}

%include <stl.i>
%include <std_string.i>
%include <std_vector.i>
%include <std_map.i>

%include "../kll/Environment.h"
