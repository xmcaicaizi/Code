#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stack>

#define ARRAY_MAX_SIZE 50000  // 数组最大长度

int swap_cout = 0;//swap 函数调用次数 全局变量

// 交换函数，用于交换数组中两个元素的位置
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swap_cout++;
}

// 冒泡排序
void BubbleSort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// 插入排序
void InsertionSort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            swap_cout++;
        }
        arr[j + 1] = key;
    }
}

// 希尔排序
void ShellSort(int arr[], int len) {
    for (int gap = len / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < len; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
            swap_cout++;
        }
    }
}

// 划分算法，将数组划分为两个部分，并返回划分点的索引
int Partition(int arr[], int low, int high) {
    int pivot = arr[low];  // 以第一个元素作为划分点
    int left = low + 1;    // 左指针
    int right = high;      // 右指针
    while (1) {
        // 左指针向右移动，直到找到大于划分点的元素
        while (left <= right && arr[left] <= pivot)
            left++;
        // 右指针向左移动，直到找到小于划分点的元素
        while (left <= right && arr[right] >= pivot)
            right--;
        // 如果左指针大于右指针，跳出循环
        if (left > right)
            break;
        // 交换左右指针所指向的元素
        swap(&arr[left], &arr[right]);
    }
    // 将划分点放置到正确的位置
    swap(&arr[low], &arr[right]);
    return right;  // 返回划分点的索引
}

// 非递归快速排序
void QuickSortIterative(int arr[], int left, int right) {
    std::stack<int> stack;
    stack.push(left);
    stack.push(right);

    while (!stack.empty()) {
        right = stack.top();
        stack.pop();
        left = stack.top();
        stack.pop();

        while (left < right) {
            int pivotIndex = Partition(arr, left, right);

            if (pivotIndex - left < right - pivotIndex) {
                stack.push(pivotIndex + 1);
                stack.push(right);
                right = pivotIndex - 1;
            }
            else {
                stack.push(left);
                stack.push(pivotIndex - 1);
                left = pivotIndex + 1;
            }
        }
    }
}

// 堆排序辅助函数，调整以start为根节点的子堆，使其满足最大堆性质
void MaxHeapify(int arr[], int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1])
            son++;
        if (arr[dad] >= arr[son])
            return;
        swap(&arr[dad], &arr[son]);
        dad = son;
        son = dad * 2 + 1;
    }
}

// 堆排序
void HeapSort(int arr[], int len) {
    // 构建最大堆，从最后一个非叶节点开始进行最大堆调整
    for (int i = len / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, i, len - 1);
    }
    // 交换堆顶元素（最大值）和堆中最后一个元素，并对剩余元素进行最大堆调整
    for (int i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        MaxHeapify(arr, 0, i - 1);
    }
}

// 归并排序的合并函数，将两个有序子数组合并为一个有序数组
void Merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;   // 左子数组的长度
    int n2 = right - mid;      // 右子数组的长度
    int* L = new int[n1];      // 左子数组
    int* R = new int[n2];      // 右子数组
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            swap_cout++;
        }
        else {
            arr[k] = R[j];
            j++;
            swap_cout++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

// 递归归并排序，将数组分割为两个子数组进行递归排序，然后合并两个有序子数组
void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // 计算中间位置
        MergeSort(arr, left, mid);            // 对左子数组进行排序
        MergeSort(arr, mid + 1, right);       // 对右子数组进行排序
        Merge(arr, left, mid, right);         // 合并两个有序子数组
    }
}

// 测试函数，用于测试排序算法的性能和稳定性
void TestSort(const char* sort_name, void (*sort_func)(int[], int), int arr[], int len) {
    clock_t start, end;
    double cpu_time_used;

    int* copy_arr = new int[len];
    memcpy(copy_arr, arr, len * sizeof(int));

    start = clock();
    (*sort_func)(copy_arr, len);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;


    printf("%s 花费 %f 秒执行\n", sort_name, cpu_time_used);
    printf("\t关键字移动次数：%d\n", swap_cout);
    swap_cout = 0;

    delete[] copy_arr;
}

// 测试函数，用于测试排序算法的性能和稳定性
void TestSort2(const char* sort_name, void (*sort_func)(int[], int, int), int arr[], int len) {
    clock_t start, end;
    double cpu_time_used;

    int* copy_arr = new int[len];
    memcpy(copy_arr, arr, len * sizeof(int));

    start = clock();
    (*sort_func)(copy_arr,0, len-1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;


    printf("%s 花费 %f 秒执行\n", sort_name, cpu_time_used);
    printf("\t关键字移动次数：%d\n", swap_cout);
    swap_cout = 0;

    delete[] copy_arr;
}

// 排序测试，用于测试各个排序算法的性能和稳定性
void SortTest() {
    const int num_datasets = 5;
    const int dataset_size = ARRAY_MAX_SIZE;

    int datasets[num_datasets][dataset_size];

    // 生成随机数据集
    srand(time(NULL));
    for (int i = 0; i < num_datasets; i++) {
        for (int j = 0; j < dataset_size; j++) {
            datasets[i][j] = rand() % 100;
        }
    }

    // 对每个数据集进行排序算法的测试
    for (int i = 0; i < num_datasets; i++) {
        printf("数据集 %d：\n", i + 1);
        TestSort("插入排序", InsertionSort, datasets[i], dataset_size);
        TestSort("希尔排序", ShellSort, datasets[i], dataset_size);
        TestSort2("快速排序", QuickSortIterative, datasets[i], dataset_size);
        TestSort2("归并排序", MergeSort, datasets[i], dataset_size);
        TestSort("堆排序", HeapSort, datasets[i], dataset_size);
        printf("\n");
    }
}
