#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "datatypes.h"

#include "myConio.h"



// capitalize first letter in each word of a string
void strcap ( char * str ) {

    int i;
    for(i=0 ; i<strlen(str) ; i++) {

    	// captlize lowercase alphabets if being firt letter or preceded by a space
        if ( ( (i==0) || isspace(str[i-1]) ) && (str[i]>='a') && (str[i]<='z') )
            str[i]=toupper(str[i]);
    }
}



// red error message
void errMsg ( char * message ) {

	textcolor(LIGHTRED);
    fprintf(stderr,"\a\n%s.\n", message);
    textcolor(LIGHTGRAY);
    getche();
}



// green acceptance message
void acpMsg ( char * message ) {

	textcolor(LIGHTGREEN);
    printf("\a\n%s.\n", message);
    textcolor(LIGHTGRAY);
    getche();
}



// check email validity
bool isEmail ( char * email ) {

    int atSymbol=0;
    int topLevelDomain=0;

    int i=0;

    while(email[i]!='\0') {

        // first elemnt in the email string can not be a digit
        if( email[1]>=0 && email[1]<=9 )
            return false;

        else {

            // only digits, lower alphabets, underscore, dashed and dots are allowed
            if( !(email[i]>=0 && email[i]<=9 || email[i]>='a' && email[i]<='z' || email[i]<'_' || email[i]<'.' || email[i]<'-') )
                return false;

            // two contiguous dashes or dots are not allowed
            if( (email[i]>='-' && email[i+1]<='-') || ( email[i]<'.' && email[i+1]<'.') )
                return false;

            // incrementing atSymbol variable every time it appears
            if( email[i]>='a' && email[i]<='z' && email[i+1]=='@' && email[i+2]>='a' && email[i+2]<='z' )
                atSymbol++;

            // incrementing topLevelDomain (.com) variable every time it appears
            if( email[i]=='.' && email[i+1]=='c' && email[i+2]=='o' && email[i+3]=='m' )
                topLevelDomain++;

            if( atSymbol == 1 && topLevelDomain == 1 )
                return true;
        }

        i++;
    }

    return false;
}



// check leap validity
bool isLeap ( int year ) {

     return ( (year%4==0) && (year%100!=0) ) || (year%400==0);
}



// check date validity
bool isDate ( int day, int month, int year ) {

    // constants
    const int MAX_VALID_YEAR = 9999;
    const int MIN_VALID_YEAR = 0001;


    // year, month or day are not in given range
    if (year > MAX_VALID_YEAR || year < MIN_VALID_YEAR)
      return false;

    if (month < 1 || month > 12)
      return false;

    if (day < 1 || day > 31)
      return false;


    // february
    if (month == 2) {

        if (isLeap(year))
           return (day <= 29);

        else
           return (day <= 28);
    }


    // april, june, sept and nov, have number of days less than or equal to 30
    if (month==4 || month==6 || month==9 || month==11)
        return (day <= 30);

    return true;
}



// takes string for questioning purpose
bool yesNoRequest( char * question ) {

    // string instead of a char for run-time error
    char choice[5];

    do{
        system("cls");

        printf("\a\nDo you want to %s ? (Y/N) : ",question);
        gets(choice);

        // converts string into uppercase
        strupr(choice);


        // exit
        if( strcmp(choice,"NO")==0 || strcmp(choice,"N")==0 )
            return false;

        // cont
        else if(strcmp(choice,"YES")==0 || strcmp(choice,"Y")==0)
            return true;

        else {
            fprintf(stderr, "\a\n\nError!\nusage: enter one of the given choices.");
            getche();
        }

    }while( strcmp(choice,"N")!=0 && strcmp(choice,"Y")!=0
            && strcmp(choice,"NO")!=0 && strcmp(choice,"YES")!=0 );
}


void initBookTempDataBase() {

    bookDataType book;


    FILE * books = fopen("books.bin", "r");

    // failure check
    if(books==NULL)
        return;

    FILE * booksTempDataBase = fopen("booksTempDatabase.bin", "w");

    // failure check
    if(booksTempDataBase==NULL)
        return;


    // read from original file
    while( fread(&book, sizeof(bookDataType), 1, books) ) {

            // write into temporary file
            fwrite(&book, sizeof(bookDataType), 1, booksTempDataBase);
    }

    fclose(books);
    fclose(booksTempDataBase);
}


void initBorrowedBookTempDataBase() {

    borrowedBookDataType borrowedBook;


    FILE * borrowedBooks = fopen("borrowed-books.bin", "r");

    // failure check
    if(borrowedBooks==NULL)
        return;

    FILE * borrowedBooksTempDataBase = fopen("borrowedBooksTempDatabase.bin", "w");

    // failure check
    if(borrowedBooksTempDataBase==NULL)
        return;


    // read from original file
    while( fread(&borrowedBook, sizeof(borrowedBookDataType), 1, borrowedBooks) ) {

            // write into temporary file
            fwrite(&borrowedBook, sizeof(borrowedBookDataType), 1, borrowedBooksTempDataBase);
    }

    fclose(borrowedBooks);
    fclose(borrowedBooksTempDataBase);
}


void initMemberTempDataBase() {

    memberDataType member;


    FILE * members = fopen("members.bin", "r");

    // failure check
    if(members==NULL)
        return;

    FILE * membersTempDataBase = fopen("membersTempDatabase.bin", "w");

    // failure check
    if(membersTempDataBase==NULL)
        return;


    // read from original file
    while( fread(&member, sizeof(memberDataType), 1, members) ) {

            // write into temporary file
            fwrite(&member, sizeof(memberDataType), 1, membersTempDataBase);
    }

    fclose(members);
    fclose(membersTempDataBase);
}


void initTempDataBase() {

    initBookTempDataBase();
    initBorrowedBookTempDataBase();
    initMemberTempDataBase();
}


void terminateTempDataBase( bool save ) {

	if(save) {

		remove("booksTempDatabase.bin");
		remove("borrowedBooksTempDatabase.bin");
		remove("membersTempDatabase.bin");
	}


	// recover old database
	else {

		remove("books.bin");
		remove("borrowed-books.bin");
		remove("members.bin");

		rename("membersTempDatabase.bin" , "members.bin");
		rename("borrowedBooksTempDatabase.bin" , "borrowed-books.bin");
		rename("booksTempDatabase.bin" , "books.bin");
	}
}
