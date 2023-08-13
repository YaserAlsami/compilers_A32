/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
###################################################
#                                                 #
#    ALGONQUIN         @@@@@@@         COLLEGE    #
#                  @@-----------@@                #
#               @@@@|  M O L D  |@@@@             #
#            @@@@@@@@-----------@@@@@@@@          #
#         @@@@@@@@@@@@@  @@@@@@@   @@@@@@@        #
#       @@@@@@@@@@@@@      @@@       @@@@@@       #
#     @@@@@@@    @@@@@    @@@@       @@@@@@@@     #
#    @@@@@@@       @@@@@ @@@@@@@    @@@@@@@@@@    #
#   @@@@@@@        @@@@@ @@@@@ @@@@@@    @@@@@@   #
#  @@@@@@@@@@    @@             @@@@      @@@@@@  #
#  @@@@@@@@@@@@@@@  @@@@@  @@@@  @@@@   @@    @@  #
# @@@@@@@@@@@@@@@   @@@@@ @@@@@   @@@@@@@@@    @@ #
# @@@@@      @@@@   @@@ @@@ @@@   @@@@    @@@@@@@ #
# @@@@        @@@@  @@@ @@@ @@@   @@@      @@@@@@ #
#  @@@@     @@@@@@@              @@@@@    @@@@@@  #
#  @@@@@@@@@@@     @@@  @@@   @@@    @@@@@@@@@@   #
#   @@@@@@@@@@@   @@@ @@@@@@ @@@@@    @@@@@@@@@   #
#    @@@@@@@@@@@@@@@ @@@@@@    @@@@@@@@@@@@@@@    #
#     @@@@@@@@@       @@@        @@@@@@@@@@@      #
#       @@@@@@         @@         @@@@@@@@@       #
#         @@@@@       @@@@@     @@@@@@@@@         #
#            @@@@@@@@@@@@@@@@@@@@@@@@@            #
#               @@@@@@@@@@@@@@@@@@@               #
#  COMPILERS        @@@@@@@@@@@        2023-S     #
#                                                 #
###################################################
*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */
#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_
#define READER_REL 0x02  /* Example value for READER_REL */

 /* TIP: Do not change pragmas, unless necessary .......................................*/
 /*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
 /*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

 /* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (gSquared^2) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for gSquared^2 */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */
/* TO_DO: BIT 2: EMP: Empty */
/* TO_DO: BIT 1: REL = Relocation */
/* TO_DO: BIT 0: END = EndOfBuffer */
/* BITS (7654.3210) */
#define READER_DEFAULT_FLAG 0x00  /* (0000.0000)_2 = (000)_10 */
#define FUL_MASK 0x08              /* (0000.1000)_2 = (08)_16 */
#define EMP_MASK 0x04              /* (0000.0100)_2 = (04)_16 */
#define REL_MASK 0x02              /* (0000.0010)_2 = (02)_16 */
#define END_MASK 0x01              /* (0000.0001)_2 = (01)_16 */
#define RST_FLAG_RLC					0xDF
#define RST_FLAG_FUL		0x7F
#define SET_FLAG_RLC		0x20	
#define RST_FLAG_END		0xEF			/*1110.1111*/
#define SET_FLAG_END		0x10			/*0001.0000*/




#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (gSquared^2) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct offset {
	i8 mark;			/* the offset to the mark position (in chars) */
	i8 read;			/* the offset to the get a char position (in chars) */
	i8 wrte;			/* the offset to the add chars (in chars) */
} Offset;

/* Buffer structure */

typedef struct bufferReader {
	ggchar* content;          /* pointer to the beginning of character array (character buffer) */
	i8 size;                  /* current dynamic memory size (in bytes) allocated to character buffer */
	i8 increment;             /* character array increment factor */
	i8 mode;                  /* operational mode indicator */
	i8 flags;                 /* contains character array reallocation flag and end-of-buffer flag */
	Offset offset;            /* Offset / position field */
	i8 histogram[NCHAR];      /* Statistics of chars */
	i8 numReaderErrors;       /* Number of errors from Reader */
} BufferReader, *ReaderPointer;


/* FUNCTIONS DECLARATION:  .................................. */
/*
/* General Operations */
ReaderPointer readerCreate(i8, i8, i8);
ReaderPointer readerAddChar(ReaderPointer const, ggchar);
bool readerClear(ReaderPointer const);
bool readerFree(ReaderPointer const);
bool readerIsFull(ReaderPointer const);
bool readerIsEmpty(ReaderPointer const);
bool readerSetMark(ReaderPointer const, i8);
i8 readerPrint(ReaderPointer const);
i8 readerLoad(ReaderPointer const, FILE* const);
bool readerRecover(ReaderPointer const);
bool readerRetract(ReaderPointer const);
bool readerRestore(ReaderPointer const);

/* Getters */
ggchar readerGetChar(ReaderPointer const);
ggchar* readerGetContent(ReaderPointer const, i8);
i8 readerGetPosRead(ReaderPointer const);
i8 readerGetPosWrte(ReaderPointer const);
i8 readerGetPosMark(ReaderPointer const);
i8 readerGetSize(ReaderPointer const);
i8 readerGetInc(ReaderPointer const);
i8 readerGetMode(ReaderPointer const);
i8 readerGetFlags(ReaderPointer const);
ggvoid readerPrintStat(ReaderPointer const);
i8 readerNumErrors(ReaderPointer const);

#endif
