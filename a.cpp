#include <vector>
#include <string>
#include <stdio.h>
#include <ctime>

std::vector<int> selectionSort(std::vector<int> list);
std::vector<int> bubbleSort(std::vector<int> list);
std::vector<int> quickSort(std::vector<int> list);
std::vector<int> radixSortMSD(std::vector<int> list);
std::vector<int> radixSortREC(std::vector<int> list);
std::vector<int> mergeSort(std::vector<int> input);
void printIntVector(const std::vector<int> &list);
void averageEachSort(int sampleSize, int jSize);

int main (int argc, char *argv[])
{
	averageEachSort(std::stoi(argv[1]), std::stoi(argv[2]));
	return 0;
};

std::vector<int> selectionSort(std::vector<int> list)
{
	int min = 0;
	int listSize = list.size();
	for (int i = 0; i < listSize; i++)
	{
		min = i;
		for (int j = i+1; j < listSize; j++)
		{
			if (list[j] < list[min])
			{
				min = j;
			}
		}
		int tmp = list[i];
		list[i] = list[min];
		list[min] = tmp;
	}
	return list;
};

std::vector<int> bubbleSort(std::vector<int> list)
{
	int passes = 1;
	int listSize = list.size();
	while(passes)
	{
		passes ^= passes;
		for (int i = 1; i < listSize; i++)
		{
			if (list[i] < list[i-1])
			{
				int tmp = list[i];
				list[i] = list[i-1];
				list[i-1] = tmp;
				passes++;
			}
		}
	}
	return list;
	
};

std::vector<int> quickSort(std::vector<int> list)
{
	unsigned int listLength = list.size();
	unsigned int pivot = listLength>>1;
	if (pivot > 650)
	{
		int pivotValue = list[pivot];
		for (int i = 0; i < listLength; i++)
		{
			if (list[i] < pivotValue && i > pivot)
			{
				int tmp = list[i];
				list.erase(list.begin()+i);
				list.emplace(list.begin()+pivot, tmp);
				pivot++;
				i--;
			}
			else if (list[i] > pivotValue && i < pivot)
			{
				int tmp = list[i];
				list.erase(list.begin()+i);
				list.emplace(list.begin()+pivot+1, tmp);
				pivot--;
				i--;
			}
		}
		std::vector<int> tmp1(list.begin(), list.begin()+pivot-1);
		tmp1 = quickSort(tmp1);
		std::vector<int> tmp2(list.begin()+pivot, list.end());
		tmp2 = quickSort(tmp2);
		for (int i = 0; i < tmp2.size(); i++)
			tmp1.push_back(tmp2[i]);
		return tmp1;
	}
	else
	{
		return selectionSort(list);
	}
	//else
		//return list;
};

std::vector<int> radixSortMSD(std::vector<int> list)
{
	// Find maximum
	// This is so that the elements can be correctly added to 'buckets'
	int maximum = list[0];
	int listSize = list.size(); // Actually has some difference to the speed
	for (int i = 0; i < listSize; i++)
	{
		if (list[i] > maximum)
			maximum = list[i];
	}
	
	// Finds number of digits
	// So that it can sort by the correct digit
	int digits = 1;
	maximum -= maximum % 10;
	while(maximum > 9)
	{
		maximum /= 10;
		digits++;
	}
	
	// lists = the 'buckets'
	std::vector<int> lists[10];
	// valdig = value to sort the values into each bucket
	int valdig = 10;
	for (int i = 1; i < digits; i++)
		valdig *= 10;
	
	
	for (int i = 0; i < listSize; i++)
	{
		lists[(list[i]-list[i]%10)/valdig].push_back(list[i]);
	}
	list.resize(0);
	for (int i = 0; i < 10; i++)
	{
		std::vector<int> tmp = quickSort(lists[i]);
		int tmpSize = tmp.size();
		for (int j = 0; j < tmpSize; j++)
			list.push_back(tmp[j]);
	}
	return list;
};

std::vector<int> radixSortREC(std::vector<int> list)
{
	// Find maximum
	// This is so that the elements can be correctly added to 'buckets'
	int maximum = list[0];
	int listSize = list.size(); // Actually has some difference to the speed
	for (int i = 0; i < listSize; i++)
	{
		if (list[i] > maximum)
			maximum = list[i];
	}
	
	// Finds number of digits
	// So that it can sort by the correct digit
	int digits = 1;
	maximum -= maximum % 10;
	while(maximum > 9)
	{
		maximum /= 10;
		digits++;
	}
	
	// lists = the 'buckets'
	std::vector<int> lists[10];
	// valdig = value to sort the values into each bucket
	int valdig = 10;
	for (int i = 1; i < digits; i++)
		valdig *= 10;
	
	for (int i = 0; i < listSize; i++)
	{
		lists[(list[i]-list[i]%10)/valdig].push_back(list[i]);
	}
	list.resize(0);
	for (int i = 0; i < 10; i++)
	{
		if (lists[i].size())
		{
			std::vector<int> tmp = radixSortMSD(lists[i]);
			int tmpSize = tmp.size();
			for (int j = 0; j < tmpSize; j++)
				list.push_back(tmp[j]);
		}
	}
	return list;
};

std::vector<int> mergeSort(std::vector<int> input)
{
	std::vector<int> output, left, right;
	// If the input size is 1 or 0 then it is sorted, and the size cannot be negative so this will catch all cases
	if (input.size() <= 1)
		return input;
	// Initialise the sublists
	for (int i = input.size(); i;)
	{
		if(--i&1)
			left.push_back(input[i]);
		else
			right.push_back(input[i]);
	}
	// Recursively sort each sublist
	left = mergeSort(left);
	right = mergeSort(right);
	// This is the part where the sublists are actually sorted,
	// but only if both sublists have items in, because if they do not then they cannot be compared
	while (left.size() && right.size())
	{
		if (left[0] < right[0])
		{
			output.push_back(left[0]);
			left.erase(left.begin());
		}
		else
		{
			output.push_back(right[0]);
			right.erase(right.begin());
		}
	}
	// These 2 ifs catch any stragglers which may be in either list,
	// it appends each item of the remaining list to the output as the remainder of the list must be sorted
	if (left.size())
		for (int i = left.size(); i;)
			output.push_back(left[--i]);
	if (right.size())
		for (int i = right.size(); i;)
			output.push_back(right[--i]);
	// Returns the sorted list
	return output;
};

void printIntVector(std::vector<int> list)
{
	for (int i = 0; i < list.size(); i++)
		printf("%d ", list[i]);
	printf("\n");
};

void averageEachSort(int sampleSize, int jSize)
{
	int elementSize = 10;
	double samples[6];
	for (int j = 0; j < jSize; j++)
	{
		elementSize <<= 2;
		for (int Kx3 = 0; Kx3 < 5; Kx3++)
			samples[Kx3] = 0;
		for (int i = 0; i < sampleSize; i++)
		{
			srand(time(NULL));
			std::vector<int> oList;
			for (int l = 0; l < elementSize; l++)
				oList.push_back(rand()%100000);
			std::vector<int> list;
			int start, stop;
			if (j < 5)
			{
				start = clock();
				list = oList;
				bubbleSort(list);
				stop = clock();
				samples[0] += (stop-start)/double(CLOCKS_PER_SEC)*1000;
			}
			if ((j < 6 && sampleSize < 4) || j < 5)
			{
				start = clock();
				list = oList;
				selectionSort(list);
				stop = clock();
				samples[1] += (stop-start)/double(CLOCKS_PER_SEC)*1000;
			}
			list = oList;
			start = clock();
			quickSort(list);
			stop = clock();
			samples[2] += (stop-start)/double(CLOCKS_PER_SEC)*1000;
			list = oList;
			start = clock();
			radixSortMSD(list);
			stop = clock();
			samples[3] += (stop-start)/double(CLOCKS_PER_SEC)*1000;
			list = oList;
			start = clock();
			radixSortREC(list);
			stop = clock();
			samples[4] += (stop-start)/double(CLOCKS_PER_SEC)*1000;
			list=oList;
			start=clock();
			mergeSort(list);
			stop = clock();
			samples[5] += (stop-start)/double(CLOCKS_PER_SEC)*1000;
		}
		printf("Num. Elements: %d\tSample Size: %d\n", elementSize, sampleSize);
		if (j < 5) printf("Bubble Sort: %f milliseconds\n", samples[0]/(double)sampleSize);
		if ((j < 6 && sampleSize < 4) || j < 5) printf("Selection Sort: %f milliseconds\n", samples[1]/(double)sampleSize);
		printf("Quick Sort: %f milliseconds\n", samples[2]/(double)sampleSize);
		printf("Radix Sort (MSD): %f milliseconds\n", samples[3]/(double)sampleSize);
		printf("Radix Sort (REC): %f milliseconds\n", samples[4]/(double)sampleSize);
		printf("MergeSort: %f milliseconds\n", samples[5]/(double)sampleSize);
		printf("\n\n");
	}
	printf("DONE!!\n");
};