#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_N 100 // Максимальний розмір матриці

int n; // Кількість працівників (та завдань)
int matrix[MAX_N][MAX_N]; // Матриця вартості
int best_perm[MAX_N]; // Найкраща перестановка (розподіл завдань)

// Функція обчислення вартості призначення
int calculate_cost(int perm[MAX_N]) {
    int cost = 0;
    for (int i = 0; i < n; i++) { // Прохід по всіх працівниках
        cost += matrix[i][perm[i]]; // Додаємо вартість відповідного завдання
    }
    return cost; // Повертаємо загальну вартість
}

// Функція для перестановок (генерація всіх можливих розподілів)
void swap(int* x, int* y) { // Функція обміну двох елементів
    int temp = *x;
    *x = *y;
    *y = temp;
}

void permute(int perm[MAX_N], int l, int r) {
    if (l == r) { // Якщо досягнуто кінця перестановки
        int cost = calculate_cost(perm); // Обчислюємо вартість перестановки
        static int first = 1; // Флаг для першої перестановки
        static int best_cost; // Найкраща вартість
        if (first || cost < best_cost) { // Якщо це перша або краща вартість
            first = 0;
            best_cost = cost; // Оновлюємо найкращу вартість
            for (int i = 0; i < n; i++) { // Зберігаємо найкращу перестановку
                best_perm[i] = perm[i];
            }
        }
    }
    else {
        for (int i = l; i <= r; i++) { // Генеруємо всі перестановки рекурсивно
            swap(&perm[l], &perm[i]);
            permute(perm, l + 1, r);
            swap(&perm[l], &perm[i]); // Повертаємо назад (backtrack)
        }
    }
}

int main() {
    SetConsoleOutputCP(1251); // Встановлення кодування для української мови
    FILE* get_data = fopen("input1.txt", "r"); // Відкриваємо файл для читання
    if (get_data == NULL) {
        printf("Файл не відкрито. Програма завершить роботу.\n");
        exit(1);
    }

    fscanf(get_data, "%d", &n); // Зчитуємо розмір матриці
    if (n > MAX_N) { // Перевірка на перевищення допустимого розміру
        printf("Розмір матриці перевищує допустиму межу.\n");
        fclose(get_data);
        exit(1);
    }

    // Зчитування матриці вартості
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(get_data, "%d", &matrix[i][j]);
        }
    }
    fclose(get_data); // Закриваємо файл

    int perm[MAX_N]; // Масив для збереження перестановки
    for (int i = 0; i < n; i++) {
        perm[i] = i; // Ініціалізуємо початкову перестановку
    }

    permute(perm, 0, n - 1); // Генеруємо всі перестановки та шукаємо оптимальну

    printf("Матриця вартості:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", matrix[i][j]); // Вирівнювання для гарного вигляду
        }
        printf("\n");
    }
    printf("\n");

    int best_cost = calculate_cost(best_perm); // Обчислюємо вартість найкращої перестановки
    printf("Вартість найкращого варіанту: %d\n", best_cost);
    printf("Призначення: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", best_perm[i] + 1); // Вивід найкращого варіанту (1-based)
    }
    printf("\n");

    return 0; // Завершення програми
}