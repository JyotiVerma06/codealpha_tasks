#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
 {
    int id;
    char name[50];
    int age;
    char course[50];
};

// Add Student
void addStudent() 
{
    FILE *fp = fopen("students.dat", "rb+"); 
    struct Student s, newStudent;
    int exists = 0;

    if(fp == NULL) {
        // if file doesn't exist yet, create it
        fp = fopen("students.dat", "wb+");
    }

    printf("Enter ID: ");
    scanf("%d", &newStudent.id);

    // check if ID already exists
    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == newStudent.id) {
            exists = 1;
            break;
        }
    }

    if(exists) {
        printf("Error: Student with ID %d already exists!\n", newStudent.id);
    } else {
        printf("Enter Name: ");
        scanf("%s", newStudent.name);
        printf("Enter Age: ");
        scanf("%d", &newStudent.age);
        printf("Enter Course: ");
        scanf("%s", newStudent.course);

        // move pointer to end before writing
        fseek(fp, 0, SEEK_END);
        fwrite(&newStudent, sizeof(newStudent), 1, fp);
        printf("Student added successfully!\n");
    }

    fclose(fp);
}

// Display Students
void displayStudents()
{
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if(fp == NULL) 
    {
        printf("No records found!\n");
        return;
    }

    printf("\n=== Student Records ===\n");
    while(fread(&s, sizeof(s), 1, fp)) 
    {
        printf("ID: %d | Name: %s | Age: %d | Course: %s\n", s.id, s.name, s.age, s.course);
    }
    fclose(fp);
}

// Search Student
void searchStudent(int id)
{
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int found = 0;

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    while(fread(&s, sizeof(s), 1, fp)) 
    {
        if(s.id == id) 
        {
            printf("Found: ID=%d | Name=%s | Age=%d | Course=%s\n", s.id, s.name, s.age, s.course);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if(!found) printf("Student not found!\n");
}

// Update Student
void updateStudent(int id) 
{
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Student s;
    int found = 0;

    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    while(fread(&s, sizeof(s), 1, fp)) {
        if(s.id == id) {
            printf("Enter new name: "); 
            scanf("%s", s.name);
            printf("Enter new age: "); 
            scanf("%d", &s.age);
            printf("Enter new course: "); 
            scanf("%s", s.course);
            found = 1;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("Student updated successfully!\n");
    else
        printf("Student not found!\n");
}

// Delete Student
void deleteStudent(int id) 
{
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Student s;
    int found = 0;

    if(fp == NULL) 
    {
        printf("No records found!\n");
        return;
    }

    while(fread(&s, sizeof(s), 1, fp)) 
    {
        if(s.id == id) {
            found = 1;
            continue; // skip writing this record
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
        printf("Student deleted successfully!\n");
    else
        printf("Student not found!\n");
}

// Main Menu
int main() 
{
    int choice, id;

    while(1) 
    {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addStudent(); 
            break;
            case 2: displayStudents(); 
            break;
            case 3: printf("Enter ID to search: "); 
            scanf("%d", &id); searchStudent(id); 
            break;
            case 4: printf("Enter ID to update: ");
            scanf("%d", &id); updateStudent(id); 
            break;
            case 5: printf("Enter ID to delete: "); 
            scanf("%d", &id); 
            deleteStudent(id); 
            break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
