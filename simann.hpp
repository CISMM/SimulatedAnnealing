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
  double (*function)(double*, void*);
  void* data;

  // Constructors:
  CostFunction() : function(NULL), data(NULL) {}
  CostFunction(double (*f)(double*, void*), void* d = NULL) : function(f), data(d)
  {
  }

  double operator()(double* f) { return function(f, data); }
};

//typedef double (*CostFunction)(double*);

class SimAnneal
{
 private:
  RUniform uniform;
  CostFunction func;
  int dimension, maxit, ddwell;
  int err;
  double* x, *xnew, *xbest;
  double dt;      // temperature increment to use when melting
  double c_jump;  // phase transition step size
  double rrange;
  double K, rho, t0, tscale, y, ybest;
  int equilibrate(const double t, const int n);

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

  double melt(const int iters = -1);
  double anneal(const int iters = -1);

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
  double Boltzmann(const double k = -1.0)
  {
    if (k > 0.0) K = k;
    return K;
  }

  double learning_rate(const double r = -1.0)
  {
    if (r > 0.0) rho = r;
    return rho;
  }
  double temperature(const double t = -1.0)
  {
    if (t >= 0.0) t0 = t;
    return t0;
  }
  double jump(const double j = -1.0)
  {
    if (j > 0.0) c_jump = j;
    return c_jump;
  }
  double range(const double r = -1.0)
  {
    if (r > 0.0) rrange = r;
    return rrange;
  }
  void initial(const double* xinit);
  void current(double* xcur);
  void optimum(double* xopt);
};

#endif
