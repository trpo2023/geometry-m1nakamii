#include <libgeometry/geometry_calc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_CIRCLES 100

void get_input(char* input, int max_len)
{
    printf("Enter the circle parameters in format circle(x y,r): ");
    fgets(input, max_len, stdin);
}

// Функция, проверяющая пересечение двух кругов
bool check_collision(struct Circle circle1, struct Circle circle2)
{
    float distance = sqrt(
            pow((circle1.x - circle2.x), 2) + pow((circle1.y - circle2.y), 2));
    return distance <= circle1.r + circle2.r;
}

int main(int argc, const char** argv)
{
    int number_of_circles;
    printf("How many circles do you want to input? ");
    scanf("%d", &number_of_circles);
    getchar();
    if (number_of_circles <= 0) {
        printf("Error: the number of circles must be a positive "
               "integer\n");
        return 1;
    }

    // Инициализируем массив структур для хранения информации о кругах
    struct Circle circles[MAX_CIRCLES];

    char input[MAX_CIRCLES][MAX_LEN];

    // Цикл получения входных данных
    for (int i = 0; i < number_of_circles; i++) {
        get_input(input[i], MAX_LEN);
    }

    int parse_result = parser(number_of_circles, input, circles);
    if (parse_result != 0) {
        return 1;
    }

    for (int i = 0; i < number_of_circles; i++) {
        float s_circle = circle_area(circles[i].r);
        printf("\nCircle %d area: %f\n", i + 1, s_circle);

        float p_circle = circle_perimeter(circles[i].r);
        printf("Circle %d perimeter: %f\n", i + 1, p_circle);
    }

    // Проверяем пересечения всех пар кругов и выводим сообщения об этом
    for (int i = 0; i < number_of_circles - 1; i++) {
        for (int j = i + 1; j < number_of_circles; j++) {
            if (check_collision(circles[i], circles[j])) {
                printf("Circle %d and Circle %d intersect\n", i + 1, j + 1);
            } else {
                printf("Circle %d and Circle %d do not intersect\n",
                       i + 1,
                       j + 1);
            }
        }
    }

    return 0;
}