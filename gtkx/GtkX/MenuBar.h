 // -*- C++ -*-

// High-level GUI wrapper for Gtkmm.

// Copyright (C) 2007 Peter Wainwright <prw@ceiriog.eclipse.co.uk>
// 
// This file is part of GtkX.
// 
// GtkX is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// GtkX is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with GtkX -- see the file COPYING.
// If not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

// High level object-oriented wrapper must support Gtk and Motif.
// Unfortunately Motif widgets require parent and name arguments to
// the constructor, unlike the Gtk ones.  Motif (Xt) widgets cannot be
// reparented.  Therefore we need a constructor with extra arguments.
// A brief look at QT indicates that this will be required there as
// well.

#ifndef GTKX_MENUBAR_H
#define GTKX_MENUBAR_H

#include <GtkX/Container.h>
#include <gtkmm/menubar.h>

namespace GtkX {

    class MenuBar: public GtkX::Container, public Gtk::MenuBar {
    public:
	MenuBar(GtkX::Container &parent, const String &name="");
	MenuBar(Gtk::Container *parent, const String &name="");
	~MenuBar(void);
	Gtk::Widget *internal(void);
	// FIXME: Disambiguate inheritance from GtkX::Widget and Gtk class.
#include <GtkX/redirect.h>
    };

}

#endif // GTKX_MENUBAR_H
