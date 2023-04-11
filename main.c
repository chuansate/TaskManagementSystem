#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Validate_Date.h"
#include "Menu_Functions.h"

int main() {
    int res;
    while (1){
        printf("*****Personal Task Management*****\n");
        printf("1) Add New Task\n");
        printf("2) View All Task\n");
        printf("3) Update Task\n");
        printf("4) Delete Task\n");
        printf("5) Sort Tasks By Due Dates in Ascending Order\n");
        printf("6) Sort Tasks By Due Dates in Descending Order\n");
        printf("7) View Tasks By Urgency\n");
        printf("8) View Tasks By Status\n");
        printf("9) View Tasks By Categories\n");
        printf("10) Exit Program\n");
        printf("**********************************\n");
        printf("Enter option:");
        scanf("%d", &res);
        fflush(stdin);
	    
        if (res == 1) {
            Add();
        } else if (res == 2){
            View();
        } else if (res == 3) {
            Update();
        } else if (res == 4){
            Delete();
        } else if (res == 5){
            Sort_Due_Dates_Ascending();
        }else if (res == 6) {
            Sort_Due_Dates_Descending();
        } else if (res == 7) {
            View_Urgency();
        } else if (res == 8) {
            View_Status();
        } else if (res == 9){
            View_Category();
        } else if (res == 10){
            Quit();
            break;
        }else {
            printf("\nInvalid input. Please try again.\n");
        }
    }
    return 0;
}



