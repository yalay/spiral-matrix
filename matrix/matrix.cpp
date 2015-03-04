// matrix.cpp : 定义控制台应用程序的入口点。
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
输出类似这样的矩阵，螺旋矩阵
对于输入3，输出这样的
1 2 3
8 9 4
7 6 5

对于输入4，输出这样的
1   2  3  4
12 13 14  5
11 16 15  6
10  9  8  7
*/
// 找规律用一维数组的方式实现
void PrintMatrix(int n)
{
	if ((n < 1) || (n > MAX_NUM))
	{
		return;
	}

	// n输出的数字个数为n*n个
	const int total_num = n*n;
	int *step = new int[total_num];
	int *data = new int[total_num];
	InitArray(step, total_num);
	InitArray(data, total_num);
	
	// 找规律，对于下一个数字所在位置和上一个数字位置的差值做下统计
	// 比如3矩阵的位置步进数 1 1 3 3 -1 -1 -3 -1
	// 比如4矩阵的位置步进数 1 1 1 4 4 4 -1 -1 -1 -4 -4 1 1 4 -1
	// 统计规律是这样的
	// 先出现n-1个1  再n-1个n 再n-1个-1 再n-2个-n，在n-2个1，反复，直到步进数目达到n*n -1个
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

// 计算相邻数字位置差值
void CalcStep(int *step, int num)
{
	if (step == NULL || num <= 0)
	{
		return;
	}
	
	// 第一个步进数为从0到0，是0，再n-1个1
	step[0] = 0;
	int i = 1;
	for (; i < num; i++)
	{
		step[i] = 1;
	}

	// 再n-1个n 再n-1个-1 再n-2个-n，在n-2个1，反复，
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

// 二维数组方式
/*
对于输入3，输出这样的
1 2 3
8 9 4
7 6 5

分四阶段
第一阶段：依次增加x。
第二阶段：依次增加y。
第三阶段：依次减小x。
第四阶段：依次减小y。
每一个阶段之后x和y所对应的数字个数会减一，直到都为0结束。

*/
void PrintMatrixBy2D(int n)
{
	if ((n < 1) || (n > MAX_NUM))
	{
		return;
	}

	// 构造二维数组，用一维指针数组指向一个全部数量的一维数组
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

	// 每一个阶段之后x和y所对应的数字个数会减一，直到都为0结束。
	int current_num = 0;
	while ((current_x_num > 0) || (current_y_num > 0))
	{
		// 第一阶段：依次增加x。
		for (i = 0; i < current_x_num; i++)
		{
			data[++current_x_position][current_y_position] = ++current_num;
		}
		current_x_num--;

		// 第二阶段：依次增加y。
		for (i = 0; i < current_y_num; i++)
		{
			data[current_x_position][++current_y_position] = ++current_num;
		}
		current_y_num--;

		// 第三阶段：依次减小x。
		for (i = 0; i < current_x_num; i++)
		{
			data[--current_x_position][current_y_position] = ++current_num;
		}
		current_x_num--;

		// 第四阶段：依次减小y。
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



