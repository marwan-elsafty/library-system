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


void insertBook() {

    SetConsoleTitle("Library System > Book Menu > Inserting New Book");

    // assigning to NULL to facilitate realloc
    // array is needed
    // writing into files will be after inserting all books
    bookDataType * book = NULL;

    // for verifications
    bool valid;


    // realloc iterator
    int i=0;
    do {
        system("cls");

        // series of terniry operators for ordinal indicators
        // i.e. 1(st), 2(nd), etc.
        printf("Please, Enter %d%s Book Details.\n\n", (i+1) , (i+1==1)?"st":(i+1==2)?"nd":(i+1==3)?"rd":"th" );

        book = realloc(book, (i+1)*sizeof(bookDataType) );

        // title entry
        do {
            printf("\nTitle : ");
            strcap(gets(book[i].title));

            if( strcmp(book[i].title , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book[i].title , "") == 0 );



        // author entry
        do {
            printf("\nAuthor : ");
            strcap(gets(book[i].author));

            if( strcmp(book[i].author , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book[i].author , "") == 0 );



        // publisher entry
        do {
            printf("\nPublisher : ");
            strcap(gets(book[i].publisher));

            if( strcmp(book[i].publisher , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book[i].publisher , "") == 0 );



        // ISBN entry
        do {
            printf("\nISBN : ");
            gets(book[i].ISBN);

            valid = duplicateISBN(book[i].ISBN);

            if(!valid)
                errMsg("Error !\nThis ISBN was previously taken.");

            if( strcmp(book[i].ISBN , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

            //else if( strlen(book[i].ISBN)!=9 || strlen(book[i].ISBN)!=13 )
                //errMsg("Error !\nusage: ISBN must be 9 (UK) or 13 (UK) character");

        } while ( strcmp(book[i].ISBN , "") == 0 || !valid );



        // publiah date entry
        printf("\nDate of Publish.");
        do {
            // assure being initialized if user skipped
            book[i].publishDate.day   = 1;
            book[i].publishDate.month = 1;
            book[i].publishDate.year  = 1;

            printf("\nDay\t: ");
            scanf("%d",&book[i].publishDate.day);

            printf("Month\t: ");
            scanf("%d",&book[i].publishDate.month);

            printf("Year\t: ");
            scanf("%d",&book[i].publishDate.year);

            valid = isDate(book[i].publishDate.day, book[i].publishDate.month, book[i].publishDate.year);

            if(!valid)
                errMsg("Error !\nusage: not a valid date");

        } while (!valid);



        // number of copies entry
        do {
            printf("\nNo of Copies : ");
            scanf("%d", &book[i].copiesNum);
            getc(stdin);

            if( book[i].copiesNum < 0 )
                errMsg("Error !\nusage: copies number >= 0");

        } while ( book[i].copiesNum < 0 );



        // category entry
        do {
            printf("\nCategory: ");
            strcap(gets(book[i].category));

            if( strcmp(book[i].category , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(book[i].category , "") == 0 );


        // members number increment
        i++;

    } while( yesNoRequest("insert another book")==true );


    FILE * books = fopen("books.bin", "a");

    // failure check
    if(books==NULL) {
        perror("\a\nError");
        getche();
        return;
    }

    int k;
    for(k=0 ; k<i ; k++) {

        // initializing logic values to each structure without user's interfere
        book[k].borrowed=0;
        book[k].avalCopiesNum = book[k].copiesNum;

        fwrite(&book[k] , sizeof(bookDataType) , 1 , books);
    }

    fclose(books);
    free(book);

    fflush(stdin);
    bookMenu();
}
