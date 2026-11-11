CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Wpedantic -Iinclude
CXXFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
OBJ_DIR = build

SRC_FILES = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
MAIN_OBJ = $(OBJ_DIR)/main.o

TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRC))

APP_EXEC = app.out
TEST_EXEC = test.out

all: $(APP_EXEC)

$(APP_EXEC): $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_EXEC): $(OBJ_FILES) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(APP_EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -rf $(OBJ_DIR) $(APP_EXEC) $(TEST_EXEC)