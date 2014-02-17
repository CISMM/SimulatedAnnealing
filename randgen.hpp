// randgen.hpp		A random number generator base class
//
//                      (c) Copyright 1994, Everett F. Carter Jr.
//                      Permission is granted by the author to use
//			this software for any application provided this
//			copyright notice is preserved.
//
// rcsid: @(#)randgen.hpp	1.5 %U 7/25/94   EFC

// Updated to 2003 C++ standard by Shawn Waldon in 2014

#ifndef RANDGEN_HPP_
#define RANDGEN_HPP_ 1.5

#include <iosfwd>
#include <limits>

#ifndef Real
#define Real float
#endif

class RandomGenerator
{
 protected:
  static std::ostream* ostr;
  RandomGenerator() {}

 public:
  virtual ~RandomGenerator() {}

  virtual long seed(const long ik = 0) = 0;
  virtual Real ranf() = 0;           // 0.0 .. 1.0 base generator for others
  virtual unsigned long int rani();  // 0..n integer base generator

  // attach the output stream for error messages,
  // (cerr is used if this is not ever used)
  static void attach(std::ostream& os) { ostr = &os; }
};

inline unsigned long int RandomGenerator::rani()
{
  return (unsigned long)(std::numeric_limits< unsigned long >::max() * ranf());
}

#endif
