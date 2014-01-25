// simanneal.hpp	A general purpose Simulated Annealing Class
//	This version allows vector data

//                      (c) Copyright 1994, Everett F. Carter Jr.
//                      Permission is granted by the author to use
//			this software for any application provided this
//			copyright notice is preserved.

// Updated to 2003 C++ standard by Shawn Waldon in 2014

// rcsid: @(#)simann.hpp	1.4 15:02:11 7/25/94   EFC

#ifndef SIM_ANNEAL_HPP_
#define SIM_ANNEAL_HPP_ 1.4

#include <random.hpp>

#ifndef PI
#define PI 3.141592653589793
#endif

// Added to allow a more object oriented cost function to be passed in without
// the need for global data accessible to the cost function
struct CostFunction
{
 public:
  float (*function)(float*, void*);
  void* data;

  // Constructors:
  CostFunction() : function(NULL), data(NULL) {}
  CostFunction(float (*f)(float*, void*), void* d = NULL) : function(f), data(d)
  {
  }

  float operator()(float* f) { return function(f, data); }
};

//typedef float (*CostFunction)(float*);

class SimAnneal
{
 private:
  RUniform uniform;
  CostFunction func;
  int dimension, maxit, ddwell;
  int err;
  float* x, *xnew, *xbest;
  float dt;      // temperature increment to use when melting
  float c_jump;  // phase transition step size
  float rrange;
  float K, rho, t0, tscale, y, ybest;
  int equilibrate(const float t, const int n);

 public:
  SimAnneal()
      : func(NULL),
        dimension(1),
        maxit(400),
        ddwell(20),
        dt(0.1),
        c_jump(100.0),
        rrange(PI / 2.0),
        K(1.0),
        rho(0.5),
        t0(0.0),
        tscale(0.1)
  {
  }
  SimAnneal(const CostFunction& f, const int d = 1);
  ~SimAnneal()
  {
    delete[] x;
    delete[] xnew;
    delete[] xbest;
  }

  int set_up(CostFunction f, const int d = 1);

  const int operator!() const { return err; }

  float melt(const int iters = -1);
  float anneal(const int iters = -1);

  int iterations(const int m = -1)
  {
    if (m > 0) maxit = m;
    return maxit;
  }
  int dwell(const int d = -1)
  {
    if (d > 0) ddwell = d;
    return ddwell;
  }
  float Boltzmann(const float k = -1.0)
  {
    if (k > 0.0) K = k;
    return K;
  }

  float learning_rate(const float r = -1.0)
  {
    if (r > 0.0) rho = r;
    return rho;
  }
  float temperature(const float t = -1.0)
  {
    if (t > 0.0) t0 = t;
    return t0;
  }
  float jump(const float j = -1.0)
  {
    if (j > 0.0) c_jump = j;
    return c_jump;
  }
  float range(const float r = -1.0)
  {
    if (r > 0.0) rrange = r;
    return rrange;
  }
  void initial(float* xinit);
  void current(float* xcur);
  void optimum(float* xopt);
};

#endif
