#include <stdio.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#include "dataTypes.h"
#include "utilities.h"


void showMemberDetails( char * choiceID ) {

	FILE * members = fopen("members.bin", "r");

    // failure check
    if(members==NULL) {
        perror("\a\n\nError");
        getche();
        return;
    }

    memberDataType member;

    // read from original file
    while( fread(&member,sizeof(memberDataType),1,members) ) {

        if( strcmp(member.ID , choiceID)==0 ) {

	    	printf("\n\n\aMember Details.\n");

	    	printf("\nFull Name\t: %s %s", member.name.first ,  member.name.last );
	    	printf("\nIdentity (ID)\t: %s", member.ID);
	    	printf("\nE-Mail Address\t: %s", member.email);
	    	printf("\nPhone Number\t: %s", member.phoneNum);
	    	printf("\nBorrowed Books\t: %d", member.borrowedBooks);

	    	getche();
	    	break;
    	}
    }

    fclose(members);
}
