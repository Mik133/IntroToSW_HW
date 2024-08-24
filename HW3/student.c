#include "student.h"


struct student *student_clone(struct student *student_c)
{
	struct student *tmp_student = malloc(sizeof(struct student));
	if(tmp_student == NULL) return NULL;
	
	tmp_student->name = (char *)malloc(sizeof(char) * strlen((char *)student_c->name) + 1);
	char *tmp_name = (char *)malloc(sizeof(char) * strlen((char *)student_c->name) + 1);
	strcpy(tmp_name,student_c->name);
	strcpy(tmp_student->name,tmp_name);
	tmp_student->age = student_c->age;
	tmp_student->id = student_c->id;
	free(tmp_name);
	return tmp_student;
}

void student_destroy(struct student *student_d)
{
	free((struct student *)student_d->name);
	if(student_d != NULL) free((struct student *)student_d);
	student_d = NULL;
}

void student_print(struct student *student_p)
{
	struct student *tmp_student = (struct student*)student_p;
	printf("student name: %s, age: %d, id: %d.\n",
			tmp_student->name,
			tmp_student->age,
			tmp_student->id);
	
}

