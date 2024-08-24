#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_INIT 1
#define ALL_GRADES_INIT_SIZE 0
#define DEFAULT_BINS 10
#define BIN_100 100
#define INIT_H 0;

int cmp_for_sort(const void *num1,const void *num2);

int main(int argc,char *argv[])
{
	//Declaring variables
	FILE *grades_file;
	int *grade;
	int *all_grades;
	int all_grades_size = ALL_GRADES_INIT_SIZE;
	int bins = DEFAULT_BINS;
	int line_count = LINE_INIT;
	int bin_width;
	int *histogram;
	int hist_min = INIT_H;
	int hist_max = INIT_H;
	int scan_return;
	//Parsing the input
	if((argc == 2 && strcmp(argv[1],"-") == 0) || argc == 1)//Input from stdin & check if bins
		grades_file = stdin;
	else if(argc == 2)//Only file supplied
		grades_file = fopen(argv[3],"r");
	else if(argc == 3)//Only bins from argv grades from stdin
	{
		bins = atoi(argv[2]); 
		grades_file = stdin;
	}
	else if(argc == 4 && strcmp(argv[1],"-") == 0)//bins and grades from stdin
	{
			bins = atoi(argv[3]);
			grades_file = stdin;
	}
	else//bins and grades from file 
	{
		if(strcmp(argv[1],"-nbins") == 0)// -nbins # file
		{
			bins = atoi(argv[2]);
			grades_file = fopen(argv[3],"r");
		}
		else // file -nbins #
		{
			bins = atoi(argv[3]);
			grades_file = fopen(argv[1],"r");	
		}		
	}
	//End of parsing inputs
	
	//Get grades
	all_grades = (int*)malloc(sizeof(int));
	grade = (int*)malloc(sizeof(int));
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
	//End of getting grades
	
	//Making the histogram
	bin_width = BIN_100/bins;
	histogram =(int*)calloc(bins,sizeof(int));
	int grades_count = 0;
	for(int i = 0;i < bins;i++)
	{
		if(i == bins - 1)
			hist_max = 101;
		else
			hist_max += bin_width;
		while(1)
		{
			if(hist_min <= all_grades[grades_count] && 
					all_grades[grades_count] < hist_max &&
					grades_count < all_grades_size)
			{
				histogram[i] += 1;
				grades_count += 1;
			}
			else
				break;
		}
		printf("%d-%d\t%d\n",hist_min,hist_max - 1,histogram[i]);
		hist_min += bin_width;
	}
	return 0;
}



int cmp_for_sort(const void *num1,const void *num2)
{
	int num1Cmp = *(int *)num1;
	int num2Cmp = *(int *)num2;
	return (num1Cmp - num2Cmp);
}
