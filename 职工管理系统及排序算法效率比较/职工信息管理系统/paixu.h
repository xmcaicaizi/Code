#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stack>

#define ARRAY_MAX_SIZE 50000  // ������󳤶�

int swap_cout = 0;//swap �������ô��� ȫ�ֱ���

// �������������ڽ�������������Ԫ�ص�λ��
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    swap_cout++;
}

// ð������
void BubbleSort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// ��������
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

// ϣ������
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

// �����㷨�������黮��Ϊ�������֣������ػ��ֵ������
int Partition(int arr[], int low, int high) {
    int pivot = arr[low];  // �Ե�һ��Ԫ����Ϊ���ֵ�
    int left = low + 1;    // ��ָ��
    int right = high;      // ��ָ��
    while (1) {
        // ��ָ�������ƶ���ֱ���ҵ����ڻ��ֵ��Ԫ��
        while (left <= right && arr[left] <= pivot)
            left++;
        // ��ָ�������ƶ���ֱ���ҵ�С�ڻ��ֵ��Ԫ��
        while (left <= right && arr[right] >= pivot)
            right--;
        // �����ָ�������ָ�룬����ѭ��
        if (left > right)
            break;
        // ��������ָ����ָ���Ԫ��
        swap(&arr[left], &arr[right]);
    }
    // �����ֵ���õ���ȷ��λ��
    swap(&arr[low], &arr[right]);
    return right;  // ���ػ��ֵ������
}

// �ǵݹ��������
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

// ��������������������startΪ���ڵ���Ӷѣ�ʹ��������������
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

// ������
void HeapSort(int arr[], int len) {
    // �������ѣ������һ����Ҷ�ڵ㿪ʼ�������ѵ���
    for (int i = len / 2 - 1; i >= 0; i--) {
        MaxHeapify(arr, i, len - 1);
    }
    // �����Ѷ�Ԫ�أ����ֵ���Ͷ������һ��Ԫ�أ�����ʣ��Ԫ�ؽ������ѵ���
    for (int i = len - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        MaxHeapify(arr, 0, i - 1);
    }
}

// �鲢����ĺϲ�����������������������ϲ�Ϊһ����������
void Merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;   // ��������ĳ���
    int n2 = right - mid;      // ��������ĳ���
    int* L = new int[n1];      // ��������
    int* R = new int[n2];      // ��������
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

// �ݹ�鲢���򣬽�����ָ�Ϊ������������еݹ�����Ȼ��ϲ���������������
void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // �����м�λ��
        MergeSort(arr, left, mid);            // �����������������
        MergeSort(arr, mid + 1, right);       // �����������������
        Merge(arr, left, mid, right);         // �ϲ���������������
    }
}

// ���Ժ��������ڲ��������㷨�����ܺ��ȶ���
void TestSort(const char* sort_name, void (*sort_func)(int[], int), int arr[], int len) {
    clock_t start, end;
    double cpu_time_used;

    int* copy_arr = new int[len];
    memcpy(copy_arr, arr, len * sizeof(int));

    start = clock();
    (*sort_func)(copy_arr, len);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;


    printf("%s ���� %f ��ִ��\n", sort_name, cpu_time_used);
    printf("\t�ؼ����ƶ�������%d\n", swap_cout);
    swap_cout = 0;

    delete[] copy_arr;
}

// ���Ժ��������ڲ��������㷨�����ܺ��ȶ���
void TestSort2(const char* sort_name, void (*sort_func)(int[], int, int), int arr[], int len) {
    clock_t start, end;
    double cpu_time_used;

    int* copy_arr = new int[len];
    memcpy(copy_arr, arr, len * sizeof(int));

    start = clock();
    (*sort_func)(copy_arr,0, len-1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;


    printf("%s ���� %f ��ִ��\n", sort_name, cpu_time_used);
    printf("\t�ؼ����ƶ�������%d\n", swap_cout);
    swap_cout = 0;

    delete[] copy_arr;
}

// ������ԣ����ڲ��Ը��������㷨�����ܺ��ȶ���
void SortTest() {
    const int num_datasets = 5;
    const int dataset_size = ARRAY_MAX_SIZE;

    int datasets[num_datasets][dataset_size];

    // ����������ݼ�
    srand(time(NULL));
    for (int i = 0; i < num_datasets; i++) {
        for (int j = 0; j < dataset_size; j++) {
            datasets[i][j] = rand() % 100;
        }
    }

    // ��ÿ�����ݼ����������㷨�Ĳ���
    for (int i = 0; i < num_datasets; i++) {
        printf("���ݼ� %d��\n", i + 1);
        TestSort("��������", InsertionSort, datasets[i], dataset_size);
        TestSort("ϣ������", ShellSort, datasets[i], dataset_size);
        TestSort2("��������", QuickSortIterative, datasets[i], dataset_size);
        TestSort2("�鲢����", MergeSort, datasets[i], dataset_size);
        TestSort("������", HeapSort, datasets[i], dataset_size);
        printf("\n");
    }
}
