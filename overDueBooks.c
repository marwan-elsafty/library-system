#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "book.h"
#include "member.h"
#include "admin.h"
#include "menu.h"
#include "dataTypes.h"
#include "utilities.h"


void overDueBooks() {

    SetConsoleTitle("Library System > Admin Menu > Over Due Books");

    system("cls");

    // declaring a variable of bookDataType so if found, it can be used
    // no need for array
    // reading from files will be instantly
    borrowedBookDataType book;


    FILE * borrowedBooks = fopen("borrowed-books.bin", "r");

    // failure check
    if(borrowedBooks==NULL) {
        perror("\a\nError");
        getche();
        return;
    }


    bool found = false;

    time_t todDate;
    time(&todDate);

    // read from original file
    while( fread(&book,sizeof(borrowedBookDataType),1,borrowedBooks) ) {

    	if( difftime(todDate,book.dueDate)>=0 ) {
			found = true;
    		showBookDetails(book.ISBN);
    	}
    }

    if(!found)
    	acpMsg("No overdue books found");


    fclose(borrowedBooks);

    getche();

    fflush(stdin);
    adminMenu();
}
