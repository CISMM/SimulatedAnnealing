// This class is a replacement for the original erstream.hpp which was too
// dependent on older non-standard C++ features to update
//
// (c) Copyright 2014, Shawn Waldon.
#ifndef ERRORSTREAM_H
#define ERRORSTREAM_H

#include <iostream>

class ErrorStream
{
 private:
  char* prog;
  std::ostream& stream;

 public:
  ErrorStream(std::ostream& s = std::cerr);
  ErrorStream(const char* title, std::ostream& s = std::cerr);
  ErrorStream(const ErrorStream& er);
  ~ErrorStream();

  std::ostream& fatal();
  std::ostream& fail();
  std::ostream& warning();
};

#endif  // ERRORSTREAM_H
