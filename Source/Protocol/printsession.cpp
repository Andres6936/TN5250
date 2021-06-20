/* TN5250 - An implementation of the 5250 telnet protocol.
 * Copyright (C) 1997-2008 Michael Madore
 * 
 * This file is part of TN5250.
 *
 * TN5250 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1, or (at your option)
 * any later version.
 * 
 * TN5250 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA
 * 
 */

#include "tn5250-private.h"

#ifndef WIN32


static const struct response_code
{
	const char* code;
	int retval;
	const char* text;
} response_codes[] = {
		{ "I901", 1, "Virtual device has less function than source device." },
		{ "I902", 1, "Session successfully started." },
		{ "I906", 1, "Automatic sign-on requested, but not allowed.  A sign-on screen will follow." },
		{ "2702", 0, "Device description not found." },
		{ "2703", 0, "Controller description not found." },
		{ "2777", 0, "Damaged device description." },
		{ "8901", 0, "Device not varied on." },
		{ "8902", 0, "Device not available." },
		{ "8903", 0, "Device not valid for session." },
		{ "8906", 0, "Session initiation failed." },
		{ "8907", 0, "Session failure." },
		{ "8910", 0, "Controller not valid for session." },
		{ "8916", 0, "No matching device found." },
		{ "8917", 0, "Not authorized to object." },
		{ "8918", 0, "Job cancelled." },
		{ "8920", 0, "Object partially damaged." },  /* As opposed to fully damaged? */
		{ "8921", 0, "Communications error." },
		{ "8922", 0, "Negative response received." }, /* From what?!? */
		{ "8923", 0, "Start-up record built incorrectly." },
		{ "8925", 0, "Creation of device failed." },
		{ "8928", 0, "Change of device failed." },
		{ "8929", 0, "Vary on or vary off failed." },
		{ "8930", 0, "Message queue does not exist." },
		{ "8934", 0, "Start up for S/36 WSF received." },
		{ "8935", 0, "Session rejected." },
		{ "8936", 0, "Security failure on session attempt." },
		{ "8937", 0, "Automatic sign-on rejected." },
		{ "8940", 0, "Automatic configuration failed or not allowed." },
		{ "I904", 0, "Source system at incompatible release." },
		{ NULL,   0, NULL }
};

static int tn5250_print_session_waitevent(Tn5250PrintSession* This);

/****f* lib5250/tn5250_print_session_waitevent
 * NAME
 *    tn5250_print_session_waitevent
 * SYNOPSIS
 *    ret = tn5250_print_session_waitevent (This);
 * INPUTS
 *    Tn5250PrintSession * This       - 
 * DESCRIPTION
 *    Calls select() to wait for data to arrive on the socket fdr.
 *    This is the socket being used by the print session to communicate
 *    with the AS/400.  There is no timeout, so the function will wait forever
 *    if no data arrives.
 *****/
static int tn5250_print_session_waitevent(Tn5250PrintSession* This)
{
	fd_set fdr;
	int result = 0;

	FD_ZERO(&fdr);
	FD_SET(This->conn_fd, &fdr);
	select(This->conn_fd + 1, &fdr, NULL, NULL, NULL);

	if (FD_ISSET(This->conn_fd, &fdr))
		result = 1;

	return result;
}

#endif /* ifndef WIN32 */
/* vi:set sts=3 sw=3: */








