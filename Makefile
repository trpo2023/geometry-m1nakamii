all: app

app: Geometry obj/libgeometry/geometry_calc
	gcc -Wall -Werror -o bin/app obj/geometry/Geometry obj/libgeometry/geometry_calc

Geometry: src/geometry/Geometry.c
	gcc -Wall -Werror -c -o obj/geometry/Geometry src/geometry/Geometry.c

obj/libgeometry/geometry_calc: src/libgeometry/geometry_calc.c
	gcc -Wall -Werror -c -o obj/libgeometry/geometry_calc src/libgeometry/geometry_calc.c
