// $Id$ -*- C++ -*-
//

/* 
Copyright (C) 1988 Free Software Foundation
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

char regex_rcsid[] = 
    "$Id$";

#ifdef __GNUG__
#pragma implementation
#endif

/* 
  regex class implementation
 */

#ifdef __GNUG__
#pragma implementation
#endif

#include "config.h"
#include "regex.h"

#include <ctype.h>
#include <new.h>
#include <stdlib.h>
#include <iostream.h>
#include <string.h>

#if defined(HAVE_MEMSET) && !defined(HAVE_MEMSET_DECL)
extern "C" void *memset(void *s, int c, size_t n);
#endif

extern "C" {
#include <librx/rx.h>
}

regex::~regex()
{
    if (buf->buffer) 
	free(buf->buffer);
    if (buf->fastmap) 
	free(buf->fastmap);
    delete buf;
    delete reg;
}

regex::regex(const char* t, int fast, int bufsize, 
	     const char* transtable)
{
    int tlen = (t == 0)? 0 : strlen(t);
    buf = new re_pattern_buffer;
#ifdef HAVE_MEMSET
    memset (buf, 0, sizeof(re_pattern_buffer));
#else
    for (int p = 0; p < sizeof(re_pattern_buffer); p++)
	((char *)buf)[p] = '\0';
#endif
    reg = new re_registers;
    if (fast)
	buf->fastmap = (char*)malloc(256);
    else
	buf->fastmap = 0;
    buf->translate = (unsigned char*)transtable;
    if (tlen > bufsize)
	bufsize = tlen;
    buf->allocated = bufsize;
    buf->buffer = (char *)malloc(buf->allocated);
    const char* msg = re_compile_pattern((const char*)t, tlen, buf);
    if (msg != 0)
    {
	cerr << "regex: " << msg << "\n";
	abort();
    }
    else if (fast)
	re_compile_fastmap(buf);
}

int regex::match_info(int& start, int& length, int nth) const
{
    if ((unsigned)(nth) >= RE_NREGS)
	return 0;
    else
    {
	start = reg->start[nth];
	length = reg->end[nth] - start;
	return start >= 0 && length >= 0;
    }
}

int regex::search(const char* s, int len, int& matchlen, int startpos) const
{
    int matchpos, pos, range;
    if (startpos >= 0)
    {
	pos = startpos;
	range = len - startpos;
    }
    else
    {
	pos = len + startpos;
	range = -pos;
    }
    matchpos = re_search_2(buf, 0, 0, (char*)s, len, pos, range, reg, len);
    if (matchpos >= 0)
	matchlen = reg->end[0] - reg->start[0];
    else
	matchlen = 0;
    return matchpos;
}

int regex::match(const char*s, int len, int p) const
{
    if (p < 0)
    {
	p += len;
	if (p > len)
	    return -1;
	return re_match_2(buf, 0, 0, (char*)s, p, 0, reg, p);
    }
    else if (p > len)
	return -1;
    else
	return re_match_2(buf, 0, 0, (char*)s, len, p, reg, len);
}

int regex::OK() const
{
    // Can't verify much, since we've lost the original string
    int v = buf != 0;             // have a regex buf
    v &= buf->buffer != 0;        // with a pat
    if (!v)
        abort();
    return v;
}

/*
 some built-in Regular expressions
*/

const regex rxwhite("[ \n\t\r\v\f]+", 1);
const regex rxint("-?[0-9]+", 1);
const regex rxdouble("-?\\(\\([0-9]+\\.[0-9]*\\)\\|\\([0-9]+\\)\\|\\(\\.[0-9]+\\)\\)\\([eE][---+]?[0-9]+\\)?", 1, 200);
const regex rxalpha("[A-Za-z]+", 1);
const regex rxlowercase("[a-z]+", 1);
const regex rxuppercase("[A-Z]+", 1);
const regex rxalphanum("[0-9A-Za-z]+", 1);
const regex rxidentifier("[A-Za-z_][A-Za-z0-9_]*", 1);
