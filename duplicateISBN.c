#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#include "book.h"
#include "dataTypes.h"
#include "utilities.h"

bool duplicateISBN ( char * enteredISBN ) {

	FILE * books = fopen("books.bin", "r");

    // failure check
    if(books==NULL)
        // no previous files available
        // thus no previous ISBN entered
        return true;

    bookDataType book;

    // read from original file
    while( fread(&book,sizeof(bookDataType),1,books) ) {

        if( strcmp(book.ISBN , enteredISBN)==0 ) {

            fclose(books);
	    	return false;
        }
    }

    fclose(books);
    return true;
}
