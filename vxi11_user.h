/* vxi11_user.h
 * Copyright (C) 2006 Steve D. Sharples
 *
 * User library for opening, closing, sending to and receiving from
 * a device enabled with the VXI11 RPC ethernet protocol. Uses the files
 * generated by rpcgen vxi11.x.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The author's email address is steve.sharples@nottingham.ac.uk
 */

#ifndef	_VXI11_USER_H_
#define	_VXI11_USER_H_

#ifdef WIN32
#  ifdef vxi11_EXPORTS
#    define vx_EXPORT __declspec(dllexport)
#  else
#    define vx_EXPORT __declspec(dllimport)
#  endif
#else
#  define vx_EXPORT
#  define __stdcall
#endif

#ifdef WIN32
#  include <visa.h>
#else
#  include <rpc/rpc.h>
#  include "vxi11.h"
#endif

#define	VXI11_CLIENT		CLIENT
#define	VXI11_LINK		Create_LinkResp

struct _CLINK {
#ifdef WIN32
	ViSession rm;
	ViSession session;
#else
	VXI11_CLIENT *client;
	VXI11_LINK *link;
#endif
} ;

typedef	struct _CLINK CLINK;

#define	VXI11_DEFAULT_TIMEOUT	10000	/* in ms */
#define	VXI11_READ_TIMEOUT	2000	/* in ms */
#define	VXI11_NULL_READ_RESP	50	/* vxi11_receive() return value if a query
					 * times out ON THE INSTRUMENT (and so we have
					 * to resend the query again) */
#define	VXI11_NULL_WRITE_RESP	51	/* vxi11_send() return value if a sent command
					 * times out ON THE INSTURMENT. */


/* The four main functions: open, close, send, receieve (plus a couple of wrappers) */
vx_EXPORT CLINK *vxi11_open_device(const char *address);
vx_EXPORT CLINK *vxi11_open_device(const char *address, char *device);
vx_EXPORT int vxi11_open_device(const char *address, CLINK *clink);
vx_EXPORT int vxi11_open_device(const char *address, CLINK *clink, char *device);
vx_EXPORT int vxi11_close_device(const char *address, CLINK *clink);
vx_EXPORT int vxi11_send(CLINK *clink, const char *cmd);
vx_EXPORT int vxi11_send(CLINK *clink, const char *cmd, unsigned long len);
vx_EXPORT long vxi11_receive(CLINK *clink, char *buffer, unsigned long len, unsigned long timeout=VXI11_READ_TIMEOUT);

/* Utility functions, that use send() and receive(). Use these too. */
vx_EXPORT int vxi11_send_data_block(CLINK *clink, const char *cmd, char *buffer, unsigned long len);
vx_EXPORT long vxi11_receive_data_block(CLINK *clink, char *buffer, unsigned long len, unsigned long timeout=VXI11_READ_TIMEOUT);
vx_EXPORT long vxi11_send_and_receive(CLINK *clink, const char *cmd, char *buf, unsigned long buf_len, unsigned long timeout=VXI11_READ_TIMEOUT);
vx_EXPORT long vxi11_obtain_long_value(CLINK *clink, const char *cmd, unsigned long timeout=VXI11_READ_TIMEOUT);
vx_EXPORT double vxi11_obtain_double_value(CLINK *clink, const char *cmd, unsigned long timeout=VXI11_READ_TIMEOUT);

#endif
