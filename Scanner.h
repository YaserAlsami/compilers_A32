/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2023
* Author: Yaser Alsami
* Professors: Paulo Sousa
************************************************************
###################################################
#                                                 #
#    ALGONQUIN         @@@@@@@         COLLEGE    #
#                  @@-----------@@                #
#               @@@@|gSquared^2 |@@@@             #
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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 24

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	// i dont think we need this MNID_T
	MNID_T,		/*  1: Method name identifier token (start: &) */

	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
	VID_T,      /* 13: Arithmetic Variable identifier token */
	SVID_T,     /* 14 String Variable identifier token */
	FPL_T,      /* 15 Floating point literal token */
	SCC_OP_T,    /* 16 String concatenation operator token */
	ASS_OP_T,   /* 17 Assignment operator token */
	ART_OP_T,    /* Arithmetic operator token */
	REL_OP_T,  /* Relational operator token */ 
	LOG_OP_T,   /* Logical operator token */
	COMM_T,
	INCR_T,
	DECR_T,

};

/* TO_DO: Define the list of keywords */
static ggchar* tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
	"AVID_T",
	"SVID_T",
	"FPL_T",
	"SCC_OP_T",
	"ASS_OP_T",
	"ART_OP_T",
	"REL_OP_T",
	"LOG_OP_T",
	"COMM_T",
	"INCR_T",
	"DECR_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	i8 codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	i8 intValue;						/* integer literal attribute (value) */
	i8 keywordIndex;					/* keyword index in the keyword table */
	i8 contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	f64 floatValue;					/* floating-point literal attribute (value) */
	ggchar idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	ggchar errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	u8 flags;			/* Flags information */
	union {
		i8 intValue;				/* Integer value */
		f64 floatValue;			/* Float value */
		string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	i8 code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	i8 scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF


/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '('
#define CHRCOL4 '"'


/* These constants will be used on VID / MID function */
#define MNID_SUF '('



/* TO_DO: Error states and illegal state */
#define ESNR	11		/* Error state with no retract */
#define ESWR	12		/* Error state with retract */
#define FS		13		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		14
#define CHAR_CLASSES	11

/* TO_DO: Transition table - type of states defined in separate table */

static int transitionTable[NUM_STATES][CHAR_CLASSES] = {
  {     1,    7,	-1,	-1,    9, -1,   4, -1, -1,   0},  // NOAS0
  {     1,    1,    1,    2,    3,    3,   3,  -1,    3,   1,	13},  // NOAS1
  {    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS,   FS},  // ASNR2 (Method)
  {    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS,   FS},  // ASWR3 (Keyword/Variable)
  {   -1, -1, -1, -1, -1, -1,   5, -1, -1,   4},  // NOAS4
  {     5,    5,    5,    5,    5,    6,   5,  -1,    5,   5},  // NOAS5
  {    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS,   FS},  // ASNR6 (Comment)
  {     8,    7,    8,    8,    8,    8,   8,   FS,    8,   7},  // NOAS7
  {    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS,   FS},  // ASWR8 (Digit)
  {     9,    9,    9,    9,   10,    9,   9,   10,    9,   9},  // NOAS9
  {    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS,   FS},  // ASNR10 (String)
  {    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS,   FS},  // ASNR11 (ES)
  {    FS,   FS,   FS,   FS,   FS,   FS,  FS,   FS,   FS,   FS},   // ASWR12 (ER)
	{ FS,  FS,  FS,  FS,  FS,  FS,  FS,  FS,  FS, FS, FS}, // ASNR13: new state for macro identifier
};


/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static int stateType[NUM_STATES] = {
  NOFS, // 00
  NOFS, // 01
  FSNR, // 02 (Methods)
  FSWR, // 03 (Keyword/Variable)
  NOFS, // 04
  NOFS, // 05
  FSNR, // 06 (Comment)
  NOFS, // 07
  FSWR, // 08 (Digit)
  NOFS, // 09
  FSNR, // 10 (String)
  FSNR, // 11 (Err1 - no retract)
  FSWR , // 12 (Err2 - retract)
	FSWR, // 13: Accepting state for macro identifier with retract
};


/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
i8			startScanner(ReaderPointer psc_buf);
Token tokenizer(challenge_void);
static i8	nextClass(ggchar c);					/* character class function */
static i8	nextState(i8, ggchar);		/* state machine function */
ggvoid			printScannerData(ScannerData scData);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(string lexeme);

/* Declare accepting states functions */
Token funcSL	(ggchar* lexeme);
Token funcIL	(ggchar* lexeme);
Token funcMNID(ggchar* lexeme);
Token funcCMT   (string lexeme);
Token funcKEY	(ggchar* lexeme);
Token funcErr	(ggchar* lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */



static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcMNID,	/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	NULL,		/*      [05] */
	funcCMT,	/* COM  [06] */
	NULL,		/*      [07] */
	funcIL,		/* IL   [08] */
	NULL,		/*      [09] */
	funcSL,		/* SL   [10] */
	funcErr,	/* ERR1 [11] */
	funcErr,		/* ERR2 [12] */
	funcMNID
};


/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 17

/* TO_DO: Define the list of keywords */
static string keywordTable[KWT_SIZE] = {
	"extern ",		/* KW00 */
	"false ",		/* KW01 */
	"true",		/* KW02 */
	"print",
	"fn",		/* KW03 */
	"for",	/* KW04 */
	"if",		/* KW05 */
	"let",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do"	,	/* KW09 */
	"else " ,
	"i8",
	"gg",
	"int",
	"code",
	"data"
	

};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	ggchar indentationCharType;
	i8 indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
i8 numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
