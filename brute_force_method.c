#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_N 100 // ������������ ����� �������

int n; // ʳ������ ���������� (�� �������)
int matrix[MAX_N][MAX_N]; // ������� �������
int best_perm[MAX_N]; // �������� ������������ (������� �������)

// ������� ���������� ������� �����������
int calculate_cost(int perm[MAX_N]) {
    int cost = 0;
    for (int i = 0; i < n; i++) { // ������ �� ��� �����������
        cost += matrix[i][perm[i]]; // ������ ������� ���������� ��������
    }
    return cost; // ��������� �������� �������
}

// ������� ��� ������������ (��������� ��� �������� ��������)
void swap(int* x, int* y) { // ������� ����� ���� ��������
    int temp = *x;
    *x = *y;
    *y = temp;
}

void permute(int perm[MAX_N], int l, int r) {
    if (l == r) { // ���� ��������� ���� ������������
        int cost = calculate_cost(perm); // ���������� ������� ������������
        static int first = 1; // ���� ��� ����� ������������
        static int best_cost; // �������� �������
        if (first || cost < best_cost) { // ���� �� ����� ��� ����� �������
            first = 0;
            best_cost = cost; // ��������� �������� �������
            for (int i = 0; i < n; i++) { // �������� �������� ������������
                best_perm[i] = perm[i];
            }
        }
    }
    else {
        for (int i = l; i <= r; i++) { // �������� �� ������������ ����������
            swap(&perm[l], &perm[i]);
            permute(perm, l + 1, r);
            swap(&perm[l], &perm[i]); // ��������� ����� (backtrack)
        }
    }
}

int main() {
    SetConsoleOutputCP(1251); // ������������ ��������� ��� ��������� ����
    FILE* get_data = fopen("input1.txt", "r"); // ³�������� ���� ��� �������
    if (get_data == NULL) {
        printf("���� �� �������. �������� ��������� ������.\n");
        exit(1);
    }

    fscanf(get_data, "%d", &n); // ������� ����� �������
    if (n > MAX_N) { // �������� �� ����������� ����������� ������
        printf("����� ������� �������� ��������� ����.\n");
        fclose(get_data);
        exit(1);
    }

    // ���������� ������� �������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(get_data, "%d", &matrix[i][j]);
        }
    }
    fclose(get_data); // ��������� ����

    int perm[MAX_N]; // ����� ��� ���������� ������������
    for (int i = 0; i < n; i++) {
        perm[i] = i; // ���������� ��������� ������������
    }

    permute(perm, 0, n - 1); // �������� �� ������������ �� ������ ����������

    printf("������� �������:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", matrix[i][j]); // ����������� ��� ������� �������
        }
        printf("\n");
    }
    printf("\n");

    int best_cost = calculate_cost(best_perm); // ���������� ������� �������� ������������
    printf("������� ���������� �������: %d\n", best_cost);
    printf("�����������: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", best_perm[i] + 1); // ���� ���������� ������� (1-based)
    }
    printf("\n");

    return 0; // ���������� ��������
}