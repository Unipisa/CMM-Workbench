/*---------------------------------------------------------------------------*
 *
 *  machine.h   Processor Dependent Definitions
 *  date:	3 January 1995
 *  authors:	Giuseppe Attardi
 *  email:	cmm@di.unipi.it
 *  address:	Dipartimento di Informatica
 *		Corso Italia 40
 *		I-56125 Pisa, Italy
 *
 *  Copyright (C) 1995 Giuseppe Attardi
 *
 *  This file is part of the PoSSo Customizable Memory Manager (CMM).
 *
 * Permission to use, copy, and modify this software and its documentation is
 * hereby granted only under the following terms and conditions.  Both the
 * above copyright notice and this permission notice must appear in all copies
 * of the software, derivative works or modified versions, and any portions
 * thereof, and both notices must appear in supporting documentation.
 *
 * Users of this software agree to the terms and conditions set forth herein,
 * and agree to license at no charge to all parties under these terms and
 * conditions any derivative works or modified versions of this software.
 * 
 * This software may be distributed (but not offered for sale or transferred
 * for compensation) to third parties, provided such third parties agree to
 * abide by the terms and conditions of this notice.  
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE COPYRIGHT HOLDERS DISCLAIM ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL THE COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
 * IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *---------------------------------------------------------------------------*/

#ifndef _MACHINE_H
#define _MACHINE_H

/*---------------------------------------------------------------------------*
 * -- Type Definitions
 *---------------------------------------------------------------------------*/

typedef unsigned char 	Byte;
typedef unsigned long	Word;
typedef char *		Ptr;
typedef Ptr *		GCP;	/* Pointer to a garbage collected object */
typedef unsigned	Page;	/* Page number */

#if defined(_MSC_VER) && (_MSC_VER < 1100) /* MS VC version < 5.0 */ \
    || defined(__mips) && !defined(__GNUC__)
#else
# define ANSI_CPP
#endif

#ifndef ANSI_CPP
typedef int	bool;
# define false	0
# define true	1
#endif

/*---------------------------------------------------------------------------*
 * -- Compatibility
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
# define C_LANG          "C"
#else
# define C_LANG          
#endif

#if defined(__sun__) && !defined(__svr4__)
  extern C_LANG void	bzero(void *, int);
#else
# include <string.h>
# define bzero(s, n)	memset(s, 0, n)
#endif

#ifndef MIN
# define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef MAX
# define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#if defined(__svr4__) || defined(_WIN32) || defined(macintosh)
# define _setjmp(x)  setjmp(x)
# define _longjmp(x,y) longjmp(x,y)
#endif

#if !defined(__BORLANDC__) && !defined(_WIN32) && !defined(macintosh)
# include <unistd.h>	// extern C_LANG void* sbrk(int);
#endif

#if !defined(_WIN32) && !defined(macintosh)
# define SBRK
#endif

/*---------------------------------------------------------------------------*
 *
 * Stack growth
 *
 *---------------------------------------------------------------------------*/

#ifndef hp9000s800
# define STACK_GROWS_DOWNWARD
#endif

/*---------------------------------------------------------------------------*
 *
 * Architectures requiring double alignement for objects
 *
 *---------------------------------------------------------------------------*/

#if defined(__mips) || defined(__sparc) || defined(__alpha)
# define OBJ_ALIGNMENT	8
#else
# define OBJ_ALIGNMENT	4
#endif

/*
 * DOUBLE_ALIGN = (OBJ_ALIGNMENT != sizeof(Word))
 */
#if defined(__mips) || defined(__sparc)
# define DOUBLE_ALIGN
# define ARRAY_PADDING
#endif

#define MEMALIGN	(char *)memalign

/*---------------------------------------------------------------------------*
 *
 * Start of system heap
 *
 *---------------------------------------------------------------------------*/

extern void *	globalHeapStart; // start of global heap

/*---------------------------------------------------------------------------*
 *
 * Start of data segment
 *
 *---------------------------------------------------------------------------*/

#if defined(__alpha)
#   define DATASTART (0x140000000)
#elif defined(__sgi) || defined(_sgi) || defined(sgi)
    typedef    unsigned int    uint;
#   include <sys/immu.h>
// IRIX 6.3: #   include <bool.h>
#   define DATASTART USRDATA
#elif defined(__svr4__) || defined(DGUX)
    extern int etext;
    extern char * CmmSVR4DataStart(int);
#   define DATASTART CmmSVR4DataStart(0x10000)
#elif defined(hp9000s300)
    extern int etext;
#   define DATASTART ((((unsigned long)(&etext)) + 0xfff) & ~0xfff)

#elif defined(_WIN32)
#   define STACKBOTTOM CmmGetStackBase()

#elif defined(__i386)
    extern int etext;
#   define DATASTART ((((unsigned long)(&etext)) + 0xfff) & ~0xfff)

#   if defined(GO32)
#       define STACKBOTTOM (0x80000000)
#   else
#       define STACKBOTTOM (0xc0000000)
#   endif

#elif defined(__mips)
#   include <machine/vmparam.h>
#   define DATASTART USRDATA
#elif defined(__hppa)
    extern int __data_start;
#   define DATASTART (&__data_start)
#elif defined(ibm032)		/* IBM RT	*/
#   define DATASTART 0x10000000
#elif defined(_IBMR2)		/* IBM RS/6000	*/
#   define DATASTART 0x20000000
#   define STACKBOTTOM ((unsigned long)0x2ff80000)
#elif defined(__NeXT)
#   define DATASTART ((unsigned long) get_etext())
#   define STACKBOTTOM ((unsigned long) 0x4000000)
#elif defined(ns32000)
    extern char **environ;
#   define DATASTART (&environ)
#elif defined(__sparc)
      /* This assumes ZMAGIC, i.e. demand-loadable executables.	*/
#   define DATASTART (*(int *)0x2004+0x2000)
#elif defined(sun3)
    extern char etext;
#   define DATASTART ((((unsigned long)(&etext)) + 0x1ffff) & ~0x1ffff)
#elif defined(SCO)
#   define DATASTART ((((unsigned long)(&etext)) + 0x3fffff) & ~0x3fffff) \
		      + ((unsigned long)&etext & 0xfff)
#elif defined(_AUX_SOURCE)
      /* This only works for shared-text binaries with magic number 0413.
	 The other sorts of SysV binaries put the data at the end of the text,
	 in which case the default of &etext would work.  Unfortunately,
	 handling both would require having the magic-number available.
	 -- Parag
	 */
#   define DATASTART ((((unsigned long)(&etext)) + 0x3fffff) & ~0x3fffff) \
		      + ((unsigned long)&etext & 0x1fff)
#elif defined(macintosh)
	// etc. etc.
#	include <LowMem.h>
#	define STACKBOTTOM ((unsigned long) LMGetCurStackBase())
#	define CMM_VERBOSE
#else
    /* The default case works only for contiguous text and data, such as
     * on a Vax.                                                           */
    extern char etext;
#   define DATASTART (&etext)
#endif

#endif /* ! _MACHINE_H */
