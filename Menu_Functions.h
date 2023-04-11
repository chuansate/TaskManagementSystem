#ifndef Menu_Functions_H
#define Menu_Functions_H
#define LEN sizeof(struct Task)
void Add();
void View();
void Update();
void Delete();
void Sort_Due_Dates_Ascending();
void Sort_Due_Dates_Descending();
void View_Urgency();
void View_Status();
void View_Category();
int is_Greater(char date1[11], char date2[11]);
void Quit();

#endif