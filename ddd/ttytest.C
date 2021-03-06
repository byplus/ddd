// $Id$ 
// TTYAgent test program

// Copyright (C) 1995 Technische Universitaet Braunschweig, Germany.
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

char ttytest_rcsid[] = 
    "$Id$";

#include <stdlib.h>
#include "TTYAgent.h"
#include "cook.h"

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

// Trace communication
static void trace(const string& prefix, void *call_data)
{
    DataLength* dl    = (DataLength *) call_data;
    string s(dl->data, dl->length);

    bool s_ends_with_nl = false;
    if (s.length() > 0 && s[s.length() - 1] == '\n')
    {
	s_ends_with_nl = true;
	s = s.before(int(s.length() - 1));
    }

    s = quote(s);
    string nl = "\\n\"\n";
    nl += replicate(' ', prefix.length());
    nl += "\"";
    s.gsub("\\n", nl);

    if (s_ends_with_nl)
	s(s.length() - 1, 0) = "\\n";

    std::cerr << prefix << s << '\n';
}

// Invoked whenever text is received from the inferior
void traceInputHP(Agent *, void *, void *call_data)
{
    trace("<- ", call_data);
}

// Invoked whenever text is sent to the inferior
void traceOutputHP(Agent *, void *, void *call_data)
{
    trace("-> ", call_data);
}

// Invoked whenever error messages are received from the inferior
void traceErrorHP (Agent *, void *, void *call_data)
{
    trace("<= ", call_data);
}

// Invoked whenever text is received from standard input
void sendInputHP(Agent *, void *client_data, void *call_data)
{
    TTYAgent& tty = *((TTYAgent *)client_data);
    DataLength* dl    = (DataLength *) call_data;

    tty.write(dl->data, dl->length);
}

// Invoked whenever EOF is received from standard input
void exitHP(Agent *, void *client_data, void *)
{
    TTYAgent& tty = *((TTYAgent *)client_data);
    tty.shutdown();
}

// Invoked whenever the inferior dies
void diedHP(Agent *a, void *client_data, void *call_data)
{
    std::cerr << a->path() << ": " << STATIC_CAST(char *,call_data) << "\n";

    TTYAgent& tty = *((TTYAgent *)client_data);
    tty.shutdown();
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    XtAppContext app_context;

    // Initialize it all
    Widget toplevel = 
	XtAppInitialize(&app_context, "TTYtest", 0, 0, &argc, argv, 0, 0, 0);

    string command;
    for (int i = 1; i < argc; i++)
    {
	if (!command.empty())
	    command += " ";
	command += argv[i];
    }

    if (command.empty())
    {
	std::cerr << XtName(toplevel) 
	     << ": usage: " << XtName(toplevel) << " COMMAND [ARGS...]\n";
	return 1;
    }

    // `tty' handles communication with the inferior
    TTYAgent tty(app_context, command);
    tty.addHandler(Input,  traceInputHP);
    tty.addHandler(Output, traceOutputHP);
    tty.addHandler(Error,  traceErrorHP);
    tty.addHandler(Died,   diedHP, &tty);

    // `me' handles communication with standard input and output
    LiterateAgent me(app_context);
    me.addHandler(Input, sendInputHP, &tty);
    me.addHandler(InputEOF, exitHP, &tty);

    tty.start();
    me.start();

    XtAppMainLoop(app_context);

    return EXIT_SUCCESS;	// Never reached
}
