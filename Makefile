CC = gcc
CFLAGS = -Wall -Werror

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

APP_NAME = app
GEOMETRY_OBJ = $(OBJ_DIR)/geometry/Geometry.o
GEOMETRY_CALC_OBJ = $(OBJ_DIR)/libgeometry/geometry_calc.o

APP_DEPS = $(GEOMETRY_OBJ) $(GEOMETRY_CALC_OBJ)
APP_OBJ = $(BIN_DIR)/$(APP_NAME)

.PHONY: all clean

all: $(APP_OBJ)

$(APP_OBJ): $(APP_DEPS)
	$(CC) $(CFLAGS) -o $@ $^

$(GEOMETRY_OBJ): $(SRC_DIR)/geometry/Geometry.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(GEOMETRY_CALC_OBJ): $(SRC_DIR)/libgeometry/geometry_calc.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Используем include для автоматической генерации зависимостей из исходных файлов
-include $(OBJ_DIR)/geometry/Geometry.d $(OBJ_DIR)/libgeometry/geometry_calc.d

# Добавляем проверку наличия объектных файлов, чтобы избежать повторной компиляции, если изменений не было
$(APP_DEPS): | $(OBJ_DIR)/geometry $(OBJ_DIR)/libgeometry
