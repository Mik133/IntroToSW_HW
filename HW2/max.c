#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_INIT 1
#define ALL_GRADES_INIT_SIZE 0

int cmp_for_sort(const void *num1,const void *num2);

int main(int argc,char *argv[])
{
	FILE *grades_file;
	int *grade;
	int *all_grades;
	int line_count = LINE_INIT;
	int all_grades_size = ALL_GRADES_INIT_SIZE;
	int scan_return;
	if(argc == 1 || strcmp(argv[1],"-") == 0)
		grades_file = stdin;
	else
		grades_file = fopen(argv[1],"r");
	if(!grades_file)
		return 1;
	grade = (int*)malloc(sizeof(int));
	all_grades = (int*)malloc(sizeof(int));
	while((scan_return = fscanf(grades_file,"%d",grade)) >= 0)
		{
		if(scan_return != 1)
		{
			fprintf(stderr,"Error at line %d:grade %d invalid\n",line_count,*grade);
			return 1;
		}
		if(*grade >= 0 && *grade <= 100)
		{
			all_grades_size += 1;
			all_grades = (int*)realloc(all_grades,sizeof(int) * all_grades_size);
			all_grades[all_grades_size - 1] = *grade;
		}
		else
		{
			fprintf(stderr,"Error at line %d:grade %d invalid",line_count,*grade);
			return 1;
		}
	line_count += 1;
	}
	qsort(all_grades,all_grades_size,sizeof(int),cmp_for_sort);
	printf("%d",all_grades[all_grades_size - 1]);
	free(all_grades);
	free(grade);
	fclose(grades_file);
	return 0;
}

int cmp_for_sort(const void *num1,const void *num2)
{
	int num1Cmp = *(int *)num1;
	int num2Cmp = *(int *)num2;
	return (num1Cmp - num2Cmp);
}
