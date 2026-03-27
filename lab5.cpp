#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

// ---------- Вспомогательные функции ----------

// Очистка буфера ввода после scanf
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------- Задание 1: просмотр файла ----------
void view_file() {
    char filename[100];
    FILE *f;
    int ch;

    printf("Введите имя файла для просмотра: ");
    scanf("%s", filename);
    clear_input();

    f = fopen(filename, "r");
    if (f == NULL) {
        printf("Ошибка: файл %s не открыт\n", filename);
        return;
    }

    printf("\n--- Содержимое файла %s ---\n", filename);
    while ((ch = fgetc(f)) != EOF) {
        putchar(ch);
    }
    fclose(f);
    printf("\n--- Конец файла ---\n");
}

// ---------- Задание 2: подсчёт пустых и непустых символов ----------
void count_chars() {
    char filename[100];
    FILE *f;
    int ch;
    int empty = 0, non_empty = 0;

    printf("Введите имя файла для анализа: ");
    scanf("%s", filename);
    clear_input();

    f = fopen(filename, "r");
    if (f == NULL) {
        printf("Ошибка: файл %s не открыт\n", filename);
        return;
    }

    printf("\n--- Статистика файла %s ---\n", filename);
    while ((ch = fgetc(f)) != EOF) {
        // Пустыми считаем: пробел, табуляцию, перевод строки, возврат каретки,
        // все управляющие символы (коды < 32) и символ DEL (127)
        if (isspace(ch) || (ch < 32 && ch != '\n' && ch != '\t') || ch == 127)
            empty++;
        else
            non_empty++;
    }
    fclose(f);

    printf("Пустых символов: %d\n", empty);
    printf("Непустых символов: %d\n", non_empty);
}

// ---------- Задание 3: поиск подстроки с записью в файл ----------
void search_substring() {
    char filename[100], substring[100], result_filename[100];
    FILE *in, *out;
    char line[MAX_LINE];
    int line_num = 0, found = 0;

    printf("Введите имя файла для поиска: ");
    scanf("%s", filename);
    printf("Введите искомую подстроку: ");
    scanf("%s", substring);
    printf("Введите имя файла для записи результатов: ");
    scanf("%s", result_filename);
    clear_input();

    in = fopen(filename, "r");
    if (in == NULL) {
        printf("Ошибка: файл %s не открыт\n", filename);
        return;
    }

    out = fopen(result_filename, "w");
    if (out == NULL) {
        printf("Ошибка: не удалось создать файл %s\n", result_filename);
        fclose(in);
        return;
    }

    fprintf(out, "Результаты поиска подстроки \"%s\" в файле %s:\n\n", substring, filename);

    while (fgets(line, MAX_LINE, in) != NULL) {
        line_num++;
        if (strstr(line, substring) != NULL) {
            found++;
            fprintf(out, "Строка %d: %s", line_num, line);
        }
    }

    if (found == 0)
        fprintf(out, "Подстрока не найдена.\n");
    else
        fprintf(out, "\nВсего найдено вхождений: %d\n", found);

    fclose(in);
    fclose(out);
    printf("Поиск завершён. Результаты записаны в файл %s\n", result_filename);
}

// ---------- Главное меню ----------
int main() {
    int choice;

    do {
        printf("\n========== Лабораторная работа #4 ==========\n");
        printf("1. Просмотр текстового файла\n");
        printf("2. Подсчёт пустых и непустых символов\n");
        printf("3. Поиск подстроки в файле\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        clear_input();

        switch (choice) {
            case 1: view_file(); break;
            case 2: count_chars(); break;
            case 3: search_substring(); break;
            case 0: printf("Выход из программы.\n"); break;
            default: printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);

    return 0;
}