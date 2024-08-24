#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

struct student{
	char *name;
	int age;
	int id;
};

struct student *student_clone(struct student *student_c);
void student_destroy(struct student *student_d);
void student_print(struct student *student_p);


#endif