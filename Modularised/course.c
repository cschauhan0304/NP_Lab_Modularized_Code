#include <stdio.h>
#include <stdlib.h>
#include "course.h"

void addCourse(Node *head, int id, int course_id, int marks)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            for (int i = 0; i < temp->data.num_subjects; i++)
            {
                if (temp->data.course_marks[i][0] == course_id)
                {
                    printf("Course ID %d already exists for student ID %d.\n", course_id, id);
                    return;
                }
            }

            int(*new_course_marks)[2] = realloc(temp->data.course_marks, (temp->data.num_subjects + 1) * sizeof(int[2]));
            if (new_course_marks == NULL)
            {
                printf("Memory allocation failed.\n");
                return;
            }
            temp->data.course_marks = new_course_marks;
            temp->data.course_marks[temp->data.num_subjects][0] = course_id;
            temp->data.course_marks[temp->data.num_subjects][1] = marks;
            temp->data.num_subjects++;
            printf("Course added successfully for student ID %d.\n", id);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}

void modifyCourse(Node *head, int id, int course_id, int new_marks)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            for (int i = 0; i < temp->data.num_subjects; i++)
            {
                if (temp->data.course_marks[i][0] == course_id)
                {
                    temp->data.course_marks[i][1] = new_marks;
                    printf("Marks for course ID %d updated to %d for student ID %d.\n", course_id, new_marks, id);
                    return;
                }
            }
            printf("Course ID %d not found for student ID %d.\n", course_id, id);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}

/*void deleteCourse(Node *head, int id, int course_id)
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            for (int i = 0; i < temp->data.num_subjects; i++)
            {
                if (temp->data.course_marks[i][0] == course_id)
                {
                    for (int j = i; j < temp->data.num_subjects - 1; j++)
                    {
                        temp->data.course_marks[j][0] = temp->data.course_marks[j + 1][0];
                        temp->data.course_marks[j][1] = temp->data.course_marks[j + 1][1];
                    }
                    temp->data.num_subjects--;
                    printf("Course ID %d deleted for student ID %d.\n", course_id, id);
                    return;
                }
            }
            printf("Course ID %d not found for student ID %d.\n", course_id, id);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found.\n", id);
}*/
