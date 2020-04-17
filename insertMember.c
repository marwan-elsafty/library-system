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


void insertMember() {

    SetConsoleTitle("Library System > Member Menu > Inserting New Member");

    // assigning to NULL to facilitate realloc
    // array is needed
    // writing into files will be after inserting all books
    memberDataType * member = NULL;

    
    // for verifications
    bool valid;


    // realloc iterator
    int i=0;
    do {
        system("cls");

        // series of terniry operators for ordinal indicators
        // i.e. 1(st), 2(nd), etc.
        printf("Please, Enter %d%s Member's Details.\n\n", (i+1) , (i+1==1)?"st":(i+1==2)?"nd":(i+1==3)?"rd":"th" );

        member = realloc(member, (i+1)*sizeof(memberDataType) );

        // first name entry
        do {
            printf("\nFirst Name : ");
            strcap(gets(member[i].name.first));

            if( strcmp(member[i].name.first , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(member[i].name.first , "") == 0 );


        // last name entry
        do {
            printf("\nLast Name : ");
            strcap(gets(member[i].name.last));

            if( strcmp(member[i].name.last , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(member[i].name.last , "") == 0 );



        // city entry
        do {
            printf("\nCity : ");
            strcap(gets(member[i].address.city));

            if( strcmp(member[i].address.city , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");

        } while ( strcmp(member[i].address.city , "") == 0 );



        // building entry
        do {
            printf("\nBulding : ");
            scanf("%d",&member[i].address.building);

            if( member[i].address.building<0 )
                errMsg("Error !\nusage: only positive integers are allowed");

        } while ( member[i].address.building<0 );



        // street entry
        do {
            printf("\nStreet : ");
            scanf("%d",&member[i].address.street);

            // avoiding logical errors causes by contiguous scanf and gets
            getc(stdin);

            if( member[i].address.street<0 )
                errMsg("Error !\nusage: only positive integers are allowed");

        } while ( member[i].address.street<0 );



        // ID entry
        do {
            printf("\nID : ");
            gets(member[i].ID);

            valid = duplicateID(member[i].ID);

            if(!valid)
                errMsg("Error !\nThis ID was previously taken.");

            if( strcmp(member[i].ID , "") == 0 )
                errMsg("Error !\nusage: no blank entry allowed");


        } while ( strcmp(member[i].ID , "") == 0 || !valid );



        // check age validity
        do{
            printf("\nAge : ");
            scanf("%d", &member[i].age);
            // avoiding logical errors causes by contiguous scanf and gets
            getc(stdin);

            if( member[i].age<=0 )
                errMsg("Error !\nusage: age must be positive number");

        }while(member[i].age<=0);


        // check phone number validity
        do{
            printf("\nPhone Number (11 digits) : ");
            gets(member[i].phoneNum);

            if( strlen(member[i].phoneNum)!=11 )
                errMsg("Error !\nusage: phone numbers must consist of 11 digit");

            else
                acpMsg("Valid phone number");

        } while ( strlen(member[i].phoneNum)!=11 );


        // check email validity
        do{
            printf("\nE-Mail : ");
            gets(member[i].email);

            valid = isEmail(member[i].email);

            if(valid)
                acpMsg("Valid e-mail address");
            else
                errMsg("Error\ninvalid e-mail address");

        } while(!valid);


        // books number increment
        i++;

    } while( yesNoRequest("add another member")==true );


    FILE * members = fopen("members.bin", "a");

    // failure check
    if(members==NULL) {
        perror("\a\nError");
        getche();
        return;
    }

    int k;
    for(k=0 ; k<i ; k++) {

        // initializing logic values to each structure without user's interfere
        member[k].borrowedBooks = 0;

        fwrite(&member[k] , sizeof(memberDataType) , 1 , members);
    }

    fclose(members);
    free(member);

    fflush(stdin);
    memberMenu();
}
