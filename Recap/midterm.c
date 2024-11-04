#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define NUMPROGRAMS 4
#define YEARLEVELS 4
#define MAXSTUDS 100

typedef struct{
    char fName[64];
    char mi;
    char lName[32];
}studName;

typedef unsigned char personalInfo;
/*Given 8 bits: 0000 0000
 
 Bits
 8    = Status:            0 - Inactive, 1 - Active
 7    = Nationality:       0 - Filipino, 1 - Foreigner
 6    = Enrollment Status: 0 - Regular, 1 - Irregular
 5    = Gender:            0 - Male, 1 - Female
 3-4  = Year Level:        00 - 1st, 01 - 2nd, 10 - 3rd, 11 - 4th
 1-2  = Program:           00 - CS, 01 - IT, 10 - IS, 11 - MATH
 
 For example:
 1001 1001 would represent an Active Regular 3rd Year Filipino Female IT Student
*/

typedef struct{
    char idNum[9];
    studName name;
    personalInfo info;
}student;

typedef struct{
    student studs[MAXSTUDS];
    int numStuds;
}arrListStud;

typedef struct studNode{
    student stud;
    struct studNode* next;
}studNode, *studLL;

typedef studLL studDict[YEARLEVELS];

typedef struct{
    studDict programStuds;
    int studCtr;               /* refers to the total number of students in the PROGRAM. */
}dcismNode;

typedef dcismNode dcismDict[NUMPROGRAMS];

typedef struct{
    char studID[9];
    studName sName;
}studRec;

typedef struct{
    studRec studs[MAXSTUDS];
    int count;
}sNode, *studSet;               /* array representation of a Set of studRecs */

char* getProgram(personalInfo);
arrListStud populateStudentList(void);
void displayArrListStud(arrListStud);
int programHash(personalInfo);
int yearLevelHash(personalInfo);
int insertStudLL(studLL*, student);
void displayStudLL(studLL);
void initDCISMDict(dcismDict);
void convertToDCISMDict(dcismDict, arrListStud);
void displayDCISMDict(dcismDict);
studSet* initStudSet(void);
void insertStudSet(studSet, studRec);
studSet* removeInactiveStudents(dcismDict);
void displayStudSets(studSet*);
bool isActive(personalInfo);

/*
 Write the code for the function getProgram().
 
 The function will return the string equivalent of the program of the provided personalInfo.
 For example: personalInfo = 1001 1001 will return the string BSIT because the last 2 bits are 01. Refer to the definition of personalInfo to know which bit pattern represent each program.
 */
char* getProgram(personalInfo I)
{

}

/*
 Code for this function has been partially provided.
 Write the code for the function populatesetList().
 The function will read a file containing student records and return the student records to the calling function in the form of an arrListStud.
 */
arrListStud populateStudentList(void)
{
    FILE* fp;
    arrListStud SL = {{}, 0};

    if ((fp = fopen("students.bin", "rb")) == NULL) {
        puts("Unsuccessful in opening students.bin");
    } else {
        fseek(fp, 0, SEEK_END);
        int dataCount = ftell(fp) / sizeof(student);
        fseek(fp, 0, SEEK_SET);

        for (int i = 0; i < dataCount; i++) {
            fread(&SL.studs[i], sizeof(student), 1, fp);
            SL.numStuds++;
        }

        fclose(fp);
    }
    
    return SL;
}

/*
 Write the code for the function displayArrListStud().
 This function will display the ID number, First Name, and Last name of the student records inside the arrListStud.
 */
void displayArrListStud(arrListStud A)
{
    printf("Student Data from the file\n");
    printf("%-10s %-10s %-10s\n", "Id Number", "fName", "lName");
    
    for (int i = 0; i < A.numStuds; i++) {
        printf("%-10s %-10s %-10s %u\n",
               A.studs[i].idNum,
               A.studs[i].name.fName,
               A.studs[i].name.lName,
               A.studs[i].info);
    }
}


/*
 Write the code for the function programHash().
 Given a personalInfo variable, the function will return the integer equivalent of the bits that represent a student's program.
 */
int programHash(personalInfo I)
{
    return (I & 3) % NUMPROGRAMS;
}

/*
 Write the code for the function yearLevelHash().
 Given a personalInfo variable, the function will return the integer equivalent of the bits that represent a student's year level.
 */
int yearLevelHash(personalInfo I)
{
    return (I & 12) % YEARLEVELS;
}

/*
 Write the code for the function insertStudentLL().
 Given a pointer to a studLL and a student to insert, the function will insert into the sorted studSet based on the student's ID number. All elements in the studLL should be unique. The function will return 1 if the insert was successful and 0 if not.
 */
int insertStudLL(studLL* SL, student S)
{

}

/*
 Code for this function has been partially provided.
 Write the code for the function displayStudLL().
 The function will display the contents of a given studLL.
 */
void displayStudLL(studLL SL)
{
    if(SL != NULL){
        printf("\nYear %d\n\n");
        printf("%-10s", "Id Number");
        // printf("%-10s", "fName");
        // printf("%-10s", "lName");
        // printf("%-10s", "Program");
        // printf("%-10s", "Year");
        // printf("%-10s", "Gender");
        // printf("%-15s", "Enrollment");
        // printf("%-15s", "Nationality");
        // printf("%-10s\n", "Status");
        for(; SL != NULL; SL = SL->next){
            // printf("%-10s%-10s%-10s%-10s%-10d%-10s%-15s%-15s%-10s\n", SL->stud.idNum, SL->stud.name.fName);
            printf("%-10s\n", SL->stud.idNum);
        }
    }
}

/*
 Write the code for the function initDCISMDict().
 The function will receive a dcismDict, and initialize it to be empty.
 */
void initDCISMDict(dcismDict D)
{
    for(int i = 0; i < NUMPROGRAMS; i++){
        D[i].studCtr = 0;
        for(int j = 0; j < YEARLEVELS; j++){
            D[i].programStuds[j] = NULL;
        }
    }
}

/*
 Write the code for the function convertToDCISMDict().
 The function will receive a dcismDict and an arrListStud. The function will go through list of students and insert them to their proper place in the dcismDict.
 */
void convertToDCISMDict(dcismDict D, arrListStud SL)
{
    for(int i = 0; i < MAXSTUDS; i++){
        int indexProgram = programHash(SL.studs[i].info);
        int indexYear = yearLevelHash(SL.studs[i].info);

        studLL newNode = (studLL)malloc(sizeof(studNode));
        newNode->stud = SL.studs[i];
        newNode->next = D[indexProgram].programStuds[indexYear];
        D[indexProgram].programStuds[indexYear] = newNode;
        D[indexProgram].studCtr++;
    }
}

/*
 Code for this function has been partially provided.
 Write the code for the function displayDCISMDict().
 The function will receive a dcismDict. The function will display all the students in the dcismDict by program and year level.
 */
void displayDCISMDict(dcismDict D)
{
    for(int i = 0; i < NUMPROGRAMS; i++){
        // printf("\n---------------------------------------------------------------------------------------------------------------\n%s %d Students\n");
        for(int j = 0; j < YEARLEVELS; j++){
            studLL current = D[i].programStuds[j];
            while(current != NULL && strcmp(current->stud.name.fName, "") != 0){
                printf("%s --> ", current->stud.idNum);
                current = current->next;
            }
            printf("\n");
        }
    }
}

/*
 Write the code for the function initStudSet().
 The function will initialize an empty array of studSets that can accommodate the total number of programs.
 */
studSet* initStudSet(void)
{
    studSet* s = (studSet*)malloc(sizeof(studSet));
    for(int i = 0; i < MAXSTUDS; i++){
        (*s)->studs[i].studID[0] = '\0';
        (*s)->studs[i].sName.fName[0] = '\0';
        (*s)->studs[i].sName.lName[0] = '\0';
        (*s)->studs[i].sName.mi = '\0';
        (*s)->count = 0;
    }
    return s;
}   

/*
 Write the code for the function insertStudSet().
 The function will receive a studSet and a studRec. The function will insert the studRec into the studSet. Student will be inserted at the end of the set.
 */
void insertStudSet(studSet S, studRec sRecord)
{
    
}

/*
 Write the code for the function removeInactiveStudents().
 The function will go through the entire dcismDict and delete all student records that have the status "inactive".
 Deleted records will be stored in an array of studSets, such that each deleted student will be stored in its proper index in the array of studSets based on their program. Return the array of studSets to the calling function.
 */
studSet* removeInactiveStudents(dcismDict D)
{
    studSet* s = initStudSet();
    for(int i = 0; i < NUMPROGRAMS; i++){
        for(int j = 0; j < YEARLEVELS; j++){
            studLL current = D[i].programStuds[j];
            while(current != NULL){
                if(!isActive(current->stud.info)){
                    strcpy((*s)->studs[(*s)->count].studID, current->stud.idNum);
                    strcpy((*s)->studs[(*s)->count].sName.fName, current->stud.name.fName);
                    strcpy((*s)->studs[(*s)->count].sName.lName, current->stud.name.lName);
                    (*s)->studs[(*s)->count].sName.mi, current->stud.name.mi;
                    (*s)->count++;
                }
                current = current->next;
            }
        }
    }
    return s;
}

/*
 Code for this function has been partially provided.
 Write the code for the function displayStudSets
 The function will go through the entire dcismDict and delete all student records that have the status "inactive".
 Deleted records will be stored in an array of studSets, such that each deleted student will be stored in its proper index in the array of studSets based on their program. Return the array of studSets to the calling function.
 */
void displayStudSets(studSet* S)
{
    printf("\nInactive Students");
    for(int i = 0; i < (*S)->count; i++){
        // printf("\n%s %d students\n");
        printf("%-10s", "Id Number");
        printf("%-10s", "fName");
        printf("%s", "lName\n");
        printf("%-10s%-10s%s\n", (*S)->studs[i].studID, (*S)->studs[i].sName.fName, (*S)->studs[i].sName.lName);
    }
}

int main(void)
{
    /* Problem 1
        1) Declare a variable SL of type arrListStud and call populateStudentList() to populate it
        2) Call displayArrListStud()
     */
    arrListStud SL;
    SL = populateStudentList();
    // displayArrListStud(SL);
    
    /* Problem 2
        1) Declare a variable D of type dcismDict
        2) Call initDCISMDict()
        3) Call convertToDCISMDict()
        4) Call displayDCISMDict()
     */
    dcismDict D;
    initDCISMDict(D);
    convertToDCISMDict(D, SL);
    // displayDCISMDict(D);
    
    /* Problem 3
        1) Declare a variable inactive of type studSet* and call removeInactiveStudents() to populate it
        2) Call displayDCISMDict()
        3) Call displayStudSets()
     */
    studSet* S = removeInactiveStudents(D);
    // displayDCISMDict(D);
    // displayStudSets(S);
    
    return 0;
}

bool isActive(personalInfo p){
    return p & (1 << 8 - 1);
}