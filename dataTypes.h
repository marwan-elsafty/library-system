#ifndef DATATYPES_H_INCLUDED
#define DATATYPES_H_INCLUDED

typedef struct books {

    char title[50];
    char author[50];
    char publisher[50];

    struct {
        int day;
        int month;
        int year;
    }publishDate;

    char ISBN[20];
    char category[20];

    int copiesNum;
    int avalCopiesNum;

    int borrowed;

}bookDataType;


typedef struct borrowedBook {

    char ISBN[20];
    char ID[20];

    time_t borrowDate;
    time_t dueDate;

}borrowedBookDataType;


typedef struct members {

    struct{
        char first[25];
        char last[25];
    }name;

    struct{
        int building;
        int street;
        char city[25];
    }address;

    char ID[20];

    char phoneNum[20];

    int age;

    char email[100];

    int borrowedBooks;

}memberDataType;


#endif // Y_H_INCLUDED
