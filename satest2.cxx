/* satest2.c++
   Simple experiments with simulated annealing

   find the nonlinear least squares optimum solution

   usage:   satest2 input.file

*/

// Updated to 2003 C++ standard by Shawn Waldon in 2014

static const char rcsid[] = "@(#)satest2.c++	1.1 09:50:25 10/30/92   EFC";

#define PROGRAM "satest2"

#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "simann.hpp"

#include <barray.hpp>
#include <cputime.hpp>
#include <random.hpp>

// #define MELT_ONLY
// #define EQUIL_ONLY

#define MAXIT 400

double lambda = 0.0; /* derivative weight factor */

BasicArray x, y;
int n;

double energy(double *,void*v=NULL);  // the cost function

double func(double, double, double), fprime_a(double, double, double);
double fprime_b(double, double, double);

int main(int argc, char **argv)
{
  int i;
  double z, t0, t;
  double a[2];

  // first read in the dataset
  std::filebuf fbuf;
  if (!fbuf.open(argv[1], std::ios::in)) {
    std::cerr << PROGRAM << " unable to open input file " << argv[1] << std::endl;
    exit(1);
  }
  std::istream fin(&fbuf);

  // read x, y pairs in
  i = 0;
  while (!fin.eof()) {
    fin >> z;
    if (fin.eof() || fin.fail()) break;
    x.resize(++i);
    y.resize(i);
    x[i - 1] = z;
    fin >> z;
    y[i - 1] = z;
  }
  n = i;

  std::cerr << n << " points read for analysis\n";

  CPUTime *cpu = new CPUTime;

  SimAnneal sa(CostFunction(energy), 2);

  if (!sa) {
    std::cerr << "problem initializing SimAnneal object\n";
    exit(1);
  }

  RUniform uniform;

  // now start up the estimation
  for (i = 0; i < 2; i++) {
    a[i] = uniform.number(0.0, 10.0);
  }

  z = energy(a);

  sa.initial(a);  // set initial condition

  sa.Boltzmann(0.5);
  // sa.jump( 150.0 );

  std::cout << "Boltzman constant: " << sa.Boltzmann()
            << "\tlearning rate: " << sa.learning_rate() << '\n';
  std::cout << "initial values: ";
  for (i = 0; i < 2; i++) std::cout << a[i] << '\t';
  std::cout << "    (energy = " << z << ")" << std::endl;

  sa.melt();  // melt the system

  sa.current(a);
  z = energy(a);

  std::cout << "melt values   : ";
  for (i = 0; i < 2; i++) std::cout << a[i] << '\t';
  std::cout << "    (energy = " << z << ")" << std::endl;

#ifdef MELT_ONLY
  t0 = sa.temperature();
#else
  /* make it a bit warmer than melting temperature */
  t0 = 1.2 * sa.temperature();

  sa.temperature(t0);

#ifndef EQUIL_ONLY
  t = sa.anneal(MAXIT);
  sa.current(a);
#endif

#endif

  z = energy(a);

  std::cout << "initial temperature: " << t0 << '\t';
  std::cout << "final temperature: " << t << '\n';

  std::cout << "Estimated minumum at: ";
  for (i = 0; i < 2; i++) std::cout << a[i] << '\t';
  std::cout << "    (energy = " << z << ")\n";
  ;

  sa.optimum(a);
  z = energy(a);

  std::cout << "Best minumum at: ";
  for (i = 0; i < 2; i++) std::cout << a[i] << '\t';
  std::cout << "    (energy = " << z << ")\n";
  ;

  delete cpu;

  return 0;
}

double func(double x, double a, double b)
{
  double f;

  f = (1.0 - x * x / (a * a)) * exp(-x * x / (b * b));

  return f;
}

double fprime_a(double x, double a, double b)
{
  double f;

  f = 2 * x * x * exp(-x * x / (b * b)) / (a * a * a);

  return f;
}

double fprime_b(double x, double a, double b)
{
  double f;

  f = func(x, a, b) * 2.0 * x * x / (b * b * b);

  return f;
}

/* evaluate the sum squared error, the "energy" */
double energy(double *a,void*)
{
  int i;
  double sum = 0.0, val;

  for (i = 0; i < n; i++) {
    val = y[i] - func(x[i], a[0], a[1]);
    sum += val * val + lambda * (fabs(fprime_a(x[i], a[0], a[1])) +
                                 fabs(fprime_b(x[i], a[0], a[1])));
  }

  return sum;
}
