#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
#define BLUE "\e[1;34m"
#define CLOSE "\e[0m"

struct point {
    double x;
    double y;
};

struct circle {
    struct point center;
    double radius;
};

enum ERROR {
    ERROR_NAME,
    ERROR_BRACKET,
    ERROR_NUMBER,
    ERROR_UNEXPECT_TOKEN,
    ERROR_EXPECT_COMMA,
};

void show_error(int ERROR, int num, char* ch)
{
    for (int i = 0; i < num; i++) {
        putchar(' ');
    }
    printf("^\n");

    switch (ERROR) {
    case ERROR_NAME:
        printf("Error at column %d: expected %s'circle'%s\n", num, BLUE, CLOSE);
        break;
    case ERROR_BRACKET:
        if (*ch == ')') {
            printf("Error at column %d: expected %s'('%s\n", num, BLUE, CLOSE);
            break;
        } else {
            printf("Error at column %d: expected %s')'%s\n", num, BLUE, CLOSE);
            break;
        }
    case ERROR_NUMBER:
        printf("Error at column %d: expected %s'<double>'%s\n",
               num,
               BLUE,
               CLOSE);
        break;
    case ERROR_UNEXPECT_TOKEN:
        printf("Error at column %d: unexpected token\n", num);
        break;
    case ERROR_EXPECT_COMMA:
        printf("Error at column %d: expected %s','%s\n", num, BLUE, CLOSE);
        break;
    }
}

void to_lower(char* str, int num)
{
    for (int i = 0; i < num; i++) {
        str[i] = tolower(str[i]);
    }
}

double coordinat_x(char* arr, int* num)
{
    char exp[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == '(' || arr[*num] == ' ') {
            *num += 1;
        } else {
            if (arr[*num] == ')') {
                show_error(ERROR_BRACKET, *num, &arr[*num]);
                exit(EXIT_FAILURE);
            } else {
                show_error(ERROR_NUMBER, *num, NULL);
                exit(EXIT_FAILURE);
            }
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        exp[i] = arr[*num];
        i++;
        *num += 1;
    }
    if (arr[*num] != ' ') {
        show_error(ERROR_UNEXPECT_TOKEN, *num, NULL);
        exit(EXIT_FAILURE);
    }
    char* trash;
    return strtod(exp, &trash);
}

double coordinat_y(char* arr, int* num)
{
    char exp[20];
    int i = 0;

    while (!isdigit(arr[*num]) && arr[*num] != '-') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            show_error(ERROR_NUMBER, *num, NULL);
            exit(EXIT_FAILURE);
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '-' || arr[*num] == '.') {
        exp[i] = arr[*num];
        i++;
        *num += 1;
    }

    while (arr[*num] != ',') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            show_error(ERROR_EXPECT_COMMA, *num, NULL);
            exit(EXIT_FAILURE);
        }
    }
    char* trash;
    return strtod(exp, &trash);
}

double radius_search(char* arr, int* num)
{
    char exp[20];
    int i = 0;

    while (!isdigit(arr[*num])) {
        if (arr[*num] == ' ' || arr[*num] == ',') {
            *num += 1;
        } else {
            show_error(ERROR_NUMBER, *num, NULL);
            exit(EXIT_FAILURE);
        }
    }

    while (isdigit(arr[*num]) || arr[*num] == '.') {
        exp[i] = arr[*num];
        i++;
        *num += 1;
    }

    while (arr[*num] != ')') {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            if (arr[*num] == '(') {
                show_error(ERROR_BRACKET, *num, &arr[*num]);
                exit(EXIT_FAILURE);
            } else {
                show_error(ERROR_UNEXPECT_TOKEN, *num, NULL);
                exit(EXIT_FAILURE);
            }
        }
    }
    char* trash;
    return strtod(exp, &trash);
}

void is_end_empty(char* arr, int* num)
{
    *num += 1;
    while (arr[*num] != '\n' && arr[*num] != EOF) {
        if (arr[*num] == ' ') {
            *num += 1;
        } else {
            show_error(ERROR_UNEXPECT_TOKEN, *num, NULL);
            exit(EXIT_FAILURE);
        }
    }
}

struct point center_search(char* arr, int* num)
{
    struct point Center;

    Center.x = coordinat_x(arr, num);
    Center.y = coordinat_y(arr, num);

    return Center;
}

struct circle circle_search(struct point* Center, char* arr, int* num)
{
    struct circle Circle;

    Circle.center.x = Center->x;
    Circle.center.y = Center->y;
    Circle.radius = radius_search(arr, num);

    return Circle;
}

void show_circle(struct circle* Circle)
{
    printf("\ncircle(%.2f %.2f, %.2f)\n",
           Circle->center.x,
           Circle->center.y,
           Circle->radius);
}

int main()
{
    char enter[SIZE], figure[SIZE];
    int num = 0;

    printf("Enter a geometric figure (or press Enter for exit):\n");
    fgets(enter, SIZE, stdin);

    for (int i = 0; i < strlen(enter); i++) {
        if (enter[i] == '(' || enter[i] == ' ') {
            to_lower(figure, num);
            if (strcmp(figure, "circle") == 0) {
                struct point Center = center_search(enter, &num);
                struct circle Circle = circle_search(&Center, enter, &num);
                is_end_empty(enter, &num);
                show_circle(&Circle);
                break;
            } else {
                show_error(ERROR_NAME, 0, NULL);
                exit(EXIT_FAILURE);
            }
        } else if (enter[i] == ')') {
            show_error(ERROR_BRACKET, num, &enter[i]);
            exit(EXIT_FAILURE);
        }

        figure[num] = enter[i];
        num++;
    }

    return 0;
}