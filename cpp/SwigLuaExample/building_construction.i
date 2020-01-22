/* File : building_construction.i */

%module building_construction
%include "std_string.i"
%include "std_string.i"
%include "std_vector.i"

%{
#include "src/Floor.hpp"
#include "src/Skyscraper.hpp"

%}

/* Let's just grab the entire header files here */
%include "src/Skyscraper.hpp"
%include "src/Floor.hpp"