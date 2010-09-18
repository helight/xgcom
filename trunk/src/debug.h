/*
 * XGCom (Xiyou Linux Group)
 *
 * Copyright (c) 2008-~  Xiyou Linux Group
 *
 * This source code is released for free distribution under the
 * terms of the GNU General Public License.
 *
 * file name: debug.h
 * modify date: 2009-7-30
 * Author: helight.xu@gmail.com
 *
 * Program definitions:
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG
#include <stdio.h>
#include <stdarg.h>

#define debug_where() \
	printf("\n###FILE: %s ###LINE: %d ###FUC: %s\n", \
        		__FILE__, __LINE__, __FUNCTION__)
static inline void debug_p(const char * format, ...)
{                                                                               
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
}

#else
#define debug_where() do { } while (0)

static inline void debug_p(const char * format, ...)
{
}

#endif


#endif /* TOOLBAR_H_ */
