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


void searchMember() {

    SetConsoleTitle("Library System > Member Menu > Search Member");

    void choices() {

        system("cls");

        printf("Search Member By :\n\n");

        printf("First Name\t(N)\n");
        printf("ID\t\t(I)\n");
        printf("Borrowings\t(B)\n");
        printf("Phone Number\t(P)\n");
    }


    do {
        char choice[20];

        char choiceName[25];
        char choiceID[20];
        int choiceBorrowings;
        char choicePhone[20];

        bool enteredName = false;
        bool enteredID = false;
        bool enteredBorrowings = false;
        bool enteredPhone = false;

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

                if( choice[i]=='N' || choice[i]=='I' || choice[i]=='B' || choice[i]=='P' || choice[i]=='+' ) {

                    // name
                    if( choice[i]=='N' ) {
                        printf("\nFirst Name : ");
                        strupr(gets(choiceName));

                        enteredName = true;
                        enteredCount++;
                    }

                    // ID
                    else if( choice[i]=='I' ) {
                        printf("\nID : ");
                        strupr(gets(choiceID));

                        enteredID = true;
                        enteredCount++;
                    }

                    // borrowings
                    else if( choice[i]=='B' ) {
                        printf("\nNumber of Borrowings : ");
                        scanf("%i",&choiceBorrowings);
                        getc(stdin);

                        enteredBorrowings = true;
                        enteredCount++;
                    }

                    // phone number
                    else if( choice[i]=='P' ) {
                        printf("\nPhone Number : ");
                        strupr(gets(choicePhone));

                        enteredPhone = true;
                        enteredCount++;
                    }
                }

                else {
                    errMsg("Error!\nusage: enter one of the given choices");
                    break;
                }
            }

        } while ( i<(strlen(choice)-1) );


        // declaring a variable of memberDataType so if found, it can be used
        // no need for array
        // reading from files will be instantly
        memberDataType member;

        FILE * members = fopen("members.bin", "r");

        // failure check
        if(members==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        // read from original file
        while( fread(&member, sizeof(memberDataType), 1, members) ) {

            int specsCount = 0;

            if(enteredName)
                if( strcmp( strupr(member.name.first) , choiceName)==0  )
                    specsCount++;

            if(enteredID)
                if( strcmp( strupr(member.ID) , choiceID)==0  )
                    specsCount++;

            if(enteredBorrowings)
                if( member.borrowedBooks == choiceBorrowings )
                    specsCount++;

            if(enteredPhone)
                if( strcmp( strupr(member.phoneNum) , choicePhone)==0 )
                    specsCount++;


            if(specsCount == enteredCount) {
                found = true;
                showMemberDetails(member.ID);
            }
        }

        fclose(members);


        if(!found)
            errMsg("No such specifications for a member");


    } while ( yesNoRequest("search another member")==true );

    fflush(stdin);
    memberMenu();
}
