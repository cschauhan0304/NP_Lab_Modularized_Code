#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "course.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    // Node *head = NULL;

    if (argc != 2)
    {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *input_filename = argv[1];
    // char *output_filename = argv[2];
    parseFile(argv[1]);
    // writingToFile(argv[2]);

    // displayList(head);

    return 0;
}
