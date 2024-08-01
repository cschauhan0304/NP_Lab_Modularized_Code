#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "course.h"

void parseFile(char *input_filename)
{
    int student_no = -1;
    Node *head = NULL;
    //   printf("%s\n", input_filename);
    FILE *file = fopen(input_filename, "r");
    char line[256];
    int commas = 0;
    char str[50];
    char student_id_to_be_deleted[50];
    int roll_no, course_no;
    char name[50];
    float cgpa;
    int row = 0;
    while (fgets(line, sizeof(line), file))
    {

        line[strcspn(line, "\n")] = 0;
        // printf("%s\n", line);

        if (strcmp(str, "# add students") == 0)
        {
            while (1)
            {
                // i need to strip the line
                // i need to read the content in the line and add that guys in the linked list
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

                // i need to exit if this reaches some #
                // printf("in add students\n");
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;

                if (line[0] == '#')
                {
                    displayList(head);
                    // printf("is this coming\n");
                    printf("%s", line);

                    strcpy(str, line);
                    printf("%s", str);
                    break;
                }
            }
        }
        else if (strcmp(line, "# initial addition of database") == 0)
        {

            fgets(line, sizeof(line), file);
            line[strcspn(line, "\n")] = 0;

            while (1)
            {
                commas = 0;
                // check no of commas
                // accordingly select the student name row or course and mark row

                for (int i = 0; i < strlen(line); i++)
                {
                    if (line[i] == ',')
                    {
                        commas++;
                    }
                }
                // printf("%d\n", commas);
                if (commas > 1)
                {
                    row = 0;
                    student_no++;
                    // printf("%s\n", line);
                    sscanf(line, "%d, %49[^,], %f, %d", &roll_no, name, &cgpa, &course_no);
                    // printf("Roll No: %d\n", roll_no);
                    // printf("Name: %s\n", name);
                    // printf("CGPA: %.2f\n", cgpa);
                    // printf("Course No: %d\n", course_no);
                    // stduent name data base row
                    // 1) i need to add this guy in linked list and
                    // check whether he is nique or not
                    // create a course linked list for his name under roll no

                    int(*course_marks)[2] = malloc(course_no * sizeof(int[2]));
                    for (int i = 0; i < course_no; i++)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            course_marks[i][j] = 0;
                        }
                    }

                    insertAtEnd(&head, roll_no, name, cgpa, course_no, course_marks);

                    // accordint o the commas i need to store the name,cgpa etc and store it into the
                    // linkedlist

                    // accessing student name and roll no cgpa courseNo
                    int comm = 0;

                    commas = 0;
                }
                else if (commas == 1)
                {
                    int course_code, marks;

                    sscanf(line, "%d, %d", &course_code, &marks);
                    // printf("Course Code: %d\n", course_code);
                    // printf("Marks: %d\n", marks);
                    // tranverse to that particular node
                    Node *nodeAtIndex = getNodeAt(head, student_no);
                    // printf("chintu");
                    // printf("Node at index %d: %s\n",student_no, nodeAtIndex->data.name);
                    // then we need to save it
                    //  printf("%d\n",nodeAtIndex->data.num_subjects);

                    nodeAtIndex->data.course_marks[row][0] = course_code;
                    nodeAtIndex->data.course_marks[row][1] = marks;
                    row++;
                    commas = 0;
                }

                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;

                if (line[0] == '#')
                {
                    displayList(head);
                    // printf("is this coming\n");
                    // printf("%s", line);

                    strcpy(str, line);
                    printf("%s\n", str);
                    // printf("%s", str);
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

                if (line[0] == '#')
                {
                    displayList(head);
                    // printf("is this coming\n");
                    // printf("%s", line);

                    strcpy(str, line);
                    printf("%s\n", str);
                    // printf("%s", str);
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
                // i need to record the information
                sscanf(line, "%d, %f", &modify_studentid, &cgpa);
                printf("%d %d\n", modify_studentid, cgpa);

                modifyCGPA(head, modify_studentid, cgpa);
                // recorded the information need to modify now :)

                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;

                if (line[0] == '#')
                {
                    displayList(head);
                    // printf("is this coming\n");
                    // printf("%s", line);

                    strcpy(str, line);
                    printf("%s\n", str);
                    // printf("%s", str);
                    break;
                }
            }
        }
        else if (strcmp(str, "# modify course") == 0)
        {
            // printf("%s", "modify course");
            int course_id;
            int new_marks;
            int id;
            while (1)
            {

                sscanf(line, "%d, %d, %d", &id, &course_id, &new_marks);

                modifyCourse(head, id, course_id, new_marks);

                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;

                if (line[0] == '#')
                {
                    printf("%s", line);
                    displayList(head);
                    // printf("is this coming\n");
                    // printf("%s", line);

                    strcpy(str, line);
                    // printf("%s", str);
                    break;
                }
            }
        }
        else if (strcmp(str, "# delete student") == 0)
        {
            while (1)
            {
                int student_id_to_be_deleted = atoi(line);
                printf("%d\n", student_id_to_be_deleted);
                deleteNode(&head, student_id_to_be_deleted);
                fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;

                if (line[0] == '#')
                {
                    printf("%s", line);
                    displayList(head);
                    // printf("is this coming\n");
                    // printf("%s", line);

                    strcpy(str, line);
                    // printf("%s", str);
                    break;
                }
            }
            // printf("%s", "delete student ra daffa ");
            // i need to read the id of student to be deleted

            // strcpy(student_id_to_be_deleted,line);

            // i need to check whether this guys exists here or not

            // i have to delete
            // i need to check the next line parse accordingly
        }
        /*else if (strcmp(str, "# delete course") == 0)
        {

            while (1)
            {

                int course_id;
                //  int new_marks
                int id;
                sscanf(line, "%d, %d", &id, &course_id);

                deleteCourse(head, id, course_id);

                char *t;
                t = fgets(line, sizeof(line), file);
                line[strcspn(line, "\n")] = 0;

                if (line[0] == '#')
                {
                    printf("%s", line);
                    displayList(head);
                    // printf("is this coming\n");
                    // printf("%s", line);

                    strcpy(str, line);
                    // printf("%s", str);
                    break;
                }
                if (feof(file))
                {
                    displayList(head);
                }
            }
        }
        */
    }

    // we are reading the file that mam gave
    // process the data
    fclose(file);
}