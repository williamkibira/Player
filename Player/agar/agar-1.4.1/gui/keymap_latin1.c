/*
 * Copyright (c) 2008 Hypertriton, Inc. <http://hypertriton.com/>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <core/core.h>

#include "widget.h"
#include "editable.h"
#include "keymap.h"

/*
 * Traditional ISO-8859-1 keyboard input mapping to Unicode.
 */
const struct ag_key_mapping agKeymapLATIN1[] = {
	{ AG_KEY_Q,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d1	},
	{ AG_KEY_W,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d7	},
	{ AG_KEY_E,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c5	},
	{ AG_KEY_R,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d2	},
	{ AG_KEY_T,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d4	},
	{ AG_KEY_Y,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d9	},
	{ AG_KEY_U,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d5	},
	{ AG_KEY_I,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c9	},
	{ AG_KEY_O,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00cf	},
	{ AG_KEY_P,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d0	},
	{ AG_KEY_LEFTBRACKET,	AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00fb	},
	{ AG_KEY_RIGHTBRACKET,	AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00fd	},
	{ AG_KEY_A,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c1	},
	{ AG_KEY_S,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d3	},
	{ AG_KEY_D,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c4	},
	{ AG_KEY_F,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c6	},
	{ AG_KEY_G,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c7	},
	{ AG_KEY_H,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c8	},
	{ AG_KEY_J,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00ca	},
	{ AG_KEY_K,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00cb	},
	{ AG_KEY_L,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00cc	},
	{ AG_KEY_SEMICOLON,	AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00ba	},
	{ AG_KEY_QUOTE,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a2	},
	{ AG_KEY_BACKSLASH,	AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00fc	},
	{ AG_KEY_Z,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00da	},
	{ AG_KEY_X,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d8	},
	{ AG_KEY_C,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c3	},
	{ AG_KEY_V,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00d6	},
	{ AG_KEY_B,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c2	},
	{ AG_KEY_N,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00ce	},
	{ AG_KEY_M,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00cd	},
	{ AG_KEY_COMMA,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00bc	},
	{ AG_KEY_PERIOD,	AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00be	},
	{ AG_KEY_SLASH,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00bf	},
	{ AG_KEY_BACKQUOTE,	AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00fe	},
	{ AG_KEY_1,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a1	},
	{ AG_KEY_2,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00c0	},
	{ AG_KEY_3,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a3	},
	{ AG_KEY_4,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a4	},
	{ AG_KEY_5,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a5	},
	{ AG_KEY_6,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00de	},
	{ AG_KEY_7,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a6	},
	{ AG_KEY_8,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00aa	},
	{ AG_KEY_9,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a8	},
	{ AG_KEY_0,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00a9	},
	{ AG_KEY_MINUS,		AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00df	},
	{ AG_KEY_EQUALS,	AG_KEYMOD_ALT|AG_KEYMOD_SHIFT,	0x00ab	},

	{ AG_KEY_Q,		AG_KEYMOD_ALT,		0x00f1	},
	{ AG_KEY_W,		AG_KEYMOD_ALT,		0x00f7	},
	{ AG_KEY_E,		AG_KEYMOD_ALT,		0x00e5	},
	{ AG_KEY_R,		AG_KEYMOD_ALT,		0x00f2	},
	{ AG_KEY_T,		AG_KEYMOD_ALT,		0x00f4	},
	{ AG_KEY_Y,		AG_KEYMOD_ALT,		0x00f9	},
	{ AG_KEY_U,		AG_KEYMOD_ALT,		0x00f5	},
	{ AG_KEY_I,		AG_KEYMOD_ALT,		0x00e9	},
	{ AG_KEY_O,		AG_KEYMOD_ALT,		0x00ef	},
	{ AG_KEY_P,		AG_KEYMOD_ALT,		0x00f0	},
	{ AG_KEY_LEFTBRACKET,	AG_KEYMOD_ALT,		0x00db	},
	{ AG_KEY_RIGHTBRACKET,	AG_KEYMOD_ALT,		0x00fd	},
	{ AG_KEY_A,		AG_KEYMOD_ALT,		0x00e1	},
	{ AG_KEY_S,		AG_KEYMOD_ALT,		0x00f3	},
	{ AG_KEY_D,		AG_KEYMOD_ALT,		0x00e4	},
	{ AG_KEY_F,		AG_KEYMOD_ALT,		0x00e6	},
	{ AG_KEY_G,		AG_KEYMOD_ALT,		0x00e7	},
	{ AG_KEY_H,		AG_KEYMOD_ALT,		0x00e8	},
	{ AG_KEY_J,		AG_KEYMOD_ALT,		0x00ea	},
	{ AG_KEY_K,		AG_KEYMOD_ALT,		0x00eb	},
	{ AG_KEY_L,		AG_KEYMOD_ALT,		0x00ec	},
	{ AG_KEY_SEMICOLON,	AG_KEYMOD_ALT,		0x00bb	},
	{ AG_KEY_QUOTE,		AG_KEYMOD_ALT,		0x00a7	},
	{ AG_KEY_BACKSLASH,	AG_KEYMOD_ALT,		0x00dc	},
	{ AG_KEY_Z,		AG_KEYMOD_ALT,		0x00fa	},
	{ AG_KEY_X,		AG_KEYMOD_ALT,		0x00f8	},
	{ AG_KEY_C,		AG_KEYMOD_ALT,		0x00e3	},
	{ AG_KEY_V,		AG_KEYMOD_ALT,		0x00f6	},
	{ AG_KEY_B,		AG_KEYMOD_ALT,		0x00e2	},
	{ AG_KEY_N,		AG_KEYMOD_ALT,		0x00ee	},
	{ AG_KEY_M,		AG_KEYMOD_ALT,		0x00ed	},
	{ AG_KEY_COMMA,		AG_KEYMOD_ALT,		0x00ac	},
	{ AG_KEY_PERIOD,	AG_KEYMOD_ALT,		0x00ae	},
	{ AG_KEY_SLASH,		AG_KEYMOD_ALT,		0x00af	},
	{ AG_KEY_BACKQUOTE,	AG_KEYMOD_ALT,		0x00e0	},
	{ AG_KEY_1,		AG_KEYMOD_ALT,		0x00b1	},
	{ AG_KEY_2,		AG_KEYMOD_ALT,		0x00b2	},
	{ AG_KEY_3,		AG_KEYMOD_ALT,		0x00b3	},
	{ AG_KEY_4,		AG_KEYMOD_ALT,		0x00b4	},
	{ AG_KEY_5,		AG_KEYMOD_ALT,		0x00b5	},
	{ AG_KEY_6,		AG_KEYMOD_ALT,		0x00b6	},
	{ AG_KEY_7,		AG_KEYMOD_ALT,		0x00b7	},
	{ AG_KEY_8,		AG_KEYMOD_ALT,		0x00b8	},
	{ AG_KEY_9,		AG_KEYMOD_ALT,		0x00b9	},
	{ AG_KEY_0,		AG_KEYMOD_ALT,		0x00b0	},
	{ AG_KEY_MINUS,		AG_KEYMOD_ALT,		0x00bd	},
	{ AG_KEY_EQUALS,	AG_KEYMOD_ALT,		0x00ad	},
	
	{ AG_KEY_LAST,		0,			0x0	},
};
