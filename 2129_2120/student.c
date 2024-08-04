#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Node *createNode(int id, char *name, float gpa, int num_subjects, int (*course_marks)[2])
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data.id = id;
    strcpy(newNode->data.name, name);
    newNode->data.gpa = gpa;
    newNode->data.num_subjects = num_subjects;
    newNode->data.course_marks = course_marks;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node **head, int id, char *name, float gpa, int num_subjects, int (*course_marks)[2])
{
    Node *temp = *head;
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            printf("Student ID %d already exists in database \n", id);
            return;
        }
        temp = temp->next;
    }

    Node *newNode = createNode(id, name, gpa, num_subjects, course_marks);
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}
Node *getNodeAt(Node *head, int x)
{
    Node *temp = head;
    int count = 0;
    while (temp != NULL && count < x)
    {
        temp = temp->next;
        count++;
    }
    if (count == x)
    {
        return temp;
    }
    else
    {
        return NULL;
    }
}

void deleteNode(Node **head, int id)
{
    if (*head == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    Node *temp = *head;
    while (temp != NULL && temp->data.id != id)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Student with ID %d not found in database \n", id);
        return;
    }

    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        *head = temp->next;
    }

    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }

    if (temp->data.course_marks != NULL)
    {
        free(temp->data.course_marks);
    }
    free(temp);
}

void modifyCGPA(Node *head, int id, float new_cgpa)
{
    Node *temp = head;
    while (temp != NULL && temp->data.id != id)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Student with ID %d not found in database.\n", id);
        return;
    }

    temp->data.gpa = new_cgpa;
}

void displayList(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("ID: %d, Name: %s, GPA: %.2f, Subjects: %d\n", temp->data.id, temp->data.name, temp->data.gpa, temp->data.num_subjects);
        for (int i = 0; i < temp->data.num_subjects; i++)
        {
            printf("Subject ID: %d, Marks: %d\n", temp->data.course_marks[i][0], temp->data.course_marks[i][1]);
        }
        temp = temp->next;
    }
}

void fileWriting(Node *head)
{
    Node *temp = head;
    FILE *Files;
    Files = fopen("2129_2120.out", "w");
    while (temp != NULL)
    {
        fputs(" ID: ", Files);
        fprintf(Files, "%d", temp->data.id);
        fputs(" NAME: ", Files);
        fprintf(Files, "%s", temp->data.name);
        fputs(" GPA: ", Files);
        fprintf(Files, "%0.2f", temp->data.gpa);
        fputs(" Subjects: ", Files);
        fprintf(Files, "%d", temp->data.num_subjects);
        fputs("\n", Files);
        for (int i = 0; i < temp->data.num_subjects; i++)
        {
            fputs(" Subject ID ", Files);
            fprintf(Files, "%d", temp->data.course_marks[i][0]);
            fputs("\t", Files);
            fputs(" Marks ", Files);
            fprintf(Files, "%d", temp->data.course_marks[i][1]);
            fputs("\n", Files);
        }
        temp = temp->next;
    }
    fclose(Files);
}