// This class is a replacement for the original erstream.cxx which was too
// dependent on older non-standard C++ features to update
//
// (c) Copyright 2014, Shawn Waldon.
#include "errorstream.hpp"

#include <cstring>

ErrorStream::ErrorStream(std::ostream &s) : prog(NULL), stream(s) {}

ErrorStream::ErrorStream(const char *title, std::ostream &s)
    : prog(NULL), stream(s)
{
  prog = new char[std::strlen(title) + 1];
  std::strcpy(prog, title);
}

ErrorStream::ErrorStream(const ErrorStream &er) : prog(NULL), stream(er.stream)
{
  if (er.prog) {
    prog = new char[std::strlen(er.prog) + 1];
    std::strcpy(prog, er.prog);
  }
}

ErrorStream::~ErrorStream()
{
  if (prog) {
    delete[] prog;
  }
}

std::ostream &ErrorStream::fatal()
{
  stream << "Fatal erorr in " << prog << ": ";
  return stream;
}

std::ostream &ErrorStream::fail()
{
  stream << "Failure in " << prog << ": ";
  return stream;
}

std::ostream &ErrorStream::warning()
{
  stream << "Warning from " << prog << ": ";
  return stream;
}
