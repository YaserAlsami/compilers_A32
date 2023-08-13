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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

ggvoid startParser() {
	/* TO_DO: Initialize Parser data */
	i8 i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
ggvoid matchToken(i8 tokenCode, i8 tokenAttribute) {
	i8 matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
		/*
	case ASS_OP_T: 
			if (lookahead.attribute.codeType != tokenAttribute)
				matchFlag = 0;
		*/
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;

	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	//else
	//	syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
ggvoid syncErrorHandler(i8 syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
ggvoid printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
ggvoid program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
		
	case CMT_T:
		comment();
	case KW_T:
		matchToken(KW_T, KW_fn);

	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(RPR_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			statements();
			optionalStatements();
			
			//dataSession();
			//codeSession();
			matchToken(RBR_T, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
ggvoid comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}


/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
ggvoid optVarListDeclarations() {
	psData.parsHistogram[BNF_optVarListDeclarations]++;
	switch (lookahead.code) {

	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}


/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
ggvoid optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}

		case KW_T:
			switch (lookahead.attribute.codeType) {
			case KW_while:
				
			case KW_if:
				statements();
				break;
			case KW_let:
				statements();
				break;

			default:
				printError();
				break;
			}
			break;
	
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ggvoid statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ggvoid statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}

	

	default:
		; //empty string
	}
}


ggvoid conditionalExpression() {
	OrExpression();
	printf("%s%s\n", STR_LANGNAME, ": Conditional Expression parsed");
}

ggvoid OrExpression() {
	andExpression();
	OrExpressionPrime();
}

ggvoid OrExpressionPrime() {
	if (lookahead.code == LOG_OP_T && lookahead.attribute.logicalOperator == OP_OR) {
		matchToken(LOG_OP_T, OP_OR);
		andExpression();
		OrExpressionPrime();
		printf("%s%s\n", STR_LANGNAME, ": Or Expression parsed");
	}
}

ggvoid andExpression() {
	notExpression();
	andExpressionPrime();
}

ggvoid andExpressionPrime() {
	if (lookahead.code == LOG_OP_T && lookahead.attribute.logicalOperator == OP_AND) {
		matchToken(LOG_OP_T, OP_AND);
		notExpression();
		andExpressionPrime();
		printf("%s%s\n", STR_LANGNAME, ": And Expression parsed");
	}
}

ggvoid notExpression() {
	if (lookahead.code == LOG_OP_T && lookahead.attribute.logicalOperator == OP_NOT) {
		matchToken(LOG_OP_T, OP_NOT);
		relationalExpression();
		printf("%s%s\n", STR_LANGNAME, ": Not Expression parsed");
	}
	else {
		relationalExpression();
	}
}

ggvoid relationalExpression() {
	relationalArithmeticExpression();
}

ggvoid relationalArithmeticExpression() {
	primaryRelationalArithmeticExpression();
	primaryRelationalArithmeticExpressionPrime();
}

ggvoid primaryRelationalArithmeticExpression() {
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, lookahead.attribute.idLexeme);
		break;
	case FPL_T:
		matchToken(FPL_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		printError();
		break;
	}
}

ggvoid primaryRelationalArithmeticExpressionPrime() {
	if (lookahead.code == REL_OP_T) {
		switch (lookahead.attribute.relationalOperator) {
		case OP_EQ:
			matchToken(REL_OP_T, OP_EQ);
			primaryRelationalArithmeticExpression();
			break;
		case OP_NE:
			matchToken(REL_OP_T, OP_NE);
			primaryRelationalArithmeticExpression();
			break;
		case OP_GT:
			matchToken(REL_OP_T, OP_GT);
			primaryRelationalArithmeticExpression();
			break;
		case OP_LT:
			matchToken(REL_OP_T, OP_LT);
			primaryRelationalArithmeticExpression();
			break;
		default:
			printError();
		}
	}
}

ggvoid ifStatement() {
	matchToken(KW_T, KW_if);
	matchToken(STR_T, NO_ATTR);
	conditionalExpression();
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	optionalStatements();
	printf("%s%s\n", STR_LANGNAME, ": if statement parsed");
}

ggvoid whileStatement() {
	matchToken(KW_T, KW_while);
	conditionalExpression();
	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	matchToken(RBR_T, NO_ATTR);
	optionalStatements();
	printf("%s%s\n", STR_LANGNAME, ": while statement parsed");
}



ggvoid  assignmentStatement() {
	switch (lookahead.code) {
	case VID_T:
		matchToken(VID_T, NO_ATTR);
		matchToken(ASS_OP_T, NO_ATTR);

		matchToken(EOS_T, NO_ATTR);
		optionalStatements();
		break;
	default:
		printError();
		break;
	}

	printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ggvoid statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_let:
			lookahead.code = VID_T;
			assignmentStatement();
			break;
		case KW_if:
			ifStatement();
			break;
		case KW_while:
			whileStatement();
			break;
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
		
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
ggvoid outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(MNID_T, NO_ATTR);
	//matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
ggvoid outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
mold_void printBNFData(ParserData psData) {
}
*/
ggvoid printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}



