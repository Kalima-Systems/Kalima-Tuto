/*
** Copyright (C) 2005-2017 Mike Pall. All rights reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** [ MIT license: http://www.opensource.org/licenses/mit-license.php ]
*/

#ifndef _LUAJ_H
#define _LUAJ_H

#include "lua.h"

#define LUAJ_VERSION		"Lua 2.0.5"
#define LUAJ_VERSION_NUM	20005  /* Version 2.0.5 = 02.00.05. */
#define LUAJ_VERSION_SYM	lua_version_2_0_5
#define LUAJ_COPYRIGHT	"Copyright (C) 2005-2017 Mike Pall"

/* Modes for lua_setmode. */
#define LUA_MODE_MASK	0x00ff

enum {
  LUA_MODE_ENGINE,		/* Set mode for whole engine. */
  LUA_MODE_DEBUG,		/* Set debug mode (idx = level). */

  LUA_MODE_FUNC,		/* Change mode for a function. */
  LUA_MODE_ALLFUNC,		/* Recurse into subroutine protos. */
  LUA_MODE_ALLSUBFUNC,	/* Change only the subroutines. */

  LUA_MODE_TRACE,		/* Flush a compiled trace. */

  LUA_MODE_WRAPCFUNC = 0x10,	/* Set wrapper mode for C function calls. */

  LUA_MODE_MAX
};

/* Flags or'ed in to the mode. */
#define LUA_MODE_OFF		0x0000	/* Turn feature off. */
#define LUA_MODE_ON		0x0100	/* Turn feature on. */
#define LUA_MODE_FLUSH	0x0200	/* Flush compiled code. */

/* Lua public C API. */

/* Control the engine. */
LUA_API int lua_setmode(lua_State *L, int idx, int mode);

/* Enforce (dynamic) linker error for version mismatches. Call from main. */
LUA_API void LUA_VERSION_SYM(void);

#endif
