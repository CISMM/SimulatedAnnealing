// randgen.c++
//                      (c) Copyright 1994, Everett F. Carter Jr.
//                      Permission is granted by the author to use
//			this software for any application provided this
//			copyright notice is preserved.

// Updated to 2003 C++ standard by Shawn Waldon in 2014

static const char rcsid[] = "@(#)randgen.c++	1.5 14:38:16 7/25/94   EFC";

#include <iostream>
#include <randgen.hpp>

std::ostream* RandomGenerator::ostr = &std::cerr;

// everything else is either inline or pure virtual
