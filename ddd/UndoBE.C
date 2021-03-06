// $Id$ -*- C++ -*-
// Undo Buffer Entry

// Copyright (C) 1998 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@gnu.org>.
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

char UndoBufferEntry_rcsid[] = 
    "$Id$";

#include "UndoBE.h"

bool UndoBufferEntry::operator == (const UndoBufferEntry& entry) const
{
    if (&entry == this)
	return true;

    StringStringAssocIter iter1(*this);
    StringStringAssocIter iter2(entry);

    // This assumes both Assocs have the same ordering.
    while (iter1.ok() && iter2.ok())
    {
	if (iter1.key() != iter2.key())
	    return false;	// Differing keys
	if (iter1.value() != iter2.value())
	    return false;	// Differing values

	++iter1;
	++iter2;
    }

    if (iter1.ok())
	return false;		// Still keys/values in THIS
    if (iter2.ok())
	return false;		// Still keys/values in ENTRY

    return true;
}

int UndoBufferEntry::allocation() const
{
    StringStringAssocIter iter(*this);
    int alloc = sizeof(*this);

    while (iter.ok())
    {
	alloc += iter.key().allocation();
	alloc += iter.value().allocation();

	++iter;
    }

    return alloc;
}
