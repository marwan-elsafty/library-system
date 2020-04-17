#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "book.h"
#include "member.h"
#include "admin.h"
#include "menu.h"
#include "utilities.h"


void header(){
    system("cls");
    printf("\n -------------------------- Welcome to Library System --------------------------\n\n");
}



void mainMenu(){

    SetConsoleTitle("Library System");

    header();

    printf("Book\t(B)\n");
    printf("Member\t(M)\n");
    printf("Borrow\t(BR)\n");
    printf("Admin\t(A)\n");

    printf("\nSave\t(S)\n");
    printf("Exit\t(E)\n");

    char choice[20];

   do{

        printf("\n\n\nYour choice : ");
        strupr(gets(choice));

        if( strcmp(choice,"B")==0 )
            bookMenu();

        else if( strcmp(choice,"M")==0 )
            memberMenu();

        else if( strcmp(choice,"BR")==0 )
            borrowMenu();

        else if( strcmp(choice,"A")==0 )
            adminMenu();

        else if( strcmp(choice,"S")==0 ) {
            terminateTempDataBase(true);
            initTempDataBase();
            acpMsg("Data saved successfully");
            mainMenu();
        }

        else if( strcmp(choice,"E")==0 )
            exitMenu();


        else{
            errMsg("Error!\nusage: enter one of the given choices");
            mainMenu();
        }

    }while( strcmp(choice,"B")!=0 && strcmp(choice,"M")!=0
            && strcmp(choice,"BR")!=0 && strcmp(choice,"A")!=0
            && strcmp(choice,"S")!=0 && strcmp(choice,"E")!=0 );
}



void bookMenu(){

    SetConsoleTitle("Library System > Book Menu");

    header();

    printf("Insert\t(I)\n");
    printf("Search\t(S)\n");
    printf("Add\t(A)\n");
    printf("Delete\t(D)\n");

    printf("\nBack\t(B)\n");

    char choice[20];

    do{
        printf("\n\n\nYour choice : ");
        strupr(gets(choice));

        if( strcmp(choice,"I")==0 )
            insertBook();

        else if( strcmp(choice,"S")==0 )
            searchBook();

        else if( strcmp(choice,"A")==0 )
            addBook();

        else if( strcmp(choice,"D")==0 )
            removeBook();

        else if( strcmp(choice,"B")==0 )
            mainMenu();

        else {
            errMsg("\n\aError!\nusage: enter one of the given choices");
            bookMenu();
        }

    }while( strcmp(choice,"I")!=0 && strcmp(choice,"S")!=0
            && strcmp(choice,"A")!=0 && strcmp(choice,"D")!=0
            && strcmp(choice,"B")!=0);
}



void memberMenu() {

    SetConsoleTitle("Library System > Member Menu");

    header();

    printf("Registration\t(RG)\n");
    printf("Search\t\t(S)\n");
    printf("Remove Member\t(RM)\n");

    printf("\nBack\t\t(B)\n");

    char choice[20];

    do{
        printf("\n\n\nYour choice : ");
        strupr(gets(choice));

        if( strcmp(choice,"RG")==0 )
            insertMember();

        else if( strcmp(choice,"S")==0 )
            searchMember();

        else if( strcmp(choice,"RM")==0 )
            removeMember();

        else if( strcmp(choice,"B")==0 )
            mainMenu();

        else {
            errMsg("Error!\nusage: enter one of the given choices");
            memberMenu();
        }

    }while( strcmp(choice,"RG")!=0 && strcmp(choice,"S")!=0
            && strcmp(choice,"RM")!=0 && strcmp(choice,"B")!=0 );
}



void borrowMenu() {

    SetConsoleTitle("Library System > Borrow Menu");

    header();

    printf("Borrow Book\t(BR)\n");
    printf("Return Book\t(RT)\n");

    printf("\nBack\t\t(B)\n");

    char choice[20];

    do{
        printf("\n\n\nYour choice : ");
        strupr(gets(choice));

        if( strcmp(choice,"BR")==0 )
            borrowBook();

        else if( strcmp(choice,"RT")==0 )
            returnBook();


        else if( strcmp(choice,"B")==0 )
            mainMenu();

        else {
            errMsg("Error!\nusage: enter one of the given choices");
            borrowMenu();
        }

    }while( strcmp(choice,"BR")!=0 && strcmp(choice,"RT")!=0
            && strcmp(choice,"B")!=0 );
}



void adminMenu(){

    SetConsoleTitle("Library System > Admin Menu");

    header();

    printf("Overdue Books\t\t(O)\n");
    printf("Most Popular Books\t(M)\n");

    printf("\nBack\t\t\t(B)\n");

    char choice[20];

    do{
        printf("\n\n\nYour choice : ");
        strupr(gets(choice));

        if( strcmp(choice,"O")==0 )
            overDueBooks();

        else if( strcmp(choice,"M")==0 )
            mostPopularBooks();

        else if( strcmp(choice,"B")==0 )
            mainMenu();

        else {
            errMsg("\n\aError!\nusage: enter one of the given choices");
            adminMenu();
        }

    }while( strcmp(choice,"O")!=0 && strcmp(choice,"M")!=0
            && strcmp(choice,"B")!=0 );
}



void exitMenu(){

    SetConsoleTitle("Library System > Exit Menu");

    header();

    printf("Save And Exit\t\t(S)\n");
    printf("Exit Without Saving\t(E)\n");

    printf("\nBack\t\t\t(B)\n");

    char choice[20];

    do{
        printf("\n\n\nYour choice : ");
        strupr(gets(choice));

        if( strcmp(choice,"S")==0 ) {
            terminateTempDataBase(true);
            system("cls");
            exit(0);
        }

        else if( strcmp(choice,"E")==0 ) {
            terminateTempDataBase(false);
            system("cls");
            exit(0);
        }

        else if( strcmp(choice,"B")==0 )
            mainMenu();

        else {
            errMsg("\n\aError!\nusage: enter one of the given choices");
            exitMenu();
        }

    }while( strcmp(choice,"S")!=0 && strcmp(choice,"S")!=0
            && strcmp(choice,"B")!=0 );
}
