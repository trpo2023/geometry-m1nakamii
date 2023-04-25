#pragma once
#define MAX_LEN 100
#define MAX_CIRCLES 100
#define pi 3.14159265359f

struct Circle {
    float x;
    float y;
    float r;
    char name;
};

float circle_area(float r);

float circle_perimeter(float r);

int parser(
        int number_of_circles, char input[][MAX_LEN], struct Circle* circles);