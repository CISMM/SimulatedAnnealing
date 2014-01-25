// cputime.cpp	implementation of CPUTime class

// Updated to 2003 C++ by Shawn Waldon in 2014

static const char rcsid[] = "@(#)cputime.c++	1.7 11:13:35 5/14/93   EFC";

#include <sys/time.h>
#include <sys/resource.h>

#include <cputime.hpp>

#include <iomanip>

CPUTime::operator double()
{
	get_cpu_time();

	return usertime + systime;
}

void CPUTime::report(const char *label)
{
	get_cpu_time();

	if ( no_print )
		return;

	if ( label == NULL )
		my_os << "CPU";
	else
		my_os << label;

	my_os << " time (sec):\t";
	// my_os << setiosflags(ios::fixed)

	int old_precision = my_os.precision(4);

	my_os << usertime << "u  " << systime << "s\ttotal: "
          << (usertime + systime) << std::endl;
  my_os.precision( old_precision );
  my_os.flush();

}

void CPUTime::get_cpu_time()
{
    struct rusage usage;

    getrusage(RUSAGE_SELF, &usage);

    usertime = (double)usage.ru_utime.tv_sec +
            (double)usage.ru_utime.tv_usec / 1000000.;
    systime = (double)usage.ru_stime.tv_sec +
            (double)usage.ru_stime.tv_usec / 1000000.;

}






