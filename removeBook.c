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


void removeBook() {

    SetConsoleTitle("Library System > Book Menu > Removing Book");

    // declaring a variable of bookDataType so if found, it can be used
    // no need for array
    // writing into files will be instantly
    bookDataType book;

    do{
        system("cls");

        char choiceISBN[20];
        printf("Enter the book's ISBN to remove : ");
        gets(choiceISBN);


        FILE * books = fopen("books.bin", "r");

        // failure check
        if(books==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        FILE * booksTemp = fopen("booksTemp.bin", "w");

        // failure check
        if(booksTemp==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        bool found = false;

        // read from original file
        while( fread(&book,sizeof(bookDataType),1,books) ) {

            if( strcmp(book.ISBN , choiceISBN)!=0 )
                // write into temporary file
                fwrite(&book,sizeof(bookDataType),1,booksTemp);

            else
                found = true;
        }

        fclose(books);
        fclose(booksTemp);

        remove("books.bin");
        rename("booksTemp.bin" , "books.bin");

        showBookDetails(choiceISBN);

        if(found)
            acpMsg("Book removed successfully");

        else
            errMsg("No such ISBN for a book to remove");


    }while( yesNoRequest("remove another book")==true );

    fflush(stdin);
    bookMenu();
}
