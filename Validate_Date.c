#include "Validate_Date.h"
//A function returns 1 if the date is reasonable, otherwise returns 0
int validate_date(char date[11]){
    char flag = 1;
    //Ensuring the added tasks have a due date which is 2022 or onwards
    if (date[0] < 50 || date[0] > 57) {
        flag = 0;
    } else if (date[1] < 48 || date[1] > 57 ) {
        flag = 0;
    } else if (date[2] < 50 || date[2] > 57) {
        flag = 0;
    } else if (date[3] < 50 || date[3] > 57) {
        flag = 0;
    } else if (date[4] != '-' || date[7] != '-') {
        flag = 0;
    } else if (date[5]<48 || date[5]>49) {//The first digit of MM can be either 0 or 1 only
        flag = 0;
    } else if (date[8] < 48 || date[8] > 51) {//the first digit of DD can be either 0,1,2, o 3 only
        flag = 0;
    } else if (date[9] < 48 || date[9] > 57){//Ensuring the second digit of DD can range from 0 to 9
        flag = 0;
    }

    if (date[5] == '0'){//Ensuring the MM to be 01, 02, 03, ..., 09
        if (date[6] < 49 || date[6] > 57) {
            flag = 0;
        }
    } else if (date[5] == '1'){
        if (date[6] < 48 || date[6] > 50) { //Ensuring the MM to be 10, 11, 12
            flag = 0;
        }
    }
    
    if (date[8] == '0'){ //DD cannot be 00
        if (date[9] == '0') {
            flag = 0;
        }
    } else if (date[8] == '3') {//DD can be 30 or 31 only
        if (date[9] < 48 || date[9] > 49) {
            flag = 0;
        }
    }
    return flag;
}