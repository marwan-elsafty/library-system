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

#include "myConio.h"


void addBook() {

    SetConsoleTitle("Library System > Book Menu > Adding Book");

    do{
        system("cls");

        // declaring a variable of bookDataType so if found, it can be used
        // no need for array
        // writing into files will be instantly
        bookDataType book;

        char choiceISBN[20];
        printf("Enter the book's ISBN to add : ");
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

            if( strcmp(book.ISBN , choiceISBN)==0 ) {

                found = true;

                int addedCopiesNum;

                do {
                    printf("\nEnter number of copies to add : ");
                    scanf("%d",&addedCopiesNum);

                    if(addedCopiesNum<0)
                        errMsg("Error !\nusage: enter positive integer.");

                } while(addedCopiesNum<0);

                // added copies are added to total number of books thus available copies increase also
                book.copiesNum += addedCopiesNum;
                book.avalCopiesNum += addedCopiesNum;
            }

            // write into temporary file
            fwrite(&book,sizeof(bookDataType),1,booksTemp);
        }

        fclose(books);
        fclose(booksTemp);

        remove("books.bin");
        rename("booksTemp.bin" , "books.bin");

        showBookDetails(choiceISBN);

        if(found) {
            system("cls");
            acpMsg("Data updated successfully");
        }

        else
            errMsg("No such ISBN for a book to add");

        getc(stdin);

    }while( yesNoRequest("add another book")==true );

    fflush(stdin);
    bookMenu();
}
