// $Id$ -*- C++ -*-
// Provide macros for compiler attributes.

// Copyright (C) 2003 Free Software Foundation, USA.
// Written by Arnaud Desitter.
// 
// This file is part of DDD.
// 
// DDD is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
// 
// DDD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with DDD -- see the file COPYING.
// If not, see <http://www.gnu.org/licenses/>.
// 
// DDD is the data display debugger.
// For details, see the DDD World-Wide-Web page, 
// `http://www.gnu.org/software/ddd/',
// or send a mail to the DDD developers <ddd@gnu.org>.

#ifndef _DDD_attribute_h
#define _DDD_attribute_h

#include "config.h"

#if HAVE_ATTRIBUTE_NORETURN
# define ATTRIBUTE_NORETURN __attribute__((noreturn))
#else
# define ATTRIBUTE_NORETURN
#endif

#if HAVE_BUILTIN_EXPECT
# ifndef likely
#  define likely(x) (__builtin_expect(!!(x),1))
# endif
# ifndef unlikely
#  define unlikely(x) (__builtin_expect(!!(x),0))
# endif
#else
# define likely(x) (x)
# define unlikely(x) (x)
#endif

#endif // _DDD_attribute_h
// DON'T ADD ANYTHING BEHIND THIS #endif
