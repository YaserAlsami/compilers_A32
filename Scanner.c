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
#               @@@@| gSquared^2 @@@@             #
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
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2022
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */

/* #define NDEBUG to suppress assert() call */
#define NDEBUG
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern ReaderPointer stringLiteralTable;	/* String literal table */
i8 line;								/* Current line number of the source code */
extern i8 errorNumber;				/* Defined in platy_st.c - run-time error number */

extern i8 stateType[NUM_STATES];
extern ggchar* keywordTable[KWT_SIZE];
extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern i8 transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static ReaderPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static ReaderPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

i8 startScanner(ReaderPointer psc_buf) {
	/* TO_DO: Start histogram */
	/* Basic scanner initialization */
	if (readerIsEmpty(psc_buf)) return EXIT_FAILURE;
	/* in case the buffer has been read previously  */;
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(ggvoid) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	ggchar c;	/* input symbol */
	i8 state = 0;		/* initial state of the FSM */
	i8 lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	i8 lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	i8 lexLength;		/* token length */
	i8 i;				/* counter */
	
	//ggchar newc;			// new char
	

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		int err_t_ch_index = 0;
		switch (c) {

		/* Cases for spaces */
		case ' ':			
		case '\t':
		case '\f':
			break;
		case '\n':
			line++;
			break;

		/* Cases for symbols */

		case ';':
			currentToken.code = EOS_T;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			return currentToken;
		case ',':
			currentToken.code = COMM_T;
			return currentToken;
		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;
		case '=':
			c = readerGetChar(sourceBuffer);
			if (c == '=') {

				currentToken.code = REL_OP_T;
				currentToken.attribute.relationalOperator = OP_EQ;
				return currentToken;
			}
			while (c != ';')
				c = readerGetChar(sourceBuffer);
			readerRetract(sourceBuffer);
			currentToken.code = ASS_OP_T;
			return currentToken;
		
		case '<':
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_LT;
			return currentToken;

		case '>':
			currentToken.code = REL_OP_T;
			currentToken.attribute.relationalOperator = OP_GT;
			return currentToken;

		case '!':
			
			c = readerGetChar(sourceBuffer);
			if (c == '(')
				break;
			else if (c == '=') {
				currentToken.code = REL_OP_T;
				currentToken.attribute.relationalOperator = OP_NE;
				return currentToken;
			}
			readerRetract(sourceBuffer);
			currentToken.code = LOG_OP_T;
			currentToken.attribute.logicalOperator = OP_NOT;
			return currentToken;
		case '+':
			c = readerGetChar(sourceBuffer);
			if (c == '+') {
				currentToken.code = INCR_T;
				return currentToken;
				}
			readerRetract(sourceBuffer);
			currentToken.code = ART_OP_T;
			currentToken.attribute.arithmeticOperator = OP_ADD;
			return currentToken;

		case '-':
			c = readerGetChar(sourceBuffer);
			if (c == '-') {
				currentToken.code = DECR_T;
				return currentToken;
			}
			readerRetract(sourceBuffer);
			currentToken.code = ART_OP_T;
			currentToken.attribute.arithmeticOperator = OP_SUB;
			return currentToken;

		case '*':
			currentToken.code = ART_OP_T;
			currentToken.attribute.arithmeticOperator = OP_MUL;
			return currentToken;
//do the comments 

		case '|':
			c = readerGetChar(sourceBuffer);
			if (c == '|') {
				currentToken.code = LOG_OP_T;
				currentToken.attribute.logicalOperator = OP_OR;
				return currentToken;
			}
			readerRetract(sourceBuffer);
			c = '|';
			return currentToken;

		case '&':
			c = readerGetChar(sourceBuffer);
			if (c == '&') {
				currentToken.code = LOG_OP_T;
				currentToken.attribute.logicalOperator = OP_AND;
			}
			readerRetract(sourceBuffer);
			c = '&';
			return currentToken;

		case '/':
			c = readerGetChar(sourceBuffer);
			if (c == '/') {
				while (c != '\n') {
					c = readerGetChar(sourceBuffer);
				}
				currentToken.code = CMT_T;
				return currentToken;
			}
			readerRetract(sourceBuffer);
			currentToken.attribute.arithmeticOperator = OP_DIV;
			return currentToken;



		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */

		default: // general case
			// Check if the character is a whitespace or non-identifying character.
			if (isspace(c)) {
				// Skip this character and continue with the next one.
				continue;
			}
			
			state = nextState(state, c);
		
			lexStart = readerGetPosRead(sourceBuffer) - 1;
			readerSetMark(sourceBuffer, lexStart);
			int pos = 0;
			while (stateType[state] == NOFS) {

				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				pos++;
			}
			
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((i8)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer); //xxx
			return currentToken;
} // switch 


	} //while

} // tokenizer


/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 
 /* TO_DO: Just change the datatypes*/ 

i8 nextState(i8 state, ggchar c) {
	i8 col;
	i8 next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */
i8 nextClass(char c) {
	i8 val = -1;
	switch (c) {
	case CHRCOL2:
		val = 2;  // U (Underscore)
		break;
	case CHRCOL3:
		val = 3;  // M ('(')
		break;
	case CHRCOL4:
		val = 4;  // Q ("")
		break;

	case '!':  // New case for '!'
			val = 10;  // Assign a new class index, let's say 10
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 5;  // E (EOF)
		break;

	case ',':
		val = 11;
		break;
	default:
		if (isalpha(c))
			val = 0;  // L (Letter)
		else if (isdigit(c))
			val = 1;  // D (Digit)
		else if (isspace(c))
			val = 8;  // W (Whitespace)
		else
			val = 7;  // O (Other)
	}
	return val;
}



/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

Token funcCMT(string lexeme) {
	Token currentToken = { 0 };
	i8 i = 0, len = (i8)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
	}
	currentToken.code = CMT_T;
	return currentToken;
}


 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(ggchar* lexeme) {
	Token currentToken = { 0 };
	//comment by yaser maybe wrong it was long_mold
	gglong tlong;
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}
	else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			currentToken.attribute.intValue = (i8)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}


/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(ggchar* lexeme) {
	Token currentToken = { 0 };
	size_t length = strlen(lexeme);
	ggchar lastch = lexeme[length - 1];
	i8 isID = FALSE;
	switch (lastch) {
		case MNID_SUF:
			currentToken.code = MNID_T;
			isID = TRUE;
			break;
		default:
			// Test Keyword
			currentToken = funcKEY(lexeme);
			break;
	}
	if (isID == TRUE) {
		strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
		currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	}
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(ggchar* lexeme) {
	Token currentToken = { 0 };
	i8 i = 0, len = (i8)strlen(lexeme);
	currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);
	for (i = 1; i < len - 1; i++) {
		if (lexeme[i] == '\n')
			line++;
		if (!readerAddChar(stringLiteralTable, lexeme[i])) {
			currentToken.code = RTE_T;
			strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
			errorNumber = RTE_CODE;
			return currentToken;
		}
	}
	if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
		currentToken.code = RTE_T;
		strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
		errorNumber = RTE_CODE;
		return currentToken;
	}
	currentToken.code = STR_T;
	return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(ggchar lexeme[]) {
	Token currentToken = { 0 };
	i8 kwindex = -1, j = 0;
	for (j = 0; j < KWT_SIZE; j++)
		if (!strcmp(lexeme, &keywordTable[j][0]))
			kwindex = j;
	if (kwindex != -1) {
		currentToken.code = KW_T;
		currentToken.attribute.codeType = kwindex;

	}

	else if (isalpha(lexeme[0])) {
		currentToken.code = VID_T;
	}
	
	else {
		currentToken.code = ERR_T;
	}
	
	return currentToken;
}


/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */

Token funcErr(string lexeme) {
	Token currentToken = { 0 };
	i8 i = 0, len = (i8)strlen(lexeme);
	if (len > ERR_LEN) {
		strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
		currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
		strcat(currentToken.attribute.errLexeme, "...");
	}
	else {
		strcpy(currentToken.attribute.errLexeme, lexeme);
	}
	for (i = 0; i < len; i++)
		if (lexeme[i] == '\n')
			line++;
	currentToken.code = ERR_T;
	return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

i8 sERR, sSEOF, sMNID, sSTR, sVID, sLPR, sRPR, sLBR, sRBR, sKW, sINCR, sDECR, sASS, sNE, sGT, sEQ, sLT,sFPL, sADD, sSUB, sMUL, sDIV, sAND, sOR, sNOT, sCMT, sEOS,sINL;
ggvoid printToken(Token t) {

	extern ggchar* keywordTable[]; 
	extern numScannerErrors;
	switch (t.code) {
	case RTE_T:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		numScannerErrors++;
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		sSEOF++;
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		sMNID++;
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case STR_T:
		sSTR++;
		printf("STR_T\t\t%d\t ", (i8)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (i8)t.attribute.codeType));
		break;
	case VID_T:
		sVID++;
		printf("VID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case LPR_T:
		sLPR++;
		printf("LPR_T\n");
		break;
	case RPR_T:
		sRPR++;
		printf("RPR_T\n");
		break;
		
	case LBR_T:
		sLBR++;
		printf("LBR_T\n");
		break;
	case RBR_T:
		sRBR++;
		printf("RBR_T\n");
		break;
	case KW_T:
		sKW++;
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case INCR_T:
		sINCR++;
		printf("INCR_T\t\t++%s\n", keywordTable[t.attribute.codeType]);
		break;
	case DECR_T:
		sDECR++;
		printf("DECR_T\t\t--%s\n", keywordTable[t.attribute.codeType]);
		break;
	case ASS_OP_T:
		sASS++;
		printf("ASS_OP_T\t\t=\n");
		break;
	case REL_OP_T:
		switch (t.attribute.relationalOperator) {
		case OP_NE:
			sNE++;
			printf("OP_NE\t\t!=\n");
			break;
		case OP_GT:
			sGT++;
			printf("OP_GT\t\t>\n");
			break;
		case OP_EQ:
			sEQ++;
			printf("OP_EQ\t\t=\n");
			break;

		case OP_LT:
			sLT++;
			printf("OP_LT\t\t<\n");
			break;
		}
		break;
	case FPL_T:
		sFPL++;
		printf("FPL_T\t\t%f\n", t.attribute.floatValue);
		break;

	case INL_T:
		sINL++;
		printf("INL_T\t\t%d\n", t.attribute.intValue);
		break;
	case ART_OP_T:
		switch (t.attribute.arithmeticOperator) {
		case OP_ADD:
			sADD++;
			printf("OP_ADD\t\t+\n");
			break;
		case OP_SUB:
			sSUB++;
			printf("OP_SUB\t\t-\n");
			break;
		case OP_MUL:
			sMUL++;
			printf("OP_MUL\t\t*\n");
			break;
		case OP_DIV:
			sDIV++;
			printf("OP_DIV\t\t/\n");
			break;
		}
		break;
	case LOG_OP_T:
		switch (t.attribute.logicalOperator) {
		case OP_AND:
			sAND++;
			printf("OP_AND\t\t&\n");
			break;

		case OP_OR:
			sOR++;
			printf("OP_OR\t\t|\n");
			break;

		case OP_NOT:
			sNOT++;
			printf("OP_NOT\t\t!\n");
			break;
		}
		break;
	case CMT_T:
		sCMT++;
		printf("CMT_T\n");
		break;
	case EOS_T:
		sEOS++;
		printf("EOS_T\n");
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
ggvoid printScannerData(ScannerData scData) {
	
	
	
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
Token funcType(i8 type, ggchar lexeme[]) {
	Token currentToken = { 0 };
	currentToken.code = type;
	strncpy(currentToken.attribute.idLexeme, lexeme, VID_LEN);
	currentToken.attribute.idLexeme[VID_LEN] = CHARSEOF0;
	return currentToken;
}

Token funcMNID(ggchar lexeme[]) {
	return funcType(MNID_T, lexeme);
}




