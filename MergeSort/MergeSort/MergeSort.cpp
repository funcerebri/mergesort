// MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

/* Function to print an array */
void printArray(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

template<typename T>
void MergeSortAlg(T a[], size_t l)
{
	size_t BlockSizeIterator;
	size_t BlockIterator;
	size_t LeftBlockIterator;
	size_t RightBlockIterator;
	size_t MergeIterator;

	size_t LeftBorder;
	size_t MidBorder;
	size_t RightBorder;
	for (BlockSizeIterator = 1; BlockSizeIterator < l; BlockSizeIterator *= 2)
	{
		for (BlockIterator = 0; BlockIterator < l - BlockSizeIterator; BlockIterator += 2 * BlockSizeIterator)
		{
			//ѕроизводим сли€ние с сортировкой пары блоков начинающуюс€ с элемента BlockIterator
			//левый размером BlockSizeIterator, правый размером BlockSizeIterator или меньше
			LeftBlockIterator = 0;
			RightBlockIterator = 0;
			LeftBorder = BlockIterator;
			MidBorder = BlockIterator + BlockSizeIterator;
			RightBorder = BlockIterator + 2 * BlockSizeIterator;
			RightBorder = (RightBorder < l) ? RightBorder : l;
			int* SortedBlock = new int[RightBorder - LeftBorder];

			//ѕока в обоих массивах есть элементы выбираем меньший из них и заносим в отсортированный блок
			while (LeftBorder + LeftBlockIterator < MidBorder && MidBorder + RightBlockIterator < RightBorder)
			{
				if (a[LeftBorder + LeftBlockIterator] < a[MidBorder + RightBlockIterator])
				{
					SortedBlock[LeftBlockIterator + RightBlockIterator] = a[LeftBorder + LeftBlockIterator];
					LeftBlockIterator += 1;
				}
				else
				{
					SortedBlock[LeftBlockIterator + RightBlockIterator] = a[MidBorder + RightBlockIterator];
					RightBlockIterator += 1;
				}
			}
			//ѕосле этого заносим оставшиес€ элементы из левого или правого блока
			while (LeftBorder + LeftBlockIterator < MidBorder)
			{
				SortedBlock[LeftBlockIterator + RightBlockIterator] = a[LeftBorder + LeftBlockIterator];
				LeftBlockIterator += 1;
			}
			while (MidBorder + RightBlockIterator < RightBorder)
			{
				SortedBlock[LeftBlockIterator + RightBlockIterator] = a[MidBorder + RightBlockIterator];
				RightBlockIterator += 1;
			}

			for (MergeIterator = 0; MergeIterator < LeftBlockIterator + RightBlockIterator; MergeIterator++)
			{
				a[LeftBorder + MergeIterator] = SortedBlock[MergeIterator];
			}
			delete SortedBlock;
		}
	}
}

int merge_sort(int *a, int l, int r) {
	if (l == r) return 0;
	int mid = (l + r) / 2;
	merge_sort(a, l, mid);
	merge_sort(a, mid + 1, r);
	int * tmp;
	int i = l;
	int j;
	j = mid + 1;
	tmp = (int*)malloc(r * sizeof(int));
	for (int step = 0; step<r - l + 1; step++) {
		if ((j>r) || ((i <= mid) && (a[i]<a[j]))) {
			tmp[step] = a[i];
			i++;
		}
		else {
			tmp[step] = a[j];
			j++;
		}
	}
	for (int step = 0; step<r - l + 1; step++)
		a[l + step] = tmp[step];
}

int merge_sort_parallel(int *a, int l, int r) {
	if (l == r) return 0;
	int mid = (l + r) / 2;
	merge_sort(a, l, mid);
	merge_sort(a, mid + 1, r);
	int * tmp;
	int i = l;
	int j;
	j = mid + 1;
	tmp = (int*)malloc(r * sizeof(int));

	#pragma omp parallel for num_threads(3)
	for (int step = 0; step<r - l + 1; step++) {
		if ((j>r) || ((i <= mid) && (a[i]<a[j]))) {
			tmp[step] = a[i];
			i++;
		}
		else {
			tmp[step] = a[j];
			j++;
		}
	}

	#pragma omp parallel for num_threads(3)
	for (int step = 0; step<r - l + 1; step++)
		a[l + step] = tmp[step];
}

#define N 50000
int main()
{
	int arr[N];
	
	//read digits from file and write its into array
	FILE *file;
	file = fopen("input_min.txt", "r");
	for (int i = 0; i < N; i++) {
		fscanf(file, "%d", &arr[i]);
	}
	fclose(file);

	//sort array and calculate time
	unsigned __int64 freq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	double timerFrequency = (1.0 / freq);
	unsigned __int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER *)&startTime);
	
	//int arr_size = sizeof(arr) / sizeof(arr[0]);
	//MergeSortAlg(arr, arr_size);
	//merge_sort(arr, 0, N - 1);
	merge_sort_parallel(arr, 0, N - 1);

	unsigned __int64 endTime;
	QueryPerformanceCounter((LARGE_INTEGER *)&endTime);
	double timeDifferenceInMilliseconds = ((endTime - startTime) * timerFrequency);

	//write sort array into file
	FILE *fileout;
	fileout = fopen("output.txt", "w+");
	printf("Execution time = %f\n", timeDifferenceInMilliseconds);
	for (int i = 0; i < N; i++) {
		fprintf(fileout, "%d%s", arr[i], " ");
	}
	fclose(fileout);

	return getchar();
}