// $Id$ -*- C++ -*-
// Undo/Redo buffer

// Copyright (C) 1998 Technische Universitaet Braunschweig, Germany.
// Written by Andreas Zeller <zeller@ips.cs.tu-bs.de>.
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
// `http://www.cs.tu-bs.de/softech/ddd/',
// or send a mail to the DDD developers <ddd@ips.cs.tu-bs.de>.

#ifndef _DDD_UndoBuffer_h
#define _DDD_UndoBuffer_h

#ifdef __GNUG__
#pragma interface
#endif

#include "bool.h"
#include "UndoBE.h"
#include "string-fun.h"		// itostring()
#include "IntArray.h"

class BreakPoint;

class UndoBuffer {

private:
    // The history itself
    static UndoBufferArray history;

    // Last position in history + 1
    static int history_position;

    // Currently processed entry
    static int current_entry;

    // General scheme:
    //
    // History
    // -------
    //
    // `history' contains:
    //
    // 0                       \ 
    // 1 ...                    > entries (state or commands) to be undone
    // (history_position - 1)  /
    // (history_position)      \ 
    // ...                      > entries (state or commands) to be redone
    // (history.size() - 1)    /
    //
    //
    // Entries
    // -------
    //
    // An entry is either a STATE (command == false) or a COMMAND
    // (otherwise).  A command is to be executed when reached; a state
    // is to be restored when reached.  STATES are distinguished in
    // execution states and non-execution states (lookups).

    // True if we have undone some exec position
    static bool _showing_earlier_state;

    // Current command source
    static string current_source;

    // True if position history is to stay unchanged
    static bool locked;

    // Helpers
    static void process_command(const UndoBufferEntry& entry, int direction);
    static void process_status(const UndoBufferEntry& entry, int direction);

    // Count undoing commands
    static int own_processed;
    static int own_direction;

    // Rename all breakpoints from OLD_BP_NR to NEW_BP_NR
    static void remap_breakpoint(int old_bp_nr, int new_bp_nr);
    static void remap_breakpoint(string& cmd, int old_bp_nr, int new_bp_nr);

    // Enter or leave `past exec' mode
    static void showing_earlier_state(bool set);

protected:
    // Add new entry
    static void add(const UndoBufferEntry& entry);

    // Process entry
    static void process_command(int entry, int direction);
    static void process_status(int entry, int direction);

    // Log current position
    static void log();

    // Call when all is done
    static void done();

    // Get a short action description from COMMAND
    static string action(const string& command);

    // True if ENTRY has any effect
    static bool has_effect(const UndoBufferEntry& entry);

public:
    // Add status NAME/VALUE to history.
    static void add(const string& name, const string& value);

    // Add command COMMAND to history.
    static void add_command(const string &command, bool exec = false);

    // Custom calls
    static void add_position(const string& file_name, int line, bool exec)
    {
	add(exec ? UB_EXEC_POS : UB_POS, file_name + ":" + itostring(line));
    }

    static void add_address(const string& address, bool exec)
    {
	add(exec ? UB_EXEC_ADDRESS : UB_ADDRESS, address);
    }

    static void add_where(const string& where)
    {
	add(UB_WHERE, where);
    }

    static void add_frame(const string& frame)
    {
	add(UB_FRAME, frame);
    }

    static void add_registers(const string& registers)
    {
	add(UB_REGISTERS, registers);
    }

    static void add_threads(const string& threads)
    {
	add(UB_THREADS, threads);
    }

    static void add_display(const string& name, const string& value)
    {
	add(UB_DISPLAY_PREFIX + name, value);
    }

    static void add_display_address(const string& name, const string& addr)
    {
	add(UB_DISPLAY_ADDRESS_PREFIX + name, addr);
    }

    // Undo/Redo action
    static void undo();
    static void redo();

    // Undo/Redo action descriptions
    static string undo_action();
    static string redo_action();

    // True iff we're showing an earlier program state
    static bool showing_earlier_state() { return _showing_earlier_state; }

    // Restore current program state
    static void restore_current_state();

    // Clear history
    static void clear();

    // Clear all execution positions
    static void clear_exec_pos();

    // Invariant
    static bool OK();

    // Add breakpoint state to OS
    static void add_breakpoint_state(ostream& os, BreakPoint *bp);

    // Set source command
    static void set_source(const string& command) { current_source = command; }
};

extern UndoBuffer undo_buffer;

#endif // _DDD_UndoBuffer_h
// DON'T ADD ANYTHING BEHIND THIS #endif
