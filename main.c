// adding header files
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

// adding self-made header files
#include "menu.h"
#include "utilities.h"


int main(void){

    // load old database in a temp archive
    initTempDataBase();

    do {
        mainMenu();
        fflush(stdin);

        SetConsoleTitle("Library System > Exit ?");

     } while( yesNoRequest("exit")==false );

    return 0;
}
