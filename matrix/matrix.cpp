// matrix.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define MAX_NUM 128

void InitArray(int *array, int num);
void CalcStep(int *array, int num);
void PrintMatrix(int n);
void PrintMatrixBy2D(int n);

int _tmain(int argc, _TCHAR* argv[])
{
	PrintMatrix(3);
	PrintMatrix(4);
	PrintMatrix(10);

	PrintMatrixBy2D(5);
	PrintMatrixBy2D(6);
	PrintMatrixBy2D(12);

	getchar();
	return 0;
}


/*
������������ľ�����������
��������3�����������
1 2 3
8 9 4
7 6 5

��������4�����������
1   2  3  4
12 13 14  5
11 16 15  6
10  9  8  7
*/
// �ҹ�����һά����ķ�ʽʵ��
void PrintMatrix(int n)
{
	if ((n < 1) || (n > MAX_NUM))
	{
		return;
	}

	// n��������ָ���Ϊn*n��
	const int total_num = n*n;
	int *step = new int[total_num];
	int *data = new int[total_num];
	InitArray(step, total_num);
	InitArray(data, total_num);
	
	// �ҹ��ɣ�������һ����������λ�ú���һ������λ�õĲ�ֵ����ͳ��
	// ����3�����λ�ò����� 1 1 3 3 -1 -1 -3 -1
	// ����4�����λ�ò����� 1 1 1 4 4 4 -1 -1 -1 -4 -4 1 1 4 -1
	// ͳ�ƹ�����������
	// �ȳ���n-1��1  ��n-1��n ��n-1��-1 ��n-2��-n����n-2��1��������ֱ��������Ŀ�ﵽn*n -1��
	int total_step = 0;
	int i = 0;
	CalcStep(step, n);
	for (i = 0; i < total_num; i++)
	{
		total_step += step[i];
		data[total_step] = i + 1; 
	}

	for (i = 0; i < total_num; i++)
	{
		printf("%-3d ",data[i]);
		if ((i + 1) % n == 0)
		{
			printf("\n");
		}
	}

	printf("\n");

	delete[] step;
	delete[] data;

}

// ������������λ�ò�ֵ
void CalcStep(int *step, int num)
{
	if (step == NULL || num <= 0)
	{
		return;
	}
	
	// ��һ��������Ϊ��0��0����0����n-1��1
	step[0] = 0;
	int i = 1;
	for (; i < num; i++)
	{
		step[i] = 1;
	}

	// ��n-1��n ��n-1��-1 ��n-2��-n����n-2��1��������
	int count = num - 1;
	while (count > 0)
	{
		int k = 0;
		if ((num - count) % 2 == 1)
		{	
			for (k = 0; k < count; k++)
			{
				step[i++] = num;
			}

			for (k = 0; k < count; k++)
			{
				step[i++] = -1;
			}
		}
		else
		{
			for (k = 0; k < count; k++)
			{
				step[i++] = -num;
			}

			for (k = 0; k < count; k++)
			{
				step[i++] = 1;
			}
		}

		count--;
	}

}

void InitArray(int *array, int num)
{
	if (array == NULL || num <= 0)
	{
		return;
	}

	for (int i = 0; i < num; i++)
	{
		array[i] = 0;
	}
}

// ��ά���鷽ʽ
/*
��������3�����������
1 2 3
8 9 4
7 6 5

���Ľ׶�
��һ�׶Σ���������x��
�ڶ��׶Σ���������y��
�����׶Σ����μ�Сx��
���Ľ׶Σ����μ�Сy��
ÿһ���׶�֮��x��y����Ӧ�����ָ������һ��ֱ����Ϊ0������

*/
void PrintMatrixBy2D(int n)
{
	if ((n < 1) || (n > MAX_NUM))
	{
		return;
	}

	// �����ά���飬��һάָ������ָ��һ��ȫ��������һά����
	int i = 0;
	const int total_num = n*n;
	int **data = new int*[n];
	data[0] = new int[total_num];   
	for(int i = 1; i < n; i++)  
	{
		data[i] = data[i - 1] + n;
	}

	int current_x_position = -1;
	int current_y_position = 0;
	int current_x_num = n;
	int current_y_num = n - 1;

	// ÿһ���׶�֮��x��y����Ӧ�����ָ������һ��ֱ����Ϊ0������
	int current_num = 0;
	while ((current_x_num > 0) || (current_y_num > 0))
	{
		// ��һ�׶Σ���������x��
		for (i = 0; i < current_x_num; i++)
		{
			data[++current_x_position][current_y_position] = ++current_num;
		}
		current_x_num--;

		// �ڶ��׶Σ���������y��
		for (i = 0; i < current_y_num; i++)
		{
			data[current_x_position][++current_y_position] = ++current_num;
		}
		current_y_num--;

		// �����׶Σ����μ�Сx��
		for (i = 0; i < current_x_num; i++)
		{
			data[--current_x_position][current_y_position] = ++current_num;
		}
		current_x_num--;

		// ���Ľ׶Σ����μ�Сy��
		for (i = 0; i < current_y_num; i++)
		{
			data[current_x_position][--current_y_position] = ++current_num;
		}
		current_y_num--;
	}

	printf("\n");
	for (i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			printf("%-3d ",data[k][i]);
		}
		printf("\n");
	}

	delete[]data[0];
	delete[]data; 
}



