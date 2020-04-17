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


void removeMember() {

    SetConsoleTitle("Library System > Member Menu > Removing Member");

    // declaring a variable of memberDataType so if found, it can be used
    // no need for array
    // writing into files will be instantly
    memberDataType member;

    do{
        system("cls");

        char choiceID[20];
        printf("Enter member's ID to remove : ");
        gets(choiceID);


        FILE * members = fopen("members.bin", "r");

        // failure check
        if(members==NULL) {
            perror("\a\nError");
            getche();
            return;
        }

        FILE * membersTemp = fopen("membersTemp.bin", "w");

        // failure check
        if(membersTemp==NULL) {
            perror("\a\nError");
            getche();
            return;
        }


        bool found = false;

        // read from original file
        while( fread(&member,sizeof(memberDataType),1,members) ) {

            if( strcmp(member.ID , choiceID)!=0 )
                // write into temporary file
                fwrite(&member,sizeof(memberDataType),1,membersTemp);

            // found member
            else {

                // having non-returned borrowed books
                if ( member.borrowedBooks>0 )
                    fprintf(stderr, "\a\n\n%s is borrowing %d books. Can not remove now until returning them.", member.name.first, member.borrowedBooks );

                else
                    found = true;
            }
        }

        fclose(members);
        fclose(membersTemp);

        remove("members.bin");
        rename("membersTemp.bin" , "members.bin");

        showMemberDetails(choiceID);

        if(found)
            acpMsg("Member removed successfully");

        else
            errMsg("No such ID for a member to remove");


    }while( yesNoRequest("remove another member")==true );

    fflush(stdin);
    memberMenu();
}
