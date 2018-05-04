#include <vector>
#include <stdio.h>
#include <ctime>
#include <stdlib.h>

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

int main() {
  srand(time(NULL));
  int num = 10;
  std::vector<int> list;
  for (int i=0;i<num;i++)
    list.push_back(rand()%100000);
  list = selectionSort(list);
}