#include <libgeometry/geometry_calc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_CIRCLES 100

struct Circle {
    float x;
    float y;
    float r;
};

// Функция, проверяющая пересечение двух кругов
bool check_collision(struct Circle circle1, struct Circle circle2)
{
    float distance = sqrt(
            pow((circle1.x - circle2.x), 2) + pow((circle1.y - circle2.y), 2));
    return distance <= circle1.r + circle2.r;
}

int main()
{
    char input[MAX_LEN];
    int number_of_circles;
    printf("How many circles do you want to input? ");
    scanf("%d", &number_of_circles);
    getchar();
    if (number_of_circles <= 0) {
        printf("Error: the number of circles must be a positive integer\n");
        return 0;
    }

    // Инициализируем массив структур для хранения информации о кругах
    struct Circle circles[MAX_CIRCLES];
    int current_circle = 0;

    for (int i = 1; i <= number_of_circles; i++) {
        printf("Enter the circle parameters in format circle(x y,r): ");
        fgets(input, MAX_LEN, stdin);

        float c_x, c_y, c_r;

        if (strncmp(input, "circle(", 7) != 0) {
            printf("Error: Input string must start with 'circle'\n");
            return 0;
        }

        if (sscanf(input, "circle(%f %f,%f)", &c_x, &c_y, &c_r) != 3) {
            printf("\nError: incorrect input format. Please enter the circle "
                   "parameters in format circle(x y,r).\n");
            return 0;
        }

        // Сохраняем информацию о круге в массив структур
        circles[current_circle].x = c_x;
        circles[current_circle].y = c_y;
        circles[current_circle].r = c_r;
        current_circle++;

        float s_circle = circle_area(c_r);
        printf("\narea: %f\n", s_circle);

        float p_circle = circle_perimeter(c_r);
        printf("\nperimeter: %f\n", p_circle);
    }

    // Проверяем пересечения всех пар кругов и выводим сообщения об этом
    for (int i = 0; i < current_circle - 1; i++) {
        for (int j = i + 1; j < current_circle; j++) {
            if (check_collision(circles[i], circles[j])) {
                printf("Circle %d and Circle %d intersect\n", i + 1, j + 1);
            } else
                printf("Circle %d and Circle %d not intersect\n", i + 1, j + 1);
        }
    }

    return 0;
}
