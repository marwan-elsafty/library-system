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


void searchBook() {

    SetConsoleTitle("Library System > Book Menu > Search Book");

    void choices() {

        system("cls");

        printf("Search Book By :\n\n");

        printf("Book Title\t(T)\n");
        printf("Author Name\t(A)\n");
        printf("ISBN\t\t(I)\n");
        printf("Category\t(C)\n");
    }


    do {
        char choice[20];

        char choiceTitle[50];
        char choiceAuthor[50];
        char choiceISBN[50];
        char choiceCategory[20];

        bool enteredTitle = false;
        bool enteredAuthor = false;
        bool enteredISBN = false;
        bool enteredCategory = false;

        int enteredCount;

        bool found = false;

        // iterator
        // do-while loop exit depends on
        int i;
        do{
            choices();

            printf("\n\n\nYour choice (add '+' for multiple search) : ");
            strupr(gets(choice));

            enteredCount = 0;

            for( i=0 ; i<strlen(choice) ; i++) {

                if( choice[i]=='T' || choice[i]=='A' || choice[i]=='I' || choice[i]=='C' || choice[i]=='+' ) {

                    // title
                    if( choice[i]=='T' ) {
                        printf("\nTitle : ");
                        strupr(gets(choiceTitle));

                        enteredTitle = true;
                        enteredCount++;
                    }

                    // author
                    else if( choice[i]=='A' ) {
                        printf("\nAuthor : ");
                        strupr(gets(choiceAuthor));

                        enteredAuthor = true;
                        enteredCount++;
                    }

                    // ISBN
                    else if( choice[i]=='I' ) {
                        printf("\nISBN : ");
                        strupr(gets(choiceISBN));

                        enteredISBN = true;
                        enteredCount++;
                    }

                    // category
                    else if( choice[i]=='C' ) {
                        printf("\nCategory : ");
                        strupr(gets(choiceCategory));

                        enteredCategory = true;
                        enteredCount++;
                    }
                }

                else {
                    errMsg("Error!\nusage: enter one of the given choices");
                    break;
                }
            }

        } while ( i<(strlen(choice)-1) );


        // declaring a variable of bookDataType so if found, it can be used
        // no need for array
        // writing into files will be instantly
        bookDataType book;

        FILE * books = fopen("books.bin", "r");

        // failure check
        if(books==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        // read from original file
        while( fread(&book,sizeof(bookDataType),1,books) ) {

            int specsCount = 0;

            if(enteredTitle)
                if( strcmp( strupr(book.title) , choiceTitle)==0  )
                    specsCount++;

            if(enteredAuthor)
                if( strcmp( strupr(book.author) , choiceAuthor)==0  )
                    specsCount++;

            if(enteredISBN)
                if( strcmp( strupr(book.ISBN)  , choiceISBN)==0 )
                    specsCount++;

            if(enteredCategory)
                if( strcmp( strupr(book.category) , choiceCategory)==0 )
                    specsCount++;


            if(specsCount == enteredCount){
                found = true;
                showBookDetails(book.ISBN);
            }
        }

        fclose(books);


        if(!found)
            errMsg("No such specifications for a book");


    } while ( yesNoRequest("search another book")==true );

    fflush(stdin);
    bookMenu();
}
