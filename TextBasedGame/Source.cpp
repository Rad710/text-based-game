#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>
#include <chrono>
#include <iostream>
constexpr auto BILLION = 1000000000L;
using namespace std;
/*Exercise 3*/

void merge(int* array, int begin, int middle, int end)
{
	int n1 = middle - begin + 1; // # of elements in left subarray
	int n2 = end - middle; // # elements in right subarray

	int* left = (int*) malloc((n1 + 1) * sizeof(int));
	int* right = (int*) malloc((n2 + 1) * sizeof(int));

	for (int i = 0; i < n1; i++) //copy data into subarrays
	{
		left[i] = array[begin + i];
	}
	for (int j = 0; j < n2; j++)
	{
		right[j] = array[middle + j + 1];
	}

	left[n1] = INT_MAX; //sentinel value
	right[n2] = INT_MAX;

	int i = 0, j = 0;
	for (int k = begin; k <= end; k++) //merge into one array, from smallest to largest
	{
		if (left[i] < right[j])
		{
			array[k] = left[i];
			i++;
		}
		else
		{
			array[k] = right[j];
			j++;
		}
	}

	free(left); //deallocate memory
	free(right);
}

void merge_sort(int* array, int begin, int end)
{
	if (begin < end)
	{
		int middle = (begin + end) / 2;
		merge_sort(array, begin, middle); //sort subarrays. Divide part
		merge_sort(array, middle + 1, end);

		merge(array, begin, middle, end); //merge sorted arrays. Conquer part
	}
}

void insertion_sort(int* array, int length)
{
	for (int j = 1; j < length; j++)
	{
		int key = array[j]; //helper for swap

		int i = j - 1; //insert element j into sorted a[0]...a[j-1]
		while (i >= 0 && array[i] > key) //swap until fit for j element
		{
			array[i + 1] = array[i];
			i--;
		}
		array[i + 1] = key; //insert j element in sorted manner
	}
}

void write_array(int* array, int length) //fill array with user input (betw. 1 and 100)
{
	printf("Input %d integers between 1 to 100: ", length);
	for (int i = 0; i < length; i++) //fill array
	{
		int input;
		cin >> input;

		if (input >= 1 && input <= 100) //input between 1 and 100
		{
			array[i] = input;
		}
		else
		{
			printf("Number out of range\nTerminating program");
			exit(1);
		}
	}
}

void print_array(int* array, int length) //print content of array
{
	for (int i = 0; i < length; i++)
	{
		printf("%d ", array[i]);
	}
}

int main()
{
	constexpr size_t length = 10;
	int test_mrg[length];
	int test_ins[length];

	write_array(test_mrg, length);

	memcpy(test_ins, test_mrg, sizeof(test_mrg[0]) * length); //copy content from array test_mrg to test_ins


	auto start = std::chrono::high_resolution_clock::now();
	merge_sort(test_mrg, 0, length - 1); //sort with merge sort
	auto finish = std::chrono::high_resolution_clock::now();


	//The variable below stores the conversion of the time to nanoseconds
	
	cout << "It took " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns.";
	print_array(test_mrg, length);

	start = std::chrono::high_resolution_clock::now();
	insertion_sort(test_ins, length); //sort with insertion sort
	finish = std::chrono::high_resolution_clock::now();

	cout << "It took " << chrono::duration_cast<chrono::nanoseconds>(finish-start).count() << "ns.";
	print_array(test_ins, length);

	return 0;
}