#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Menu_Functions.h"
#include "Validate_Date.h"

struct date {
    int month;
    int day;
    int year;
};

struct Task {
    char task_name[30];
    char due_date[11];
    char star; //Indicate the importance of a certain task, so that we can display all the starred tasks. 'S' to indicate it is urgent, 'N' by default
    char status;//indicate if the task is completed, 'N' by default and 'C' to indicate completion of the task
    char category[20];
}; 

void Add(){
    struct Task task_records[50];
    int i, m = 0;
    FILE *fp = fopen("TaskRecords.txt", "ab+");
    if (fp == NULL) {
        printf("Failed to open file...\n");
        return;
    }

    while (!feof(fp)){
        if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
            m++;
        }
    }

    while (1){
        printf("Enter task name:\n");
        gets(task_records[m].task_name);
        fflush(stdin);
        printf("Enter its due date(in format of YYYY-MM-DD):\n");
        gets(task_records[m].due_date);
        fflush(stdin);
        //Validation of the format of date
        while (!validate_date(task_records[m].due_date)) {
            printf("Incorrect format of date. Please try again!\n");
            printf("Enter the due date of the task (in the format of YYYY-MM-DD):\n");
            gets(task_records[m].due_date);
            fflush(stdin);
        }

        while (1) {
            printf("Is the task very urgent to complete? Enter 'S' to indicate it is urgent otherwise enter 'N':\n");
            scanf( "%c", &task_records[m].star);
            fflush(stdin);

            if (task_records[m].star == 'N' || task_records[m].star == 'S') {
                break;
            }
            printf("Invalid input! Please try again.");
        }

        printf("Specify the category of the task:\n");
        gets(task_records[m].category);
        fflush(stdin);

        task_records[m].status = 'N';//By default, 'N' is to indicate the task is incomplete

        if ( fwrite(&task_records[m], LEN, 1, fp) != 1){
            printf("Unable to save the record...\n");
        } else {
            printf("New task has been added!\n");
        }
        m++;

        char res;
        printf("Do you still want to add new task? Enter Y to proceed, enter anything to quit.\n");
        scanf("%c", &res);
        fflush(stdin);
        if (res != 'Y'){
            break;
        } 
    }
    fclose(fp);

}

void View(){
    struct Task task_records[50];
    FILE *fp;
    int m = 0;
    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL){
        printf("Failed to open the file...\n");
        return ;
    } else {
        //Load all the records into the array of structs
        while (!feof(fp)) {
            if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
                ++m;
            }
        }
        fclose(fp);
        printf("          Task Name            Due Date   Urgency   Status        Category      \n");
        for (int i=0; i<m; i++){
            printf("%-30s%s     %c         %c      %s", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
            printf("\n");
        }
       
    }
}

void Update() {
    struct Task task_records[50];
    FILE *fp;
    int i, m = 0;
    char task_name[30];
    char ch;
    char flag = 1;
    

    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL) {
        printf("Failed to open file...\n");
        return ;
    } else {
        while (!feof(fp)){
            if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
                m++;
            }
        }
        
    }
    fclose(fp);

    char task_name_temp[30];
    char due_date_temp[11];
    char category_temp[20];
    while (flag) {
        printf("Please enter the task name to be updated:\n");
        gets(task_name);
        fflush(stdin);
        //Loop thru the task_records
        for (int i=0; i<m; i++){
            //When the record is found, then update its info
            if (strcmp(task_name, task_records[i].task_name) == 0) {
                printf("Task record found!\n");
                printf("The information of the task record is as below:\n");
                printf("          Task Name            Due Date   Urgency   Status        Category      \n");
                printf("%-30s%s     %c         %c      %s", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
                printf("\n");
                
                printf("Enter the new task name, enter R to retain the old task name:\n");
                gets(task_name_temp);
                fflush(stdin);
                if (task_name_temp[0] == 'R' && task_name_temp[1] == '\0'){
                    printf("Task name remains unchanged.\n");
                } else {
                    strcpy(task_records[i].task_name, task_name_temp);
                }
                
                printf("Enter the new due date(in format of YYYY-MM-DD), enter R to retain the old due date:\n");
                gets(due_date_temp);
                fflush(stdin);
                if (due_date_temp[0] == 'R' && due_date_temp[1] == '\0'){
                    printf("Due date remains unchanged.\n");
                } else {
                    //Validation of the format of date
                    while (!validate_date(due_date_temp)) {
                        printf("Incorrect format of date. Please try again!\n");
                        printf("Enter the new due date(in the format of YYYY-MM-DD):\n");
                        gets(due_date_temp);
                        fflush(stdin);
                    }
                    strcpy(task_records[i].due_date, due_date_temp);
                }
                
                while (1) {
                    printf("Is the task very urgent to complete? Enter 'S' to indicate it is urgent otherwise enter 'N':\n");
                    scanf("%c", &task_records[i].star);
                    fflush(stdin);
                    if (task_records[i].star == 'S' || task_records[i].star == 'N') {
                        break;
                    }
                    printf("Invalid input. Please try again.\n");
                }

                while (1) {
                    printf("Is the task completed? Enter 'C' to indicate it is completed, enter 'N' to indicate it is not completed yet:\n");
                    scanf("%c", &task_records[i].status);
                    fflush(stdin);
                    if (task_records[i].status == 'C' || task_records[i].status == 'N'){
                        break;
                    } 
                    printf("Invalid input. Please try again.\n");
                }
                

                printf("Enter the new category that the task belongs to, enter R to retain the old category:\n");
                gets(category_temp);
                fflush(stdin);
                if (category_temp[0] == 'R' && category_temp[1] == '\0'){
                    printf("Category remains unchanged.\n");
                } else {
                    strcpy(task_records[i].category, category_temp);
                }
                
                printf("Information of the task has been updated successfully!\n");
                flag = 0;
                break;
            }
        }

        //After looping thru the task_records but not found, then raise a warning
        if (flag) {
            printf("Record not found!\n");
        }
    }

    //Update the file
    fp = fopen("TaskRecords.txt", "wb");
    for (int i=0; i<m; i++){
        fwrite(&task_records[i], LEN, 1, fp);
    }
    fclose(fp);

}

void Delete() {
    struct Task task_records[50];
    FILE *fp;
    int i, j, k, m = 0;
    char flag = 1;
    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL) {
        printf("Failed to open the file...\n");
        return ;
    } else {
        while (!feof(fp)) {
            if (fread(&task_records[m], LEN, 1, fp) == 1){
                m++;
            }
        }
    }
    fclose(fp);

    char task_name[30];
    char ch;
    while (flag){
        printf("Enter the task name to be deleted:\n");
        gets(task_name);
        //Loop thru the task_records
        for (int i=0; i<m; i++){
            //If the task name is found, delete the record
            if (strcmp(task_name, task_records[i].task_name) == 0) {
                printf("Task record found!\n");
                printf("The information of the task record is as below:\n");
                printf("          Task Name            Due Date   Urgency   Status        Category      \n");
                printf("%-30s%s     %c         %c      %s", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
                printf("\n");
                printf("Are you sure you want to delete? Enter 'Y' to delete, enter anything to cancel:\n");
                scanf("%c", &ch);
                fflush(stdin);
                
                if (ch == 'Y'){
                    //Delete the record in task_records
                    for (j = i; j<m; j++){
                        task_records[j] = task_records[j+1];
                    }
                    m--;

                    //Update the file
                    if ((fp = fopen("TaskRecords.txt", "wb")) == NULL){
                        printf("Failed to open the file...\n");
                    } else {
                        for (k=0; k<m; k++){
                            fwrite(&task_records[k], LEN, 1, fp);
                        }
                    }
                    fclose(fp);
                    printf("The record has been deleted successfully!\n");
                }else {
                    printf("The operation has been cancelled!\n");
                }

                flag = 0;
                break;
            }
        }

        //If the record is not found, raise a warning
        if (flag){
            printf("Record not found!\n");
        }
    }
}

//Sort tasks by due dates(ascending order) then write tasks the file
void Sort_Due_Dates_Ascending(){
    struct Task task_records[50];
    FILE *fp;
    int i, j, m = 0;
    struct Task tmp;
    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL) {
        printf("Failed to open the file...\n");
        return ;
    } else {
        while (!feof(fp)){
            if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
                m++;
            }
        }
    }
    fclose(fp);

    //Bubble Sort To Sort The List In Ascending Order
    struct Task *task_records_pointer = task_records;
    for (i=0; i<m-1; i++){
        for(j=0; j < m-1-i; j++){
            if (is_Greater(task_records[j].due_date, task_records[j+1].due_date)) {
                tmp = *(task_records_pointer + j);
                *(task_records_pointer + j) = *(task_records_pointer + j + 1);
                *(task_records_pointer + j + 1) = tmp;
            }
        }
    }
    
    printf("Here is the list sorted in ascending order:\n");
    printf("          Task Name            Due Date   Urgency   Status        Category      \n");
    for (int i=0; i<m; i++){
        printf("%-30s%s     %c         %c      %s\n", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
    }
    printf("\n");
    
    char ch;
    while (1){
        printf("Are you sure that you want to rewrite the records in ascending order? Enter Y to rewrite, N to skip this operation:\n");
        scanf("%c", &ch);
        fflush(stdin);

        if (ch == 'Y') {
            //Update the file with records in ascending order
            if ((fp = fopen("TaskRecords.txt", "wb")) == NULL){
                printf("Failed to open the file...\n");
                return;
            } else {
                for (i=0; i<m; i++){
                    fwrite(&task_records[i], LEN, 1, fp);
                }
            }
            fclose(fp);
            printf("File records have been sorted successfully!\n");
            break;
        } else if (ch == 'N'){
            printf("The operation has been cancelled!\n");
            break;
        } else {
            printf("Invalid input. Please try again!\n");
        }
    }
    
    
}

//Sort tasks by due dates(descending order) then write tasks the file
void Sort_Due_Dates_Descending(){
    struct Task task_records[50];
    FILE *fp;
    int i, j, m = 0;
    struct Task tmp;
    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL) {
        printf("Failed to open the file...\n");
        return ;
    } else {
        while (!feof(fp)){
            if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
                m++;
            }
        }
    }
    fclose(fp);

    //Bubble Sort To Sort The List In Descending Order
    struct Task *task_records_pointer = task_records;
    for (i=0; i<m-1; i++){
        for(j=0; j < m-1-i; j++){
            if (is_Greater(task_records[j+1].due_date, task_records[j].due_date)) {
                tmp = *(task_records_pointer + j);
                *(task_records_pointer + j) = *(task_records_pointer + j + 1);
                *(task_records_pointer + j + 1) = tmp;
            }
        }
    }

    
    printf("Here is the list sorted in descending order:\n");
    printf("          Task Name            Due Date   Urgency   Status        Category      \n");
    for (int i=0; i<m; i++){
        printf("%-30s%s     %c         %c      %s\n", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
    }
    char ch;
    while (1){
        printf("Are you sure that you want to rewrite the records in descending order? Enter Y to rewrite, N to skip this operation:\n");
        scanf("%c", &ch);
        fflush(stdin);

        if (ch == 'Y') {
            //Update the file with records in descending order
            if ((fp = fopen("TaskRecords.txt", "wb")) == NULL){
                printf("Failed to open the file...\n");
                return ;
            } else {
                for (i=0; i<m; i++){
                    fwrite(&task_records[i], LEN, 1, fp);
                }
            }
            fclose(fp);
            printf("File records have been sorted successfully!\n");
            break;
        } else if (ch == 'N'){
            printf("The operation has been cancelled!\n");
            break;
        } else {
            printf("Invalid input. Please try again!\n");
        }
    }
}

// A function which returns 1 when date1 is greater than date2, otherwise return 0; 
int is_Greater(char date1[11], char date2[11]){
    char date1_year[5] = {date1[0], date1[1], date1[2], date1[3]};
    char date1_month[3] = {date1[5], date1[6]};
    char date1_day[3] = {date1[8], date1[9]};
    char date2_year[5] = {date2[0], date2[1], date2[2], date2[3]};
    char date2_month[3] = {date2[5], date2[6]};
    char date2_day[3] = {date2[8], date2[9]};
    
    struct date d1; 
    struct date d2;
    d1.year = atoi(date1_year);
    d1.month = atoi(date1_month);
    d1.day = atoi(date1_day);
    d2.year = atoi(date2_year);
    d2.month = atoi(date2_month);
    d2.day = atoi(date2_day);

    if (d1.year > d2.year){
        return 1;
    }


    if (d1.year == d2.year){
        if (d1.month > d2.month)
            return 1;
        else if (d1.month == d2.month){
            if (d1.day > d2.day){
                return 1;
            }
        }
    }
    return 0;
}


void View_Status(){
    struct Task task_records[50];
    FILE *fp;
    int i, j, m = 0;
    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL) {
        printf("Failed to open the file...\n");
        return ;
    } else {
        while (!feof(fp)){
            if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
                m++;
            }
        }
    }
    fclose(fp);
    
    char ch;
    while (1) {
        printf("Want to see completed tasks or uncompleted tasks? (C for completed, N for uncompleted)\n");
        scanf("%c", &ch);
        fflush(stdin);
        if (ch == 'C'){
            printf("Here is the list of completed tasks:\n");
            printf("          Task Name            Due Date   Urgency   Status        Category      \n");
            for (i=0; i<m; i++){
                if (task_records[i].status == 'C') {
                    printf("%-30s%s     %c         %c      %s", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
                    printf("\n");
                }
            }
            break;
        }else if(ch == 'N'){
            printf("Here is the list of uncompleted tasks:\n");
            printf("          Task Name            Due Date   Urgency   Status        Category      \n");
            for (i=0; i<m; i++){
                if (task_records[i].status == 'N') {
                    printf("%-30s%s     %c         %c      %s", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
                    printf("\n");
                }
            }
            break;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }        
}

void View_Urgency(){
    struct Task task_records[50];
    FILE *fp;
    int i, j, m = 0;
    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL) {
        printf("Failed to open the file...\n");
        return ;
    } else {
        while (!feof(fp)){
            if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
                m++;
            }
        }
    }
    fclose(fp);

    char ch;
    while (1) {
        printf("Want to see urgent tasks or non-urgent tasks? (S for urgent, N for non-urgent)\n");
        scanf("%c", &ch);
        fflush(stdin);
        if (ch == 'S'){
            printf("Here is the list of urgent tasks:\n");
            printf("          Task Name            Due Date   Urgency   Status        Category      \n");
            for (i=0; i<m; i++){
                if (task_records[i].star == 'S') {
                    printf("%-30s%s     %c         %c      %s", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
                    printf("\n");
                }
            }
            break;
        }else if(ch == 'N'){
            printf("Here is the list of non-urgent tasks:\n");
            printf("          Task Name            Due Date   Urgency   Status        Category      \n");
            for (i=0; i<m; i++){
                if (task_records[i].star == 'N') {
                    printf("%-30s%s     %c         %c      %s", task_records[i].task_name, task_records[i].due_date, task_records[i].star, task_records[i].status, task_records[i].category);
                    printf("\n");
                }
            }
            break;
        } else {
            printf("Invalid input. Please try again.\n");
        }
    }
}

void View_Category(){
    struct Task task_records[50];
    FILE *fp;
    int i, j, m = 0;
    if ((fp = fopen("TaskRecords.txt", "ab+")) == NULL) {
        printf("Failed to open the file...\n");
        return ;
    } else {
        while (!feof(fp)){
            if ((fread(&task_records[m], LEN, 1, fp)) == 1) {
                m++;
            }
        }
    }
    fclose(fp);

    char flag = 1;
    char category[20];

    while (flag) {
        printf("Which category of tasks that you would like to see?\n");
        gets(category);
        fflush(stdin);

        for (i=0; i<m; i++){
            //The category is found
            if (strcmp(task_records[i].category, category) == 0) {
                printf("Category found! Here is the list of tasks that fall under %s:\n", category);
                printf("          Task Name            Due Date   Urgency   Status        Category      \n");
                for (int j = i; j<m; j++){
                    if (strcmp(task_records[j].category, category) == 0) {
                        printf("%-30s%s     %c         %c      %s", task_records[j].task_name, task_records[j].due_date, task_records[j].star, task_records[j].status, task_records[j].category);
                        printf("\n");
                    }
                }
                flag = 0;
                break;
            }
        }

        //If the category is not found
        if (flag) {
            printf("The category is not found! Please try again.\n");
        }
    }
}

void Quit(){
    printf("Quiting system... Have a nice day!\n");
}