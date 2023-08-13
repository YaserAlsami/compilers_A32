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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

ReaderPointer readerCreate(i8 size, i8 increment, i8 mode) {
	ReaderPointer readerPointer;

	/* TO_DO: Defensive programming */
	if (size < 0) {
		// Handle invalid size
		return NULL;
	}
	if (increment < 0) {
		// Handle invalid increment
		return NULL;
	}

	// Adjust values based on parameters if necessary
	if (size == 0) {
		size = READER_DEFAULT_SIZE;
	}
	if (increment == 0) {
		increment = READER_DEFAULT_INCREMENT;
	}
	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI) {
		mode = MODE_FIXED;
	}

	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	if (!readerPointer) {
		// Handle allocation failure
		return NULL;
	}

	readerPointer->content = (ggchar*)malloc(size );
	if (!readerPointer->content) {
		// Handle allocation failure
		free(readerPointer);
		return NULL;
	}

	/* TO_DO: Initialize the histogram */
	// Initialize the histogram array with appropriate values

	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;

	/* TO_DO: Initialize flags */
	// Initialize the flags according to the desired initial state

	/* TO_DO: The created flag must be signaled as EMP */
	readerPointer->flags = READER_DEFAULT_FLAG;

	return readerPointer;
}




/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, ggchar ch) {
	ggchar* tempReader = NULL; // dooooooooooo the string
	i8 newSize = 0;

	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return NULL;
	}

	/* TO_DO: Reset Reallocation */
	readerPointer->flags = readerPointer->flags & RST_FLAG_RLC;



	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->offset.wrte * sizeof(ggchar) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	}
	else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags = readerPointer->flags & RST_FLAG_FUL;

		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize <= readerPointer->size) {
				return NULL;
			}
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment;
			/* TO_DO: Defensive programming */
			if (newSize <= readerPointer->size) {
				return NULL;
			}
			break;
		default:
			return NULL;
		}

		/* TO_DO: New reader allocation */
		tempReader = (char*)realloc(readerPointer->content, newSize );
		/* TO_DO: Defensive programming */
		if (tempReader == NULL) {
			return NULL;
		}

		/* TO_DO: Check Relocation */
		if (tempReader != readerPointer->content) {
			readerPointer->flags |= READER_REL;
		}

		readerPointer->flags = readerPointer->flags | SET_FLAG_RLC;
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
	}

	/* TO_DO: Add the char */
	readerPointer->content[readerPointer->offset.wrte++] = ch;

	/* TO_DO: Updates histogram */
	readerPointer->histogram[(int)ch]++;
	/* ... */

	return readerPointer;
}

bool readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}

	/* TO_DO: Adjust flags original */
	readerPointer->offset.wrte = readerPointer->offset.mark = readerPointer->offset.read = 0;
	readerPointer->flags = readerPointer->flags & RST_FLAG_END;
	readerPointer->flags = readerPointer->flags & RST_FLAG_RLC;

	return TRUE;
}

bool readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}

	/* TO_DO: Free pointers */
	free(readerPointer->content);
	free(readerPointer);

	return TRUE;
}


bool readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}

	/* TO_DO: Check flag if buffer is FUL */
	return ((readerPointer->flags & READER_MAX_SIZE
		) != 0);
}



bool readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return TRUE;
	}

	/* TO_DO: Check flag if buffer is EMP */
	return ((readerPointer->flags & READER_DEFAULT_FLAG) != 0);
}


bool readerSetMark(ReaderPointer const readerPointer, i8 mark) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || mark < 0 || mark > readerPointer->offset.wrte) {
		return FALSE;
	}

	/* TO_DO: Adjust mark */
	readerPointer->offset.mark = mark;
	return TRUE;
}


i8 readerPrint(ReaderPointer const readerPointer) {
	i8 cont = 0;
	ggchar c;
	/* TO_DO: Defensive programming (including invalid chars) */
	if (readerPointer == NULL) {
		return 0;
	}

	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->offset.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	readerPointer->flags = readerPointer->flags | SET_FLAG_END;

	return cont;
}
/*
i8 readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	i8 size = 0;
	ggchar c;

	if (readerPointer == NULL || fileDescriptor == NULL) {
		return 0;
	}

	c = (ggchar)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	return size;
} */

i8 readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	i8 size = 0;
	ggchar c;

	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || fileDescriptor == NULL) {
		return 0;
	}

	c = (ggchar)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			fclose(fileDescriptor);  // Close the file descriptor before returning an error
			return READER_ERROR;
		}
		c = (ggchar)fgetc(fileDescriptor);
		size++;

		/* TO_DO: Check buffer size limit */
		if (size >= readerPointer->size) {
			// Perform buffer reallocation to accommodate more content
			readerPointer->size += readerPointer->increment;

			ggchar* temp = realloc(readerPointer->content, readerPointer->size * sizeof(ggchar));
			if (temp == NULL) {
				fclose(fileDescriptor);  // Close the file descriptor before returning an error
				return READER_ERROR;
			}
			else {
				readerPointer->content = temp;
			}
		}
	}

	fclose(fileDescriptor);  // Close the file descriptor after reading the entire file
	return size;
}




bool readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}

	/* TO_DO: Recover positions */
	readerPointer->offset.read = 0;
	readerPointer->offset.mark = 0;

	return TRUE;
}

bool readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}

	/* TO_DO: Retract (return 1 pos read) */
	if (readerPointer->offset.read > 0) {
		readerPointer->offset.read--;
	}

	return TRUE;
}


bool readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return FALSE;
	}

	/* TO_DO: Restore positions (read/mark) */
	readerPointer->offset.read = readerPointer->offset.mark;

	return TRUE;
}


ggchar readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || readerPointer->content == NULL) {
		// Handle error or return a default value
		return FALSE;
	}

	/* TO_DO: Check condition to read/wrte */
	if (readerPointer->offset.read == readerPointer->offset.wrte) {
		// Handle end of buffer condition or return a default value
		readerPointer->flags = readerPointer->flags | SET_FLAG_END;

		return '\0';
	}

	/* TO_DO: Set EOB flag */

	/* TO_DO: Reset EOB flag */
	readerPointer->flags = readerPointer->flags & RST_FLAG_END;

	return readerPointer->content[readerPointer->offset.read++];
}



ggchar* readerGetContent(ReaderPointer const readerPointer, i8 pos) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || readerPointer->content == NULL) {
		// Handle error or return NULL
		return NULL;
	}

	/* TO_DO: Check boundary conditions */
	if (pos < 0 || pos >= readerPointer->offset.wrte) {
		// Handle out-of-bounds position or return NULL
		return NULL;
	}

	/* TO_DO: Return content (string) */
	return readerPointer->content+pos;
}



i8 readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Return read */
	return readerPointer->offset.read;
}



i8 readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Return wrte */
	return readerPointer->offset.wrte;
}


i8 readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Return mark */
	return readerPointer->offset.mark;
}


i8 readerGetSize(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Return size */
	return readerPointer->size;
}


i8 readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Return increment */
	return readerPointer->increment;
}


i8 readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Return mode */
	return readerPointer->mode;
}

bool readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Return flags */
	return readerPointer->flags;
}

void readerPrintStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL || readerPointer->content == NULL) {
		// Handle error or return
		return;
	}

	i8 charFreq[256] = { 0 };  // Array to store character frequencies

	// Count the frequency of each character
	for (i8 i = 0; i < readerPointer->offset.wrte; i++) {
		gg_bool c = (gg_bool)readerPointer->content[i];
		charFreq[c]++;
	}

	// Print the histogram
	printf("Character Statistics:\n");
	for (i8 i = 0; i < 256; i++) {
		if (charFreq[i] > 0) {
			printf("%c: %d\n", (ggchar)i, charFreq[i]);
		}
	}
}


i8 readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		// Handle error or return a default value
		return 0;
	}

	/* TO_DO: Returns the number of errors */
	return readerPointer->numReaderErrors;
}
