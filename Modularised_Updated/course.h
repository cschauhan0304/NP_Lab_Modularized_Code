#ifndef COURSE_H
#define COURSE_H

#include "student.h"

void addCourse(Node *head, int id, int course_id, int marks);
void modifyCourse(Node *head, int id, int course_id, int new_marks);
void deleteCourse(Node *head, int id, int course_id);

#endif
