// $Id$ -*- C++ -*-
// Hash functions

/* 
Copyright (C) 1990 Free Software Foundation
    written by Doug Lea (dl@rocky.oswego.edu)

This file is part of the GNU C++ Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, see <http://www.gnu.org/licenses/>.
*/

char hash_rcsid[] = 
    "$Id$";

#include "hash.h"

/*
 some useful hash functions
*/

unsigned int hashpjw(const char* x) // From Dragon book, p436
{
    unsigned int h = 0;
    unsigned int g;

    while (*x != '\0')
    {
	h = (h << 4) + *x++;
	if ((g = h & 0xf0000000) != 0)
	    h = (h ^ (g >> 24)) ^ g;
    }
    return h;
}

unsigned int foldhash(double x)
{
    union 
    { 
	unsigned int i[2]; 
	double d; 
    } u;

    u.d = x;
    unsigned int u0 = u.i[0];
    unsigned int u1 = u.i[1]; 
    return u0 ^ u1;
}
