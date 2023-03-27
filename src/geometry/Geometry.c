#include "../libgeometry/geometry_calc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

int main()
{
    char input[MAX_LEN];
    printf("Enter the circle parameters in format circle(x y,r):");
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

    float s_circle = circle_area(c_r);
    printf("\narea: %f\n", s_circle);

    float p_circle = circle_perimeter(c_r);
    printf("\nperimeter: %f\n", p_circle);
}
