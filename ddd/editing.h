// $Id$ -*- C++ -*-
// DDD command-line actions and callbacks

// Copyright (C) 1996 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@gnu.org>.
// 
// This file is part of DDD.
// 
// DDD is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// DDD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with DDD -- see the file COPYING.
// If not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
// 
// DDD is the data display debugger.
// For details, see the DDD World-Wide-Web page, 
// `http://www.gnu.org/software/ddd/',
// or send a mail to the DDD developers <ddd@gnu.org>.

#ifndef _DDD_editing_h
#define _DDD_editing_h

#ifdef IF_MOTIF

#include <X11/Intrinsic.h>

#endif // IF_MOTIF

#include "gtk_wrapper.h"

#include "bool.h"
#include "strclass.h"

// Actions
extern void controlAct            (Widget, XEvent*, String*, Cardinal*);
extern void interruptAct          (Widget, XEvent*, String*, Cardinal*);
extern void commandAct            (Widget, XEvent*, String*, Cardinal*);
extern void processAct            (Widget, XEvent*, String*, Cardinal*);
extern void forward_characterAct  (Widget, XEvent*, String*, Cardinal*);
extern void backward_characterAct (Widget, XEvent*, String*, Cardinal*);
extern void beginning_of_lineAct  (Widget, XEvent*, String*, Cardinal*);
extern void end_of_lineAct        (Widget, XEvent*, String*, Cardinal*);
extern void set_lineAct           (Widget, XEvent*, String*, Cardinal*);
extern void delete_or_controlAct  (Widget, XEvent*, String*, Cardinal*);
extern void insert_source_argAct  (Widget, XEvent*, String*, Cardinal*);
extern void insert_graph_argAct   (Widget, XEvent*, String*, Cardinal*);
extern void next_tab_groupAct     (Widget, XEvent*, String*, Cardinal*);
extern void prev_tab_groupAct     (Widget, XEvent*, String*, Cardinal*);
extern void get_focusAct          (Widget, XEvent*, String*, Cardinal*);
extern void select_allAct         (Widget, XEvent*, String*, Cardinal*);
extern void isearch_nextAct       (Widget, XEvent*, String*, Cardinal*);
extern void isearch_prevAct       (Widget, XEvent*, String*, Cardinal*);
extern void isearch_exitAct       (Widget, XEvent*, String*, Cardinal*);
extern void popupAct              (Widget, XEvent*, String*, Cardinal*);


// Callbacks
extern void gdbModifyCB          (Widget, XtPointer, XtPointer);
extern void gdbMotionCB          (Widget, XtPointer, XtPointer);
#ifdef IF_MOTIF
extern void gdbChangeCB          (Widget, XtPointer, XtPointer);
#else // NOT IF_MOTIF
extern void gdbChangeCB          (SCROLLEDTEXT_P);
#endif // IF_MOTIF

#ifdef IF_MOTIF
extern void gdbNextCB            (CB_ARG_LIST_13(,));
extern void gdbPrevCB            (CB_ARG_LIST_13(,));
extern void gdbISearchNextCB     (CB_ARG_LIST_13(,));
extern void gdbISearchPrevCB     (CB_ARG_LIST_13(,));
extern void gdbISearchExitCB     (CB_ARG_LIST_13(,));
extern void gdbCompleteCB        (CB_ARG_LIST_13(,));
extern void gdbApplyCB           (CB_ARG_LIST_13(,));
extern void gdbApplySelectionCB  (CB_ARG_LIST_13(,));
#else // NOT IF_MOTIF
extern void gdbNextCB            (CB_ARG_LIST_1());
extern void gdbPrevCB            (CB_ARG_LIST_1());
extern void gdbISearchNextCB     (CB_ARG_LIST_1());
extern void gdbISearchPrevCB     (CB_ARG_LIST_1());
extern void gdbISearchExitCB     (CB_ARG_LIST_1());
extern void gdbCompleteCB        (CB_ARG_LIST_1());
extern void gdbApplyCB           (CB_ARG_LIST_1());
extern void gdbApplySelectionCB  (CB_ARG_LIST_NULL);
#endif // IF_MOTIF
extern void gdbClearCB           (CB_ARG_LIST_NULL);
extern void gdbClearWindowCB     (CB_ARG_LIST_NULL);

// Return current GDB command line.
extern string current_line();

// Set current GDB input line
extern void set_current_line(const string& input);

// True if last input was at GDB prompt.
extern bool gdb_input_at_prompt;

// True if debuggee is currently running.
extern bool gdb_debuggee_running;

// Clear isearch mode.
// RESET means to reset the history; SHOW means to redisplay.
extern void clear_isearch(bool reset = false, bool show = true);

// Pass the COMMAND given in CLIENT_DATA to gdb_button_command()
#ifdef IF_MOTIF
void gdbCommandCB(CB_ALIST_123(Widget, XtPointer, XtPointer));
#else // NOT IF_MOTIF
void gdbCommandCB(CB_ALIST_12(Widget, const char *));
#endif // IF_MOTIF

// Like gdb_command(), but perform `...' and `()' substitutions
void gdb_button_command(const string& command, Widget origin = 0);

#endif // _DDD_editing_h
// DON'T ADD ANYTHING BEHIND THIS #endif
