#include <libgeometry/geometry_calc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
#define MAX_CIRCLES 100
float circle_area(float r)
{
    if (r <= 0) {
        return 0;
    }
    return pi * r * r;
}

float circle_perimeter(float r)
{
    if (r <= 0) {
        return 0;
    }
    return 2 * pi * r;
}

int parser(int number_of_circles, char input[][MAX_LEN], struct Circle* circles)
{
    for (int i = 0; i < number_of_circles; i++) {
        // проверяем, что ввод начинается с "circle("
        if (strncmp(input[i], "circle(", 7) != 0) {
            printf("Error: Input string must start with 'circle('\n");
            return 1;
        }

        // считываем координаты центра круга
        char* p1 = input[i] + 7;
        char* p2 = strchr(p1, ' ');
        if (!p2) {
            printf("Error: Missing ' ' after x coordinate in input string\n");
            return 1;
        }
        *p2++ = '\0'; // заменяем ' ' на '\0', чтобы завершить строку
        float c_x = atof(p1);

        p1 = p2;
        p2 = strchr(p1, ',');
        if (!p2) {
            printf("Error: Missing ', ' after x coordinate in input string\n");
            return 1;
        }
        *p2++ = '\0';
        float c_y = atof(p1);

        // считываем радиус круга
        p1 = p2;
        p2 = strchr(p1, ')');
        if (!p2) {
            printf("Error: Missing ')' after radius in input string\n");
            return 1;
        }
        *p2 = '\0';
        float c_r = atof(p1);

        // сохраняем информацию о круге в массив структур
        circles[i].x = c_x;
        circles[i].y = c_y;
        circles[i].r = c_r;
    }

    return 0;
}