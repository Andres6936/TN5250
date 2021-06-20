/* TN5250 - An implementation of the 5250 telnet protocol.
 * Copyright (C) 2005-2008 James Rich
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

Tn5250Scrollbar*
tn5250_scrollbar_new()
{
	Tn5250Scrollbar* This = tn5250_new (Tn5250Scrollbar, 1);
	if (This == NULL)
	{
		return NULL;
	}
	memset(This, 0, sizeof(Tn5250Scrollbar));
	This->next = NULL;
	This->prev = NULL;
	This->table = NULL;
	This->id = -1;
	return (This);
}


void
tn5250_scrollbar_destroy(Tn5250Scrollbar* This)
{
	free(This);
}


int
tn5250_scrollbar_start_rowscols(Tn5250Scrollbar* This)
{
	return (This->rowscols);
}


Tn5250Scrollbar*
tn5250_scrollbar_list_destroy(Tn5250Scrollbar* list)
{
	Tn5250Scrollbar* iter, * next;

	if ((iter = list) != NULL)
	{
		do
		{
			next = iter->next;
			tn5250_scrollbar_destroy(iter);
			iter = next;
		} while (iter != list);
	}
	return NULL;
}


Tn5250Scrollbar*
tn5250_scrollbar_list_add(Tn5250Scrollbar* list, Tn5250Scrollbar* node)
{
	node->prev = node->next = NULL;

	if (list == NULL)
	{
		node->next = node->prev = node;
		return node;
	}
	node->next = list;
	node->prev = list->prev;
	node->prev->next = node;
	node->next->prev = node;
	return list;
}


