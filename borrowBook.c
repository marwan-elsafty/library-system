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


void borrowBook() {

    SetConsoleTitle("Library System > Borrow Menu > Borrowing Book");

    memberDataType member;
    bookDataType book;
    borrowedBookDataType borrowedBook;

    do {
        system("cls");


        /*
        ISBN check
        */

        char choiceISBN[20];
        printf("\nEnter book's ISBN to borrow : ");
        gets(choiceISBN);

        FILE * books = fopen("books.bin", "r");

        // failure check
        if(books==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        // initializing search attempt to false to modify if found
        bool foundBook = false;

        // check ISBN availability
        while( fread(&book, sizeof(bookDataType) ,1 ,books) ) {

            if( strcmp(book.ISBN , choiceISBN)==0 ) {

                foundBook = true;

                if(book.avalCopiesNum==0) {
                    errMsg("There's no available copies of this book");
                    borrowMenu();
                }

                else
                    break;
            }
        }

        fclose(books);

        // ISBN not found
        if(!foundBook) {
            errMsg("Error.\nNo such ISBN for a book found");
            borrowMenu();
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /*
        ID check
        */

        char choiceID[40];
        printf("\nEnter member's ID : ");
        gets(choiceID);


        FILE * members = fopen("members.bin", "r");

        // failure check
        if(members==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        // initializing search attempt to false to modify if found
        bool foundMember = false;

        // check number of already borrowed books by member
        while( fread(&member, sizeof(memberDataType), 1, members) ) {

            if( strcmp(member.ID , choiceID)==0 ) {

                foundMember = true;

                if(member.borrowedBooks==3) {
                    errMsg("This user has reached the limit of borrowed number of books");
                    borrowMenu();
                }

                else
                    break;
            }
        }

        if(!foundMember) {
            errMsg("Error.\nNo such ID for a member found");
            borrowMenu();
        }

        fclose(members);


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /*
        initializing borrowedBook
        */

        strcpy(borrowedBook.ISBN , choiceISBN);
        strcpy(borrowedBook.ID , choiceID);

        int days;

        // borrowing days
        do  {
            printf("\nEnter days to be borrowed ? (21 max) : ");
            scanf("%d",&days);

            if( days<=0 || days>21 )
                errMsg("Error.\nBorrowing days must range within 0<days<22");

        }while( days<=0 || days>21 );


        // instant local date
        time_t borrowTime;
        borrowedBook.borrowDate = time(&borrowTime);

        // due date
        // time is taken in seconds
        time_t dueDate;
        dueDate = borrowTime + (days*24*60*60);
        borrowedBook.dueDate = dueDate;


        FILE * borrowedBooks = fopen("borrowed-books.bin", "a");

        // failure check
        if(borrowedBooks==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        // save info
        fwrite(&borrowedBook, sizeof(borrowedBook), 1, borrowedBooks);

        fclose(borrowedBooks);


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /*
        changing book info
        */

        books = fopen("books.bin","r");

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

        // decrement available copies and increment borrowed times
        while( fread(&book, sizeof(bookDataType), 1, books) ) {

            if( strcmp(book.ISBN , choiceISBN)==0 ) {
                book.avalCopiesNum--;
                book.borrowed++;
            }

            fwrite(&book,sizeof(bookDataType),1,booksTemp);
        }

        fclose(books);
        fclose(booksTemp);

        remove("books.bin");
        rename("booksTemp.bin","books.bin");


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /*
        changing member info
        */

        members = fopen("members.bin","r");

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


        // increment number of current borrowed books
        while( fread(&member, sizeof(memberDataType) ,1 ,members) ) {

            if (strcmp(member.ID , choiceID)==0 ) {
                member.borrowedBooks++;
            }

            fwrite(&member, sizeof(memberDataType) ,1 ,membersTemp);
        }

        fclose(members);
        fclose(membersTemp);

        remove("members.bin");
        rename("membersTemp.bin","members.bin");

        getc(stdin);
        getche();

    } while( yesNoRequest("borrow another book")==true );

    fflush(stdin);
    borrowMenu();
}
