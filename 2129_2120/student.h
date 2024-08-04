#ifndef STUDENT_H
#define STUDENT_H

typedef struct student
{
    int id;
    char name[50];
    float gpa;
    int num_subjects;
    int (*course_marks)[2];
} Student;

typedef struct node
{
    Student data;
    struct node *prev;
    struct node *next;
} Node;

Node *createNode(int id, char *name, float gpa, int num_subjects, int (*course_marks)[2]);
void insertAtEnd(Node **head, int id, char *name, float gpa, int num_subjects, int (*course_marks)[2]);
Node *getNodeAt(Node *head, int x);
void deleteNode(Node **head, int id);
void modifyCGPA(Node *head, int id, float new_cgpa);
void displayList(Node *head);
void fileWriting(Node *head);
#endif