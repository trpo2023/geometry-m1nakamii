#include <../thirdparty/ctest.h>
#include <libgeometry/geometry_calc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

CTEST(circle_area, correct_input)
{
    const float radius = 5.0;
    const float expected_area = 78.539816;

    const float result = circle_area(radius);

    ASSERT_DBL_NEAR(expected_area, result);
}

CTEST(circle_area, negative_radius)
{
    const float radius = -5.0;
    const float expected_area = 0.0;

    const float result = circle_area(radius);

    ASSERT_DBL_NEAR(expected_area, result);
}

CTEST(circle_perimeter, correct_input)
{
    const float radius = 5.0;
    const float expected_perimeter = 31.415927;

    const float result = circle_perimeter(radius);

    ASSERT_DBL_NEAR(expected_perimeter, result);
}

CTEST(circle_perimeter, negative_radius)
{
    const float radius = -5.0;
    const float expected_perimeter = 0.0;

    const float result = circle_perimeter(radius);

    ASSERT_DBL_NEAR(expected_perimeter, result);
}

CTEST(input_test, correct_input)
{
    char input[MAX_LEN];
    strcpy(input, "circle(0 0,1.5)");
    float c_x, c_y, c_r;

    ASSERT_EQUAL(3, sscanf(input, "circle(%f %f,%f)", &c_x, &c_y, &c_r));
    ASSERT_EQUAL(0, strncmp(input, "circle(", 7));
    ASSERT_EQUAL(0.0, c_x);
    ASSERT_EQUAL(0.0, c_y);
    ASSERT_EQUAL(1.5, c_r);
}

CTEST(input_test, incorrect_input)
{
    char input[MAX_LEN];
    strcpy(input, "square(0 0,1.5)");
    float c_x, c_y, c_r;

    ASSERT_EQUAL(2, sscanf(input, "circle(%f %f,%f)", &c_x, &c_y, &c_r));
    ASSERT_NOT_EQUAL(0, strncmp(input, "circle(", 7));
}