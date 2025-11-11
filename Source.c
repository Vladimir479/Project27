#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define PI 3.14159265358979323846
#define MAX_ITERATIONS 16 // Для суммы от n=0 до 15

// Функция для вычисления факториала
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Основная функция f(x)
double f(double x) {
    // Проверка области определения
    if (x < 1) {
        // Первая часть: (x^2 - 4)/(x - 2)
        return (x * x - 4) / (x - 2);
    }
    else if (x >= 1 && x < PI / 2) {
        // Вторая часть: sec(x) - tan(x)
        double cos_x = cos(x);
        return 1 / cos_x - sin(x) / cos_x;
    }
    else if (x >= PI / 2) {
        // Третья часть: сумма ряда
        double sum = 0;
        for (int n = 0; n <= 15; n++) {
            double term = pow(-1, n) * pow(x, 3 * n) / factorial(3 * n + 1);
            sum += term;
        }
        return sum;
    }
    return NAN; // На случай, если ни одно условие не выполнилось
}

// Функция для вычисления производной численным методом
double derivative(double x, double h) {
    if (isnan(f(x - h)) || isnan(f(x + h))) {
        return NAN;
    }
    return (f(x + h) - f(x - h)) / (2 * h);
}

// Функция для табулирования
void tabulate(double start, double end, double step) {
    printf("\n=== Таблица значений функции ===\n");
    printf("%-15s %-20s\n", "x", "f(x)");
    printf("---\n");
    for (double x = start; x <= end; x += step) {
        double y = f(x);
        printf("%-15.6f %-20.10f\n", x, y);
    }
}

// Функция для поиска минимума и максимума на отрезке
void findMinMax(double start, double end, double step) {
    double min_val = INFINITY, max_val = -INFINITY;
    double min_x = 0, max_x = 0;
    bool found = false;

    for (double x = start; x <= end; x += step) {
        double y = f(x);
        if (!isnan(y)) {
            found = true;
            if (y < min_val) {
                min_val = y;
                min_x = x;
            }
            if (y > max_val) {
                max_val = y;
                max_x = x;
            }
        }
    }

    if (found) {
        printf("\n=== Экстремумы на отрезке [%.2f, %.2f] ===\n", start, end);
        printf("Минимум: f(%.6f) = %.10f\n", min_x, min_val);
        printf("Максимум: f(%.6f) = %.10f\n", max_x, max_val);
    }
    else {
        printf("Не удалось найти экстремумы на заданном отрезке\n");
    }
}

// Функция для поиска x: f(x) = Y методом перебора
void findX(double Y, double start, double end, double step, double tolerance) {
    printf("\n=== Поиск x: f(x) = %.6f ===\n", Y);
    printf("Допустимая погрешность: %.10f\n", tolerance);
    bool found = false;
    for (double x = start; x <= end; x += step) {
        double y = f(x);
        if (!isnan(y) && fabs(y - Y) < tolerance) {
            printf("Найдено: x = %.10f, f(x) = %.10f\n", x, y);
            found = true;
        }
    }
    if (!found) {
        printf("Решение не найдено на отрезке [%.2f, %.2f]\n", start, end);
    }
}

// Главное меню
void showMenu() {
    printf("\n=========== МЕНЮ ===========\n");
    printf("1. Вычислить значение функции в точке\n");
    printf("2. Построить таблицу значений на интервале\n");
    printf("3. Найти экстремумы на отрезке\n");
    printf("4. Найти х для заданного у\n");
    printf("5. Вычислить производную функции в точке\n");
    printf("0. Выход\n");
    printf("Выберите пункт: ");
}

int main() {
    setlocale(LC_CTYPE, "RUS");

    int choice;
    double x, start, end, step, Y, tolerance;
    double h;

    printf("=== Программа для работы с кусочно-заданной функцией ===\n");
    printf("Область определения: вся числовая прямая\n");
    printf("(x^2 - 4)/(x - 2) не определена при x=2 но она задана при x<1\n");
    printf("sec(x) - tan(x) не определена при x=П/2 но она задана 1 <= x < П/2\n");
    printf("Таким образом заданная функция определена на всей числовой прямой\n");




    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("\nВведите x: ");
            scanf("%lf", &x);
            double result = f(x);
            if (!isnan(result)) {
                printf("f(%.10f) = %.10f\n", x, result);
            }
            else {
                printf("Функция не определена в точке x=%.10f\n", x);
            }
            break;
        case 2:
            printf("\nВведите начало интервала: ");
            scanf("%lf", &start);
            printf("Введите конец интервала: ");
            scanf("%lf", &end);
            printf("Введите шаг: ");
            scanf("%lf", &step);
            tabulate(start, end, step);
            break;
        case 3:
            printf("\nВведите начало отрезка: ");
            scanf("%lf", &start);
            printf("Введите конец отрезка: ");
            scanf("%lf", &end);
            printf("Введите шаг поиска: ");
            scanf("%lf", &step);
            findMinMax(start, end, step);
            break;
        case 4:
            printf("\nВведите искомое значение Y: ");
            scanf("%lf", &Y);
            printf("Введите начало интервала поиска: ");
            scanf("%lf", &start);
            printf("Введите конец интервала поиска: ");
            scanf("%lf", &end);
            printf("Введите шаг поиска: ");
            scanf("%lf", &step);
            printf("Введите допустимую погрешность: ");
            scanf("%lf", &tolerance);
            findX(Y, start, end, step, tolerance);
            break;
        case 5:
            printf("\nВведите x для вычисления производной: ");
            scanf("%lf", &x);
            printf("Введите шаг h (рекомендуется 1e-6): ");
            scanf("%lf", &h);
            double deriv = derivative(x, h);
            if (!isnan(deriv)) {
                printf("f'(%.10f) = %.10f\n", x, deriv);
            }
            else {
                printf("Производная не может быть вычислена в точке x=%.10f\n", x);
            }
            break;
        case 0:
            printf("Завершение работы программы.\n");
            break;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}
