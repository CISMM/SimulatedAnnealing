// barray.cpp	Implementation of bare Float,Double or Complex Array class

//                      (c) Copyright 1995, Everett F. Carter Jr.
//                      Permission is granted by the author to use
//			this software for any application provided this
//			copyright notice is preserved.

// Updated to 2003 C++ by Shawn Waldon in 2014

#include <barray.hpp>

static const char rcsid[] = "@(#)barray.c++	1.17 12:27:14 6/3/96   EFC";

// #define DEBUG
// #define DEBUG_RESIZE


BasicArray::BasicArray() : rsize(1), wdth(1), sze(1), n(sze)
{
	x = new scalar_type[ 1 ];

}

BasicArray::BasicArray(const int ni) : rsize(ni), wdth(ni+1), sze(ni), n(sze)
{
	x = new scalar_type[ ni ];

}

BasicArray::BasicArray(const BasicArray& f2) : n(sze)
{
	rsize = sze = f2.size();
	wdth = f2.wdth;
	
	x = new scalar_type[rsize];

	for (int k = 0; k < rsize; k++)
		x[k] = f2.x[k];

}

BasicArray::~BasicArray()
{
	        if ( x ) delete []x;

		x = NULL;
		rsize = sze = 0;                 
}

BasicArray& BasicArray::operator = (const BasicArray& f2)
{
	if ( this == &f2 )
		return *this;

	if ( x != NULL && rsize != f2.size() )
	{
		delete []x;

		rsize = f2.size();
		x = new scalar_type[rsize];
	}

	sze = rsize;
	// wdth = f2.wdth;


	for (int k = 0; k < rsize; k++)
		x[k] = f2.x[k];

	return *this;	
}

void BasicArray::trim(const int nsize)	// make the array SEEM to be smaller
{
	if ( nsize >= 0 && nsize <= rsize )
		sze = nsize;
}

void BasicArray::reset(const scalar_type val)
{
	for (int k = 0; k <sze; k++)
        		x[k] = val;
}

void BasicArray::resize(const int nsize)
{
	 int k, kend;

	sze = nsize;

	if ( nsize == rsize )
		return;			// nothing to do

	 kend = rsize;

	  if ( nsize < kend )			// keep the smaller size
			kend = nsize;

	  scalar_type *xn = new scalar_type[ nsize ];

	  if ( x )
	  {
	 	 // copy the old data
	 	 for (k = 0; k < kend; k++)
				xn[k] = x[k];

	  	delete []x;
	  }
	  else
		for (k = 0; k < nsize; k++)
				xn[k] = 0.0;

	  rsize = nsize;
	  x = xn;

	  wdth = rsize + 1;
}

int BasicArray::write(std::ofstream &ofs, int count,const int first) const
{
	if ( count < 0 )
		count = sze - first;

	if ( count <= 0 )
		return -1;

	ofs.write( (char *)&(x[first]), count * sizeof( scalar_type ) );

	if ( ofs.fail() )
		return -1;
	else
		return 0;
 
}

int BasicArray::read(std::ifstream &ifs, int count,const int first)
{

	if ( count < 0 )
		count = sze;

	if ( (first + count) > sze )
		resize( first+count );

 
	ifs.read( (char *)&(x[first]), count * sizeof( scalar_type ) );


	if ( ifs.fail() )
		return -1;
	else
		return 0;

}

std::istream& operator>> (std::istream& is, BasicArray& arry)
{
	scalar_type new_x;
	int k, kend;


	if ( is.eof() )
		return is;


	kend = arry.size();

	for (k = 0; k < kend; k++)
	{		
		is >> new_x;
		

 		// end of file reached, abort the read
		if ( is.eof() || is.fail() )
			return is;

		arry[k] = new_x;		
	}
	
	return is;
	
}

std::ostream& operator<< (std::ostream& os,const BasicArray& arry)
{
	int iend = arry.size();

	for (int i = 0; i < iend;  )
	{
		os << arry[i];
		if ( (++i % arry.wdth) == 0 )
				os << '\n';
		else
				os << "   "; 
	}

//	if ( (i % arry.wdth) != 0 )	os << '\n';
	
	return os;
	
}


int operator!=(const BasicArray &a,const BasicArray &b) //      int i = (a != b)
{
        if ( a.size() != b.size() )
                return 1;

        const int sz = a.size();
        int l = 1;

        for (int i = 0; i < sz; i++)
                        l = l && ( a[i] != b[i] );

        return l;

}

int operator==(const BasicArray &a,const BasicArray &b) //      int i = (a == b)
{
        if ( a.size() != b.size() )
                return 0;

        const int sz = a.size();
        int l = 1;

        for (int i = 0; i < sz; i++)
                        l = l && ( a[i] == b[i] );

        return l;

}






