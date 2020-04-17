#ifndef UTILITIES_H_
#define UTILITIES_H_

// because of bool in the prototype
#include <stdbool.h>


// string capitalization
void strcap ( char * str );

// messages
void errMsg ( char * message );
void acpMsg ( char * message );
bool yesNoRequest(char* question);

// validations
bool isEmail ( char * email );
bool isLeap ( int year );
bool isDate ( int day, int month, int year );

// database
void initTempDataBase();
void initBookTempDataBase();
void initBorrowedBookTempDataBase();
void initMemberTempDataBase();

void terminateTempDataBase( bool save );

#endif
