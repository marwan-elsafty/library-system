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


void returnBook() {

    SetConsoleTitle("Library System > Borrow Menu > Returning Book");

    // declaring a variables so if found, it can be used
    // no need for array
    // writing into files will be instantly
    memberDataType member;
    bookDataType book;
    borrowedBookDataType borrowedBook;

    do {
        system("cls");


        char choiceID[20];
        printf("\nEnter member's ID : ");
        gets(choiceID);


        FILE * borrowedBooks = fopen("borrowed-books.bin", "r");

        // failure check
        if(borrowedBooks==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        bool foundBorrower = false;
        int counter = 1;

        // read from original file
        while( fread(&borrowedBook,sizeof(borrowedBookDataType),1,borrowedBooks) ) {

            if( strcmp(borrowedBook.ID , choiceID)==0 ) {

                foundBorrower = true;

                showBorrowedBookDetails( borrowedBook.ISBN , counter );
                counter++;
            }
        }


        // borrower not found
        if(!foundBorrower) {
            errMsg("Error.\nNo borrowed books with such ID");
            borrowMenu();
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        char choiceReturnISBN[20];
        printf("\n\nEnter ISBN to return : ");
        gets(choiceReturnISBN);


        FILE * borrowedBooksTemp = fopen("borrowed-booksTemp.bin", "w");

        // failure check
        if(borrowedBooksTemp==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        while( fread(&borrowedBook,sizeof(borrowedBookDataType),1,borrowedBooks) ) {

            if( strcmp(borrowedBook.ID , choiceReturnISBN)!=0 )

                fwrite(&borrowedBook, sizeof(borrowedBook), 1, borrowedBooksTemp);
        }


        fclose(borrowedBooks);
        fclose(borrowedBooksTemp);

        remove("borrowed-books.bin");
        rename("borrowed-booksTemp.bin","borrowed-books.bin");


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /*
        changing book info
        */

        FILE * books = fopen("books.bin","r");

        // failure check
        if(books==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        FILE * booksTemp = fopen("booksTemp.bin","w");

        // failure check
        if(booksTemp==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        // increment available copies and increment borrowed times
        while( fread(&book, sizeof(bookDataType), 1, books) ) {

            if( strcmp(book.ISBN , choiceReturnISBN)==0 ) {
                book.avalCopiesNum++;
            }

            fwrite(&book,sizeof(book),1,booksTemp);
        }

        fclose(books);
        fclose(booksTemp);

        remove("book.bin");
        rename("booksTemp.bin","books.bin");


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /*
        changing member info
        */


        FILE * members = fopen("members.bin","r");

        // failure check
        if(members==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        FILE * membersTemp = fopen("membersTemp.bin","w");

        // failure check
        if(membersTemp==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        // decrement number of current borrowed books
        while( fread(&member, sizeof(memberDataType) ,1 ,members) ) {

            if (strcmp(member.ID , choiceID)==0 ) {
                member.borrowedBooks--;
            }

            fwrite(&member, sizeof(memberDataType) ,1 ,membersTemp);
        }

        fclose(members);
        fclose(membersTemp);

        remove("members.bin");
        rename("membersTemp.bin","members.bin");


    } while( yesNoRequest("return another book")==true );

    fflush(stdin);
    borrowMenu();
}
