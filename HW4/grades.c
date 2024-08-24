#include "grades.h"
#include "linked-list.h" //May be removed later
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int c_clone(void *e_to_clone,void **e_cloned);
int i_clone(void *e_to_clone,void **e_cloned);
int student_clone(void *e_to_clone,void **e_cloned);

void e_destroy(void *e_to_destroy);

int (*c_clonef)(void*,void**) = &c_clone;
int (*i_clonef)(void*,void**) = &i_clone;
int (*student_clonef)(void*,void**) = &student_clone;
void (*e_destroyf)(void*) = &e_destroy;

typedef struct{
	int id;
	char *name;
	struct list *courses;
	struct list *c_grades;
}student;

struct grades{
	struct list *students;
};

struct grades* grades_init()
{
	struct grades* grades = malloc(sizeof(grades));
	grades->students = list_init(student_clonef,e_destroyf);
	return grades;
}

int grades_add_student(struct grades *grades, const char *name, int id)
{
	if(grades == NULL)
		return -1;
	struct iterator *itr_student = list_begin(grades->students);
	while(itr_student != NULL)
	{
		student *tmp_student = (student*)list_get(itr_student);
		if(tmp_student->id == id)
		{
			return -1;
		}	
		itr_student = list_next(itr_student);
	}
	student *new_student = malloc(sizeof(student));
	if(new_student == NULL)
	{
		free(new_student);
		return -1;
	}
	new_student->name = malloc(sizeof((strlen(name)) + 1));
	if(new_student->name  == NULL)
	{
		free(new_student->name );
		return -1;
	}
	strcpy(new_student->name,name);
	new_student->id = id;
	new_student->courses = list_init(c_clonef,e_destroyf);
	new_student->c_grades = list_init(i_clonef,e_destroyf);
	list_push_back(grades->students,(void*)new_student);
	free(new_student);
	return 0;
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade)
{
	if(grades == NULL || grade < 0 || grade > 100)
		return -1;
	struct iterator *itr_student = list_begin(grades->students);
	char *cname = (char*)malloc(strlen(name) + 1);
	if(cname == NULL)
	{
		free(cname);
		return -1;
	}
	strcpy(cname,name);
	for(int i = 0;i < (int)list_size(grades->students);i++)
	{
		student *tmp_student = (student*)list_get(itr_student);
		if(tmp_student->id == id)
		{
			list_push_back(tmp_student->courses,cname);
			list_push_back(tmp_student->c_grades,&grade);
			free(cname);
			return 0;
		}
		else
			itr_student = list_next(itr_student);
	}
	free(cname);
	return -1;
}

float grades_calc_avg(struct grades *grades, int id, char **out)
{
	if(grades == NULL)
		return -1;
	struct iterator *itr_student = list_begin(grades->students);
	int sum_of_grades = 0;
	for(int i = 0;i < (int)list_size(grades->students);i++)
	{
		student *tmp_student = (student*)list_get(itr_student);
		if(tmp_student->id == id)
		{
			*out = malloc(strlen(tmp_student->name) + 1);
			struct iterator *itr_cgrade = list_begin(tmp_student->c_grades);
			for(int j = 0;j <(int)list_size(tmp_student->c_grades);j++)
			{
				sum_of_grades += *(int*)list_get(itr_cgrade);
				itr_cgrade = list_next(itr_cgrade);
			}
			strcpy(*out,tmp_student->name);
			if(sum_of_grades != 0)
				return (float)sum_of_grades/((float)list_size(tmp_student->c_grades));
			else 
				return 0;
		}
		else
			itr_student = list_next(itr_student);
	}
	return -1;
}

int grades_print_student(struct grades *grades, int id)
{
	if(grades == NULL)
		return -1;
	struct iterator *itr_student = list_begin(grades->students);
	while(itr_student != NULL)
	{
		student *tmp_student = (student*)list_get(itr_student);
		if(tmp_student->id == id)
		{
			printf("%s %d:",tmp_student->name,tmp_student->id);
			struct iterator *itr_course = list_begin(tmp_student->courses);
			struct iterator *itr_cgrade = list_begin(tmp_student->c_grades);
			for(int j = 0;j <(int)list_size(tmp_student->courses);j++)
			{
				printf(" %s %d",(char*)list_get(itr_course),*(int*)list_get(itr_cgrade));
				itr_course = list_next(itr_course);
				itr_cgrade = list_next(itr_cgrade);
				if(j != (int)list_size(tmp_student->courses) - 1)
					printf(",");
			}
			printf("\n");
			return 0;
		}
		else
			itr_student = list_next(itr_student);
	}
	return -1;
}

int grades_print_all(struct grades *grades)
{
	if(grades == NULL)
		return -1;
	struct iterator *itr_student = list_begin(grades->students);
	while(itr_student != NULL)
	{
		student *tmp_student = (student*)list_get(itr_student);
		printf("%s %d:",tmp_student->name,tmp_student->id);
		struct iterator *itr_course = list_begin(tmp_student->courses);
		struct iterator *itr_cgrade = list_begin(tmp_student->c_grades);
		for(int j = 0;j <(int)list_size(tmp_student->courses);j++)
		{
			printf(" %s %d",(char*)list_get(itr_course),*(int*)list_get(itr_cgrade));
			itr_course = list_next(itr_course);
			itr_cgrade = list_next(itr_cgrade);
			if(j != (int)list_size(tmp_student->courses) - 1)
				printf(",");
		}
		printf("\n");
		itr_student = list_next(itr_student);
	}
	return 0;
}

void grades_destroy(struct grades *grades)
{
	struct iterator *itr_dest = list_begin(grades->students);
	while(itr_dest != NULL)
	{
		student *student_dest = list_get(itr_dest);
		free(student_dest->name);
		list_destroy(student_dest->courses);
		list_destroy(student_dest->c_grades);
		itr_dest = list_next(itr_dest);
	}
	list_destroy(grades->students);
	free(grades);
}

int student_clone(void *e_to_clone,void **e_cloned)
{
	*e_cloned = (student*)malloc(sizeof(*(student*)e_to_clone));
	memcpy(*e_cloned,(student*)e_to_clone,sizeof(*(student*)e_to_clone));
	if(*e_cloned == NULL)
		return 1;
	else
		return 0;
}


int c_clone(void *e_to_clone,void **e_cloned)
{
	*e_cloned = (char *)malloc(strlen((char *)e_to_clone) + 1);
	strcpy(*e_cloned,e_to_clone);
	if(*e_cloned == NULL)
		return 1;
	else
		return 0;
}

int i_clone(void *e_to_clone,void **e_cloned)
{
	
	*e_cloned = (int *)malloc(sizeof(int));
	**(int **)e_cloned = *(int *)e_to_clone;
	if(*e_cloned == NULL)
		return 1;
	else
		return 0;
}

void e_destroy(void *e_to_destroy)
{
	free(e_to_destroy);
}




