/* $Header: /u/christos/src/tcsh-6.04/RCS/sh.char.h,v 3.7 1993/07/03 23:47:53 christos Exp christos $ */
/*
 * sh.char.h: Table for spotting special characters quickly
 * 	      Makes for very obscure but efficient coding.
 */
/*-
 * Copyright (c) 1980, 1991 The Regents of the University of California.
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _h_sh_char
#define _h_sh_char
#if defined(NeXT) && defined(NLS)
# include <appkit/NXCType.h>
#else
# include <ctype.h>
#endif

#ifdef _MINIX
# undef _SP
#endif /* _MINIX */
extern unsigned short _cmap[];

#ifndef NLS
extern unsigned char _cmap_lower[], _cmap_upper[];

#endif

#define	_QF	0x0001		/* '" (Forward quotes) */
#define	_QB	0x0002		/* ` (Backquote) */
#define	_SP	0x0004		/* space and tab */
#define	_NL	0x0008		/* \n */
#define	_META	0x0010		/* lex meta characters, sp #'`";&<>()|\t\n */
#define	_GLOB	0x0020		/* glob characters, *?{[` */
#define	_ESC	0x0040		/* \ */
#define	_DOL	0x0080		/* $ */
#define	_DIG  	0x0100		/* 0-9 */
#define	_LET  	0x0200		/* a-z, A-Z, _ */
#define	_UP   	0x0400		/* A-Z */
#define	_DOW  	0x0800		/* a-z */
#define	_XD 	0x1000		/* 0-9, a-f, A-F */
#define	_CMD	0x2000		/* lex end of command chars, ;&(|` */
#define _CTR	0x4000		/* control */
#define _PUN	0x8000		/* punctuation */

#if defined(SHORT_STRINGS) && defined(KANJI)
#define cmap(c, bits)	\
	((((c) & QUOTE) || (c>127 && adrof(STRnokanji))) ? \
	0 : (_cmap[(unsigned char)(c)] & (bits)))
#else
#define cmap(c, bits)	\
	(((c) & QUOTE) ? 0 : (_cmap[(unsigned char)(c)] & (bits)))
#endif

#define isglob(c)	cmap(c, _GLOB)
#define isspc(c)	cmap(c, _SP)
#define ismeta(c)	cmap(c, _META)
#define iscmdmeta(c)	cmap(c, _CMD)
#define letter(c)	(((Char)(c) & QUOTE) ? 0 : \
			 (isalpha((unsigned char) (c)) || (c) == '_'))
#define alnum(c)	(((Char)(c) & QUOTE) ? 0 : \
		         (isalnum((unsigned char) (c)) || (c) == '_'))
#ifdef NLS
# ifdef NeXT
#  define Isspace(c)	(((Char)(c) & QUOTE) ? 0 : NXIsSpace((unsigned) (c)))
#  define Isdigit(c)	(((Char)(c) & QUOTE) ? 0 : NXIsDigit((unsigned) (c)))
#  define Isalpha(c)	(((Char)(c) & QUOTE) ? 0 : NXIsAlpha((unsigned) (c)))
#  define Islower(c)	(((Char)(c) & QUOTE) ? 0 : NXIsLower((unsigned) (c)))
#  define Isupper(c)	(((Char)(c) & QUOTE) ? 0 : NXIsUpper((unsigned) (c)))
#  define Tolower(c) 	(((Char)(c) & QUOTE) ? 0 : NXToLower((unsigned) (c)))
#  define Toupper(c) 	(((Char)(c) & QUOTE) ? 0 : NXToUpper((unsigned) (c)))
#  define Isxdigit(c)	(((Char)(c) & QUOTE) ? 0 : NXIsXDigit((unsigned) (c)))
#  define Isalnum(c)	(((Char)(c) & QUOTE) ? 0 : NXIsAlNum((unsigned) (c)))
#  define Iscntrl(c) 	(((Char)(c) & QUOTE) ? 0 : NXIsCntrl((unsigned) (c)))
#  define Isprint(c) 	(((Char)(c) & QUOTE) ? 0 : NXIsPrint((unsigned) (c)))
#  define Ispunct(c) 	(((Char)(c) & QUOTE) ? 0 : NXIsPunct((unsigned) (c)))
# else /* !NeXT */
#  define Isspace(c)	(((Char)(c) & QUOTE) ? 0 : isspace((unsigned char) (c)))
#  define Isdigit(c)	(((Char)(c) & QUOTE) ? 0 : isdigit((unsigned char) (c)))
#  define Isalpha(c)	(((Char)(c) & QUOTE) ? 0 : isalpha((unsigned char) (c)))
#  define Islower(c)	(((Char)(c) & QUOTE) ? 0 : islower((unsigned char) (c)))
#  define Isupper(c)	(((Char)(c) & QUOTE) ? 0 : isupper((unsigned char) (c)))
#  define Tolower(c) 	(((Char)(c) & QUOTE) ? 0 : tolower((unsigned char) (c)))
#  define Toupper(c) 	(((Char)(c) & QUOTE) ? 0 : toupper((unsigned char) (c)))
#  define Isxdigit(c)	(((Char)(c) & QUOTE) ? 0 : isxdigit((unsigned char) (c)))
#  define Isalnum(c)	(((Char)(c) & QUOTE) ? 0 : isalnum((unsigned char) (c)))
#  define Iscntrl(c) 	(((Char)(c) & QUOTE) ? 0 : iscntrl((unsigned char) (c)))
#  define Isprint(c) 	(((Char)(c) & QUOTE) ? 0 : isprint((unsigned char) (c)))
#  define Ispunct(c) 	(((Char)(c) & QUOTE) ? 0 : ispunct((unsigned char) (c)))
# endif /* !NeXT */
#else /* !NLS */
# define Isspace(c)	cmap(c, _SP|_NL)
# define Isdigit(c)	cmap(c, _DIG)
# define Isalpha(c)	(cmap(c,_LET) && !(((c) & META) && AsciiOnly))
# define Islower(c)	(cmap(c,_DOW) && !(((c) & META) && AsciiOnly))
# define Isupper(c)	(cmap(c, _UP) && !(((c) & META) && AsciiOnly))
# define Tolower(c)	(_cmap_lower[(unsigned char)(c)])
# define Toupper(c)	(_cmap_upper[(unsigned char)(c)])
# define Isxdigit(c)	cmap(c, _XD)
# define Isalnum(c)	(cmap(c, _DIG|_LET) && !(((Char)(c) & META) && AsciiOnly))
# define Iscntrl(c)	(cmap(c,_CTR) && !(((c) & META) && AsciiOnly))
# define Isprint(c)	(!cmap(c,_CTR) && !(((c) & META) && AsciiOnly))
# define Ispunct(c)	(cmap(c,_PUN) && !(((c) & META) && AsciiOnly))
#endif /* !NLS */

#endif /* _h_sh_char */
