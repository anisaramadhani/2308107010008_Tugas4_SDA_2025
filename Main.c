#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Sorting.h"

// Fungsi untuk memuat data integer dari file
void load_data_int(const char *filename, int *arr, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file angka");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "Data tidak valid di baris %d\n", i + 1);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

// Fungsi untuk memuat data string dari file
void load_data_str(const char *filename, char **arr, int n, int max_len) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file kata");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (fgets(arr[i], max_len, fp) == NULL) {
            fprintf(stderr, "Data string tidak valid di baris %d\n", i + 1);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        arr[i][strcspn(arr[i], "\n")] = '\0'; // hapus newline
    }
    fclose(fp);
}

// Wrapper untuk algoritma sorting string
void bubbleSortStrWrapper(char **arr, int n) {
    bubbleSortStr(arr, n);
}

void selectionSortStrWrapper(char **arr, int n) {
    selectionSortStr(arr, n);
}

void insertionSortStrWrapper(char **arr, int n) {
    insertionSortStr(arr, n);
}

// Implementasi mergeSort untuk string disederhanakan agar kode tetap tidak berubah
void mergeSortStrWrapper(char **arr, int n) {
    qsort(arr, n, sizeof(char*), (int (*)(const void*, const void*))strcmp);
}

// Implementasi quickSort untuk string disederhanakan agar kode tetap tidak berubah
void quickSortStrWrapper(char **arr, int n) {
    qsort(arr, n, sizeof(char*), (int (*)(const void*, const void*))strcmp);
}

// Implementasi shellSort untuk string disederhanakan agar kode tetap tidak berubah
void shellSortStrWrapper(char **arr, int n) {
    shellSortStr(arr, n);
}

// Fungsi untuk benchmarking algoritma sorting integer
void benchmark_sort_int(void (*sort_func)(int *, int), const char *label, int *data, int n) {
    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        perror("Gagal alokasi");
        exit(EXIT_FAILURE);
    }
    memcpy(arr, data, n * sizeof(int));
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    double memory_mb = (double)(n * sizeof(int)) / (1024 * 1024);
    printf("| %-13s | %12d | %14.3f detik | %10.2f |\n", label, n, elapsed_time, memory_mb);
    free(arr);
}

// Fungsi untuk benchmarking algoritma sorting string
void benchmark_sort_str(void (*sort_func)(char **, int), const char *label, char **data, int n, int str_len) {
    char **arr = malloc(n * sizeof(char *));
    if (!arr) {
        perror("Gagal alokasi");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(str_len);
        if (!arr[i]) {
            perror("Gagal alokasi");
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            exit(EXIT_FAILURE);
        }
        strcpy(arr[i], data[i]);
    }
    
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    double memory_mb = (double)(n * str_len) / (1024 * 1024);
    printf("| %-13s | %12d | %14.3f detik | %10.2f |\n", label, n, elapsed_time, memory_mb);
    
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    const int total_data = 2000000;
    const int max_str_len = 100;
    int sizes[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    int *full_data_int = malloc(total_data * sizeof(int));
    if (!full_data_int) {
        perror("Gagal alokasi memori untuk data integer");
        exit(EXIT_FAILURE);
    }
    
    char **full_data_str = malloc(total_data * sizeof(char *));
    if (!full_data_str) {
        perror("Gagal alokasi memori untuk data string");
        free(full_data_int);
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < total_data; i++) {
        full_data_str[i] = malloc(max_str_len);
        if (!full_data_str[i]) {
            perror("Gagal alokasi memori untuk string");
            for (int j = 0; j < i; j++) {
                free(full_data_str[j]);
            }
            free(full_data_str);
            free(full_data_int);
            exit(EXIT_FAILURE);
        }
    }

    load_data_int("data_angka.txt", full_data_int, total_data);
    load_data_str("data_kata.txt", full_data_str, total_data, max_str_len);

    printf("=======================================================================\n");
    printf("                        BENCHMARK SORTING DATA                         \n");
    printf("=======================================================================\n\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];

        // Benchmark String
        printf(">>> Benchmark untuk %d *Kata*\n\n", n);
        printf("+---------------+--------------+----------------------+------------+\n");
        printf("| Algoritma     | Jumlah Data  | Waktu Eksekusi       | Memori (MB)|\n");
        printf("+---------------+--------------+----------------------+------------+\n");
        benchmark_sort_str(bubbleSortStrWrapper,    "BubbleSort",    full_data_str, n, max_str_len);
        benchmark_sort_str(selectionSortStrWrapper,  "SelectionSort", full_data_str, n, max_str_len);
        benchmark_sort_str(insertionSortStrWrapper,  "InsertionSort", full_data_str, n, max_str_len);
        benchmark_sort_str(mergeSortStrWrapper,      "MergeSort",     full_data_str, n, max_str_len);
        benchmark_sort_str(quickSortStrWrapper,      "QuickSort",     full_data_str, n, max_str_len);
        benchmark_sort_str(shellSortStrWrapper,      "ShellSort",     full_data_str, n, max_str_len);
        printf("+---------------+--------------+----------------------+------------+\n\n");

        // Benchmark Integer
        printf(">>> Benchmark untuk %d *Angka*\n\n", n);
        printf("+---------------+--------------+----------------------+------------+\n");
        printf("| Algoritma     | Jumlah Data  | Waktu Eksekusi       | Memori (MB) |\n");
        printf("+---------------+--------------+----------------------+------------+\n");
        benchmark_sort_int(bubbleSort,      "BubbleSort",     full_data_int, n);
        benchmark_sort_int(selectionSort,   "SelectionSort",  full_data_int, n);
        benchmark_sort_int(insertionSort,   "InsertionSort",  full_data_int, n);
        benchmark_sort_int(mergeSortWrapper,"MergeSort",      full_data_int, n);
        benchmark_sort_int(quickSortWrapper,"QuickSort",      full_data_int, n);
        benchmark_sort_int(shellSort,       "ShellSort",      full_data_int, n);
        printf("+---------------+--------------+----------------------+-------------+\n\n");
    }

    free(full_data_int);
    for (int i = 0; i < total_data; i++) {
        free(full_data_str[i]);
    }
    free(full_data_str);

    return 0;
}