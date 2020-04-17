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


void mostPopularBooks() {

    SetConsoleTitle("Library System > Admin Menu > Most Popular Books");

    system("cls");


    FILE * books = fopen("books.bin", "r");

    // failure check
    if(books==NULL) {
        perror("\a\nError");
        getche();
        return;
    }

    bookDataType bookBuffer;
    bookDataType * book = NULL;

    int i=0;

    // read from original file
    while( fread(&bookBuffer,sizeof(bookDataType),1,books) ) {

        book = realloc(book, (i+1)*sizeof(bookDataType) );
        book[i] = bookBuffer;

        i++;
    }

    fclose(books);


    bookDataType temp;

    // bubble sort
    int j,k;
    for(j=0 ; j<(i-1) ; j++)
        for(k=0 ; k<(i-1) ;k++)
            if( book[k].borrowed < book[k+1].borrowed ) {
                temp = book[k];
                book[k] = book[k+1];
                book[k+1] = temp;
            }


    // table header
    printf("\n #  ");

    printf("Title\t\t\t");
    printf("Author\t\t\t");
    printf("ISBN\t\t");
    printf("Borrowed\n\n\n");


    int top=5;
    int rank=1;

    // table printing
    for(j=1 ; j<=top , j<=i ; j++) {

        // to avoid not taking duplication
        // i.e. 5th and 6th are same at value
        if( (j>=5) && (book[j-1].borrowed == book[j].borrowed) )
            top++;

        printf("%2d  ", (j==1) ? 1 : (book[j-1].borrowed == book[j].borrowed) ? rank : ++rank );

        printf("%.50s\t", book[j-1].title );
        printf("%.30s\t\t", book[j-1].author );
        printf("%.20s\t", book[j-1].ISBN );
        printf("%8d\n", book[j-1].borrowed );
    }

    free(book);

    getche();

    fflush(stdin);
    adminMenu();
}
