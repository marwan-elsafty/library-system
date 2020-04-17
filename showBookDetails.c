#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include "dataTypes.h"
#include "utilities.h"


void showBookDetails( char * choiceISBN ) {

	FILE * books = fopen("books.bin", "r");

    // failure check
    if(books==NULL) {
        perror("\a\n\nError");
        getche();
        return;
    }

    bookDataType book;

    // read from original file
    while( fread(&book,sizeof(bookDataType),1,books) ) {

        if( strcmp(book.ISBN , choiceISBN)==0 ) {

	    	printf("\n\n\aBook Details.\n");

	    	printf("\nTitle\t: %s.", book.title);
	    	printf("\nAuthor\t: %s.", book.author);
	    	printf("\nISBN\t: %s", book.ISBN);
	    	printf("\nCopies\t: %d", book.copiesNum);
            printf("\nAvail.\t: %d", book.avalCopiesNum);
	    	printf("\nPub.\t: %d / %d / %d", book.publishDate.day , book.publishDate.month , book.publishDate.year );
	    	printf("\nCateg.\t: %s.", book.category);

	    	getche();
	    	break;
    	}
    }

    fclose(books);
}
