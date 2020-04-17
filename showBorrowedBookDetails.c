#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include "dataTypes.h"
#include "utilities.h"


void showBorrowedBookDetails ( char * choiceID , int counter ) {

    FILE * books = fopen("books.bin", "r");

    // failure check
    if(books==NULL) {
        perror("\a\n\nError");
        getche();
        return;
    }

	FILE * borrowedBooks = fopen("borrowed-books.bin", "r");

    // failure check
    if(borrowedBooks==NULL) {
        perror("\a\n\nError");
        getche();
        return;
    }

    bookDataType book;
    borrowedBookDataType borrowedBook;

    time_t todDate;
    time(&todDate);

    // read from original file
    while( fread(&borrowedBook,sizeof(borrowedBookDataType),1,borrowedBooks) ) {

        if( strcmp(borrowedBook.ID , choiceID)==0 ) {

	    	printf("\n\nBorrowed Book %d Details.\n",counter);

	    	// printing book's title from bookDataType since borrowedBookDataType does not contain title
            while( fread(&book,sizeof(bookDataType),1,books) ) {
                if( strcmp(book.ISBN , borrowedBook.ISBN)==0 ) {
                    printf("\nTitle\t\t: %s", book.title);
                    break;
                }
            }

	    	// printing rest of book details from borrowedBookDataType
            printf("\nISBN\t\t: %s", borrowedBook.ISBN);
	    	printf("\nBorrow Date\t: %s", ctime(&borrowedBook.borrowDate));
	    	printf("Due Date\t: %s %s", ctime(&borrowedBook.dueDate) , (difftime(todDate,borrowedBook.dueDate)>=0)? "(Overdue)" : "" );

	    	getche();
	    	break;
    	}
    }

    fclose(books);
    fclose(borrowedBooks);
}
