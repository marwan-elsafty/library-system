#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#include "member.h"
#include "dataTypes.h"
#include "utilities.h"


bool duplicateID ( char * enteredID )
{

    FILE * members = fopen("members.bin", "r");

    // failure check
    if(members==NULL)
        // no previous files available
        // thus no previous ID entered
        return true;

    memberDataType member;

    // read from original file
    while( fread(&member,sizeof(memberDataType),1,members) )
    {

        if( strcmp(member.ID, enteredID)==0 )
        {

            fclose(members);
            return false;
        }
    }

    fclose(members);
    return true;
}
