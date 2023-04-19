CC = gcc
CFLAGS = -Wall -Werror -I src -MP -MMD

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

APP_NAME = app

GEOMETRY_OBJ = $(OBJ_DIR)/geometry/Geometry.o
GEOMETRY_CALC_A = $(OBJ_DIR)/libgeometry/geometry_calc.a
GEOMETRY_CALC_OBJ = $(OBJ_DIR)/libgeometry/geometry_calc.o

APP_DEPS = $(GEOMETRY_OBJ) $(GEOMETRY_CALC_A)
APP_OBJ = $(BIN_DIR)/$(APP_NAME)

TEST_MAIN_FILE = test/main.c
TEST_DEPS = $(GEOMETRY_CALC_OBJ) $(OBJ_DIR)/parser_test.o
TEST_OBJ = $(BIN_DIR)/test_app

#Сборка приложения

all: $(APP_OBJ)

$(APP_OBJ): $(APP_DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(GEOMETRY_OBJ): $(SRC_DIR)/geometry/Geometry.c | $(OBJ_DIR)/geometry
	$(CC) $(CFLAGS) -c -o $@ $<

$(GEOMETRY_CALC_A): $(GEOMETRY_CALC_OBJ) $(TEST_OBJ) | $(OBJ_DIR)/libgeometry
	ar rcs $@ $<
$(GEOMETRY_CALC_OBJ): $(SRC_DIR)/libgeometry/geometry_calc.c | $(OBJ_DIR)/libgeometry
	$(CC) $(CFLAGS) -c -o $@ $<

#Тестирование приложения

test: $(TEST_OBJ) $(GEOMETRY_CALC_A)
	$(TEST_OBJ)

$(TEST_OBJ): $(TEST_DEPS) $(TEST_MAIN_FILE)
	mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/parser_test.o: test/parser_test.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

#Создание папок obj

$(OBJ_DIR)/geometry:
	mkdir -p $@

$(OBJ_DIR)/libgeometry:
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

# make clean

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)