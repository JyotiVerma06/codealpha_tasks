#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student
{
    int id;
    char name[50];
    int age;
    char course[50];
};


void removeNewline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}


void clearBuffer()
{
    while (getchar() != '\n');
}


int idExists(int id)
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
        return 0;

    struct Student s;

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                  &s.id,
                  s.name,
                  &s.age,
                  s.course) == 4)
    {
        if (s.id == id)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}



void addStudent()
{
    struct Student s;

    FILE *fp = fopen(FILE_NAME, "a");

    if (fp == NULL)
    {
        printf("\nUnable to open file!\n");
        return;
    }

    printf("\n========== Add Student ==========\n");

    while (1)
    {
        printf("Enter Student ID: ");

        if (scanf("%d", &s.id) != 1)
        {
            printf("Invalid ID!\n");
            clearBuffer();
            continue;
        }

        if (s.id <= 0)
        {
            printf("ID must be greater than 0.\n");
            continue;
        }

        if (idExists(s.id))
        {
            printf("Student ID already exists!\n");
            continue;
        }

        break;
    }

    clearBuffer();

    printf("Enter Student Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    removeNewline(s.name);

    while (1)
    {
        printf("Enter Age: ");

        if (scanf("%d", &s.age) != 1)
        {
            printf("Invalid Age!\n");
            clearBuffer();
            continue;
        }

        if (s.age <= 0 || s.age > 120)
        {
            printf("Please enter a valid age.\n");
            continue;
        }

        break;
    }

    clearBuffer();

    printf("Enter Course: ");
    fgets(s.course, sizeof(s.course), stdin);
    removeNewline(s.course);

    fprintf(fp, "%d|%s|%d|%s\n",
            s.id,
            s.name,
            s.age,
            s.course);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}



void displayStudents()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    struct Student s;
    int count = 0;

    printf("\n=================================================================\n");
    printf("%-10s %-25s %-8s %-20s\n",
           "ID", "NAME", "AGE", "COURSE");
    printf("=================================================================\n");

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                  &s.id,
                  s.name,
                  &s.age,
                  s.course) == 4)
    {
        printf("%-10d %-25s %-8d %-20s\n",
               s.id,
               s.name,
               s.age,
               s.course);

        count++;
    }

    printf("=================================================================\n");
    printf("Total Students : %d\n", count);

    fclose(fp);
}

void searchStudent()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    struct Student s;
    int id, found = 0;

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                  &s.id,
                  s.name,
                  &s.age,
                  s.course) == 4)
    {
        if (s.id == id)
        {
            printf("\n========== Student Found ==========\n");
            printf("ID     : %d\n", s.id);
            printf("Name   : %s\n", s.name);
            printf("Age    : %d\n", s.age);
            printf("Course : %s\n", s.course);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nStudent not found.\n");
}




void updateStudent()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("\nUnable to create temporary file.\n");
        fclose(fp);
        return;
    }

    struct Student s;
    int id, found = 0;

    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);
    clearBuffer();

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                  &s.id,
                  s.name,
                  &s.age,
                  s.course) == 4)
    {
        if (s.id == id)
        {
            found = 1;

            printf("\nUpdating Student Record\n");

            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            removeNewline(s.name);

            while (1)
            {
                printf("Enter New Age: ");

                if (scanf("%d", &s.age) != 1)
                {
                    printf("Invalid Age!\n");
                    clearBuffer();
                    continue;
                }

                if (s.age <= 0 || s.age > 120)
                {
                    printf("Please enter a valid age.\n");
                    continue;
                }

                break;
            }

            clearBuffer();

            printf("Enter New Course: ");
            fgets(s.course, sizeof(s.course), stdin);
            removeNewline(s.course);
        }

        fprintf(temp, "%d|%s|%d|%s\n",
                s.id,
                s.name,
                s.age,
                s.course);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("\nStudent updated successfully!\n");
    else
        printf("\nStudent not found!\n");
}




void deleteStudent()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
    {
        printf("\nNo student records found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("\nUnable to create temporary file.\n");
        fclose(fp);
        return;
    }

    struct Student s;
    int id, found = 0;
    char choice;

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    printf("Are you sure you want to delete this record? (Y/N): ");
    scanf(" %c", &choice);

    if (choice != 'Y' && choice != 'y')
    {
        fclose(fp);
        fclose(temp);
        remove("temp.txt");

        printf("\nDeletion cancelled.\n");
        return;
    }

    while (fscanf(fp, "%d|%49[^|]|%d|%49[^\n]\n",
                  &s.id,
                  s.name,
                  &s.age,
                  s.course) == 4)
    {
        if (s.id == id)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d|%s|%d|%s\n",
                s.id,
                s.name,
                s.age,
                s.course);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent not found!\n");
}


int main()
{
    int choice;

    while (1)
    {
        printf("\n");
        printf("=========================================\n");
        printf("      STUDENT MANAGEMENT SYSTEM\n");
        printf("=========================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");
            clearBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\n=========================================\n");
                printf("Thank you for using Student Management System!\n");
                printf("Program Closed Successfully.\n");
                printf("=========================================\n");
                return 0;

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}
