cmake_minimum_required(VERSION 2.8)

Project(simanneal_cpp)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

SET(simanneal_library_sources
  barray.cxx
  cputime.cxx
  errorstream.cxx
  r250.cxx
  randgen.cxx
  random.cxx
  registrar.cxx
  rndlcg.cxx
  simann.cxx
)
SET(simanneal_library_headers
  barray.hpp
  cputime.hpp
  errorstream.hpp
  r250.hpp
  randgen.hpp
  random.hpp
  registrar.hpp
  rndlcg.hpp
  scalar.hpp
  simann.hpp
)

SET(test1_src
  satest1.cxx
)

SET(test2_src
  satest2.cxx
)

ADD_LIBRARY(simann ${simanneal_library_sources} ${simanneal_library_headers})

ADD_EXECUTABLE(satest1 ${test1_src})
TARGET_LINK_LIBRARIES( satest1
  simann
)

ADD_EXECUTABLE(satest2 ${test2_src})
TARGET_LINK_LIBRARIES( satest2
  simann
)

INSTALL( FILES ${simanneal_library_headers} DESTINATION include/simann)
INSTALL( TARGETS simann DESTINATION lib)
