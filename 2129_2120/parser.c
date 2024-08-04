#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "course.h"
#include "student.h"
void parseFile(char *input_filename)
{
    int student_no = -1;
    Node *head = NULL;
    FILE *file = fopen(input_filename, "r");
    char line[256];
    int commas = 0;
    char str[50];
    int roll_no, course_no;
    char name[50];
    float cgpa;
    int row = 0;
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        if (strcmp(str, "# add student") == 0)
        {
            while (1)
            {
                line[strcspn(line, "\n")] = 0;
                sscanf(line, "%d, %49[^,], %f, %d", &roll_no, name, &cgpa, &course_no);

                int(*course_marks)[2] = malloc(course_no * sizeof(int[2]));
                for (int i = 0; i < course_no; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        course_marks[i][j] = 0;
                    }
                }
                insertAtEnd(&head, roll_no, name, cgpa, course_no, course_marks);
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;
                if (line[0] == '#' || feof(file))
                {
                    strcpy(str, line);
                    break;
                }
            }
        }
        else if (strcmp(line, "# initial database") == 0)
        {
            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = 0;
            while (1)
            {
                commas = 0;
                for (int i = 0; i < strlen(line); i++)
                {
                    if (line[i] == ',')
                    {
                        commas++;
                    }
                }
                if (commas > 1)
                {
                    row = 0;
                    student_no++;
                    sscanf(line, "%d, %49[^,], %f, %d", &roll_no, name, &cgpa, &course_no);
                    int(*course_marks)[2] = malloc(course_no * sizeof(int[2]));
                    for (int i = 0; i < course_no; i++)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            course_marks[i][j] = 0;
                        }
                    }
                    insertAtEnd(&head, roll_no, name, cgpa, course_no, course_marks);
                    commas = 0;
                }
                else if (commas == 1)
                {
                    int course_code, marks;
                    sscanf(line, "%d, %d", &course_code, &marks);
                    Node *nodeAtIndex = getNodeAt(head, student_no);
                    nodeAtIndex->data.course_marks[row][0] = course_code;
                    nodeAtIndex->data.course_marks[row][1] = marks;
                    row++;
                    commas = 0;
                }
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;
                if (line[0] == '#' || feof(file))
                {
                    strcpy(str, line);
                    break;
                }
            }
        }
        else if (strcmp(str, "# add course") == 0)
        {
            int course_id;
            int marks;
            while (1)
            {
                sscanf(line, "%d, %d, %d", &roll_no, &course_id, &marks);
                addCourse(head, roll_no, course_id, marks);

                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;
                if (line[0] == '#' || feof(file))
                {
                    strcpy(str, line);
                    break;
                }
            }
        }
        else if (strcmp(str, "# modify student") == 0)
        {
            while (1)
            {
                int modify_studentid;
                float cgpa;
                sscanf(line, "%d, %f", &modify_studentid, &cgpa);
                modifyCGPA(head, modify_studentid, cgpa);
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;
                if (line[0] == '#' || feof(file))
                {
                    strcpy(str, line);
                    break;
                }
            }
        }
        else if (strcmp(str, "# modify course") == 0)
        {
            int course_id;
            int new_marks;
            int id;
            while (1)
            {
                sscanf(line, "%d, %d, %d", &id, &course_id, &new_marks);
                modifyCourse(head, id, course_id, new_marks);
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;
                if (line[0] == '#' || feof(file))
                {
                    strcpy(str, line);
                    break;
                }
            }
        }
        else if (strcmp(str, "# delete student") == 0)
        {
            while (1)
            {
                int student_id_to_be_deleted = atoi(line);
                deleteNode(&head, student_id_to_be_deleted);
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;
                if (line[0] == '#' || feof(file))
                {
                    strcpy(str, line);
                    break;
                }
            }
        }
        else if (strcmp(str, "# delete course") == 0)
        {
            while (1)
            {
                int course_id;
                int id;
                sscanf(line, "%d, %d", &id, &course_id);
                deleteCourse(head, id, course_id);
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;
                if (line[0] == '#' || feof(file))
                {
                    strcpy(str, line);
                    break;
                }
            }
        }
    }
    fileWriting(head);
    fclose(file);
}
