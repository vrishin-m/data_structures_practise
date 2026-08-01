#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address {
    int house_no;
    char street[50];
    char city[50];
    char state[50];
    int pin_code;
};

struct Student {
    char name[50];
    char father_name[50];
    char enrollment_no[20];
    char specialization[50];
    char majors[50];
    char minors[50];
    float gate_score;
    char status_category[20];
    char bhawan[50];
    char room_no[10];
    struct Address home_address;
    char blood_group[5];
};

int main() {
    int num_students = 15;
    
    printf("--- M.Tech Student Database Allocation ---\n");
    struct Student *students = (struct Student *)malloc(num_students * sizeof(struct Student));
    
    strcpy(students[0].name, "udhay");
    strcpy(students[0].enrollment_no, "wrgnrejngjekr");
    students[0].gate_score = 850.0;
    
    strcpy(students[1].name, "raju");
    strcpy(students[1].enrollment_no, "wfnrjwgnrwjfgr");
    students[1].gate_score = 720.0;
    
    printf("Displaying populated student records:\n");
    for (int i = 0; i < 2; i++) {
        printf("Student %d -> Name: %s | Enrollment: %s | GATE Score: %.1f\n", 
               i+1, students[i].name, students[i].enrollment_no, students[i].gate_score);
    }
    
    free(students);
    return 0;
}