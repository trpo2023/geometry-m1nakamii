#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100

int main()
{
    char input[MAX_LEN];
    printf("Enter the circle parameters in format circle(x y,r):");
    fgets(input, MAX_LEN, stdin);

    float x, y, r;
    if (strncmp(input, "circle(", 7) != 0) {
        printf("Error: Input string must start with 'circle'\n");
        return 0;
    }

    if (sscanf(input, "circle(%f %f,%f)", &x, &y, &r) != 3) {
        printf("\nError: incorrect input format. Please enter the circle "
               "parameters in format circle(x y,r).\n");
        return 0;
    }
    printf("circle(%.2f %.2f,%.2f)", x, y, r);
    return 0;
}
