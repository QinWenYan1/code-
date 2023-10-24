#include <stdio.h>
#include <stdlib.h>
#include "date.h"

struct date{
    int date;
    int month;
    int year;
};

Date *date_create(char *datestr){
/*first we need to initilize what we need*/
    int date;
    int month;
    int year;
     

    if(sscanf_s(datestr, "%d/%d/%d", &date, &month, &year)!=3){
        return NULL; /*incorrect input format*/
    }else if((date>= 1 && date <= 31) && (month>= 1 && month<= 12)){
        if(year >= 1){
            Date* datep = (Date*)malloc(sizeof(Date*));
            if(datep){/*successfully return a pointer*/
                datep -> date = date;
                datep -> month = month;
                datep -> year = year;
                return datep; 
            }
        }
    }
    /*invalid string input*/
    return NULL; 

}

Date *date_duplicate(Date *d){

    Date* duplicatep = (Date*)malloc(sizeof(Date*));
    if(d && duplicatep){/*valid pointer*/
        duplicatep -> date = d -> date;
        duplicatep -> month = d -> month;
        duplicatep -> year = d -> year;
        return duplicatep; 
    }
    /*invalid pointer*/
    return NULL; 

}

int date_compare(Date *date1, Date *date2){
    int outcome;
    int yeard = (date1 -> year) - (date2 -> year);
    int monthd = (date1 -> month) - (date2 -> month);
    int dated = (date1 -> date) - (date2 -> date);

    if(yeard != 0){
        return outcome = yeard > 0? 1:-1; 
    }else if(monthd != 0){
        return outcome = monthd > 0? 1:-1; 
    }else if(dated !=0 ){
        return outcome = dated > 0? 1:-1;
    }else{ /*the two dats must equal*/
        outcome = 0; 
    }
    return outcome; 
}

void date_destroy(Date *d){
    free(d);
}