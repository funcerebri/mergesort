// MergeSort.cpp : Defines the entry point for the console application.
//
#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include "stdafx.h"
#include<stdlib.h>

#include <vector>
#include<stdio.h>
#include <time.h>
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
			//���������� ������� � ����������� ���� ������ ������������ � �������� BlockIterator
			//����� �������� BlockSizeIterator, ������ �������� BlockSizeIterator ��� ������
			LeftBlockIterator = 0;
			RightBlockIterator = 0;
			LeftBorder = BlockIterator;
			MidBorder = BlockIterator + BlockSizeIterator;
			RightBorder = BlockIterator + 2 * BlockSizeIterator;
			RightBorder = (RightBorder < l) ? RightBorder : l;
			int* SortedBlock = new int[RightBorder - LeftBorder];

			//���� � ����� �������� ���� �������� �������� ������� �� ��� � ������� � ��������������� ����
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
			//����� ����� ������� ���������� �������� �� ������ ��� ������� �����
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

#define N 20000
int main()
{
	int arr[N];
	
	FILE *file;
	file = fopen("dsd.txt", "r");
	for (int i = 0; i < N; i++) {
		fscanf(file, "%d", &arr[i]);
	}
	fclose(file);

	clock_t time = clock();
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	MergeSortAlg(arr, arr_size);
	time = clock() - time;
	double ms = double(time) / CLOCKS_PER_SEC * 1000;

	FILE *fileout;
	fileout = fopen("output.txt", "w+");
	printf("Execution time = %f\n", ms);	
	for (int i = 0; i < N; i++) {
		fprintf(fileout, "%d%s", arr[i], " ");
	}
	fclose(fileout);

	return getchar();
}