/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2023
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
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferReader*	stringLiteralTable;
extern i8				line;
extern Token			tokenizer();
extern string			keywordTable[KWT_SIZE];
static i8				syntaxErrorNumber = 0;

#define LANG_WRTE		"println!("
#define LANG_READ		"input&"
#define LANG_MAIN		"main("

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_extern,
	KW_false,
	KW_true,
	KW_print,
	KW_fn,
	KW_for,
	KW_if,
	KW_let,
	KW_else,
	KW_while,
	KW_do,
	KW_i8,
	KW_int,
	KW_code,
	KW_data
};


/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 12

/* Parser */
typedef struct parserData {
	i8 parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
i8 numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
ggvoid startParser();
ggvoid matchToken(i8, i8);
ggvoid syncErrorHandler(i8);
ggvoid printError();
ggvoid printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_codeSession,								/*  1 */
	BNF_comment,									/*  2 */
	BNF_dataSession,								/*  3 */
	BNF_optVarListDeclarations,						/*  4 */
	BNF_optionalStatements,							/*  5 */
	BNF_outputStatement,							/*  6 */
	BNF_outputVariableList,							/*  7 */
	BNF_program,									/*  8 */
	BNF_statement,									/*  9 */
	BNF_statements,									/* 10 */
	BNF_statementsPrime								/* 11 */
};


/* TO_DO: Define the list of keywords */
static string BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_codeSession",
	"BNF_comment",
	"BNF_dataSession",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime"
};

/* TO_DO: Place ALL non-terminal function declarations */
ggvoid comment();
ggvoid optVarListDeclarations();
ggvoid optionalStatements();
ggvoid outputStatement();
ggvoid outputVariableList();
ggvoid program();
ggvoid statement();
ggvoid statements();
ggvoid statementsPrime();
ggvoid conditionalExpression();
ggvoid ifStatement();
ggvoid whileStatement();
ggvoid conditionalExpression();
ggvoid OrExpression();
ggvoid OrExpressionPrime();
ggvoid andExpression();
ggvoid andExpressionPrime();
ggvoid notExpression();
ggvoid relationalExpression();
ggvoid relationalArithmeticExpression();
ggvoid primaryRelationalArithmeticExpression();
ggvoid primaryRelationalArithmeticExpressionPrime();

#endif
