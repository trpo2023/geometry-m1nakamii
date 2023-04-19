#include <libgeometry/geometry_calc.h>

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
