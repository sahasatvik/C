#include <stdio.h>
#include <ctype.h>

#define	MAXSIZE	100000

int  getnum(int *, int, const char **);
void qsort(int[], int, int);
int  partition(int[], int, int);
void swap(int[], int, int);

int numbers[MAXSIZE];


int main(int argc, const char *argv[])
{
	int i, size;
	size = getnum(numbers, argc, argv);
	qsort(numbers, 0, size-1);
	for(i = 0; i < size; i++)
		printf("%d ", numbers[i]);
	return 0;
}

int getnum(int *target, int argc, const char *argv[])
{
	int size, n;
	const char *arg;
	size = 0;
	while(--argc)
		if(isdigit(*(arg = *++argv)))
		{
			n = 0;
			while(isdigit(*arg))
				n = (n * 10) + (*arg++ - '0');
			target[size++] = n;
		}
	return size;
}

void qsort(int v[], int left, int right)
{
	int pivot;
	if(left >= right)
		return;
	pivot = partition(v, left, right);
	qsort(v, left, pivot-1);
	qsort(v, pivot+1, right);
}

int  partition(int v[], int left, int right)
{
	int i, last;
	swap(v, left, (left + right) / 2);
	last = left;
	for(i = left+1; i <= right; i++)
		if(v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);
	return last;
}

void swap(int v[], int i, int j)
{
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
