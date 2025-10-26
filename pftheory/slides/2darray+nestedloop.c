#include <stdio.h>

#define STUDENTS 3
#define SUBJECTS 4
int main(){

    char studentNames[STUDENTS][20] = {"Nyle", "Rubas", "Aryan"};
    char subjectNames[SUBJECTS][20] = {"PF", "CG", "AP", "FE"};

    int grades[STUDENTS][SUBJECTS]; // 2D array that holds student grades
    float studentAverage;           // variable to hold average of all grades of a particular students (row-wise)
    int studentTotal;               // variable to hold total value(summation) of all grades of a particular students (row-wise)
    int subjectTotal;               // variable to hold total value(summation) of all grades for a particular subject (column-wise)
    float subjectAverage;           // variable to hold average of all grades for a particular subject (column-wise)


    /*
        nested loop to take grades input from the user
       14        15        15        13
       15        13        14        14
       14        15        15        13
    */ 
    
    for (int i = 0; i < STUDENTS; i++)
    {
        printf("Enter grades for %s \n", studentNames[i]);
        for (int j = 0; j < SUBJECTS; j++)
        {
            printf("Enter grades for %s: ", subjectNames[j]);
            scanf("%d", &grades[i][j]);
        }
        printf("\n");
    }
    
    //  printing header row
    /*
        Student                PF        CG        AP        FE    Total    Average
        ---------------------------------------------------------------------------
    */
    
    printf("%-15s", "Students");
    for (int j = 0; j < SUBJECTS; j++)
    {
        printf("%10s", subjectNames[j]);
    }
    printf("%10s%13s","Total", "Average");
    printf("\n------------------------------------------------------------------------------\n");

    // printing student names with grades, total and average (row-wise)
    /*
        Student                PF        CG        AP        FE    Total    Average
        ---------------------------------------------------------------------------
        Nyle                   14        15        15        13       57      14.25 
        Rubas                  15        13        14        14       56      14.00  
        Aryan                  14        15        15        13       57      14.25
        ---------------------------------------------------------------------------
    */
    for (int i = 0; i < STUDENTS; i++)
    {
        studentTotal = 0;
        printf("%-15s", studentNames[i]);
        for (int j = 0; j < SUBJECTS; j++)
        {
            printf("%10d", grades[i][j]);
            studentTotal += grades[i][j];

        }
        studentAverage = (float)studentTotal/SUBJECTS;
        printf("%10d%13.2f", studentTotal, studentAverage);
        printf("\n");
        
    }
    printf("------------------------------------------------------------------------------\n");
    // printing subject average (column-wise)
    /*
        Student                PF        CG        AP        FE    Total    Average
        ---------------------------------------------------------------------------
        Nyle                   14        15        15        13       57      14.25 
        Rubas                  15        13        14        14       56      14.00  
        Aryan                  14        15        15        13       57      14.25
        ---------------------------------------------------------------------------
        Subject Average        14.33     14.33     14.66     13.33
    */
    printf("%-18s","Subject Average");
    for (int j = 0; j < SUBJECTS; j++)
    {
        subjectTotal = 0;
        for (int i = 0; i < STUDENTS; i++)
        {
            subjectTotal += grades[i][j];
        }
        subjectAverage = (float)subjectTotal/STUDENTS;
        printf("%10.2f", subjectAverage);
        
        
    }
}