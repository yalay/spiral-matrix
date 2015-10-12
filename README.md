#### 概述
面试的时候碰到了该问题，当时想的方法不是很完善，这里完善了下，并且按照自己当时想的思路写出了两种解法，纯原创算法，可能还不完善，功能应该没问题。

#### 试题要求
根据用户输入的数组来输出这样的螺旋矩阵：
 - 用户输入3，输出  
![用户输入3][1]
 - 用户输入4，输出  
![用户输入4][2]
 - 数组从最外层旋转到最里层，依次增加。

#### 可行思路
 1. 思路一  
将输出数据作为一维数组来看待，就变这样了1 2 3 8 9 4 7 6 5，我们统计一下下一个数字的索引号和上一个数字的差值，是这样的：
对于输入3，是0 1 1 3 3 -1 -1 -3 -1 对于输入4，是0 1 1 1 4 4 4 -1 -1 -1 -4 -4 1 1 4 -1
发现规律，数字1因为没有对比，默认差值为0，后面以这样的规律重复这，先出现n-1个1  再n-1个n 再n-1个-1 再n-2个-n，在n-2个1，几个再是反复的。
 2. 思路二  
将输出数据作为二维数组来看待，设定为往右为增加y，往下为增加x：
第一阶段：依次增加y。 第二阶段：依次增加x。 第三阶段：依次减小y。 第四阶段：一次减小y。
每一个阶段之后x和y所对应的数字个数会减一，直到都为0结束。

#### 源码实现
 1. 一维数组法

```c++
// 用一维数组的方式实现
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
```

 2. 二维数组法

```c++
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
    for(i = 1; i < n; i++)
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
```

#### 测试结果
 1. 一维数组法测试3、4 和10  
 ![结果一][3]
 2. 二维数组法测试5、6和12  
 ![结果二][4]
 
#### 完整源代码
[github地址][5]

  [1]: https://raw.githubusercontent.com/yalay/spiral-matrix/master/Demo/1.jpg
  [2]: https://raw.githubusercontent.com/yalay/spiral-matrix/master/Demo/2.jpg
  [3]: https://raw.githubusercontent.com/yalay/spiral-matrix/master/Demo/3.jpg
  [4]: https://raw.githubusercontent.com/yalay/spiral-matrix/master/Demo/4.jpg
  [5]: https://github.com/yalay/spiral-matrix
