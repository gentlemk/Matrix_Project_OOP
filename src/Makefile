CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++20
TESTFLAGS := -lgtest -pthread

BIN_FILE := s21_matrix_oop
STATIC_LIB := $(BIN_FILE).a
TEST_BIN := testing

SRC_DIR := .
TEST_DIR := gtests

OBJ_DIR := obj
TOBJ_DIR := t_obj

# Каталог для отчёта и всех файлов покрытия
REPORT_DIR := report
COV_OBJ_DIR := $(REPORT_DIR)/coverage_obj
GCOV_BIN := $(REPORT_DIR)/testing_coverage
COVERAGE_INFO := $(REPORT_DIR)/coverage.info
HTML_REPORT_DIR := $(REPORT_DIR)/html

SRC_FILES := $(wildcard *.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ_TEST_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(TOBJ_DIR)/%.o,$(TEST_FILES))

# Объектные файлы для сборки с покрытием
COV_SRC_OBJ_FILES := $(patsubst %.cpp,$(COV_OBJ_DIR)/%.o,$(SRC_FILES))
COV_TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp,$(COV_OBJ_DIR)/$(TEST_DIR)/%.o,$(TEST_FILES))
COV_OBJ_FILES := $(COV_SRC_OBJ_FILES) $(COV_TEST_OBJ_FILES)

.PHONY: all test clean rebuild valgrind gcov_report style fix-style

all: $(STATIC_LIB) test

# Сборка статической библиотеки
$(STATIC_LIB): $(OBJ_FILES)
	ar rcs $@ $^
	ranlib $@

# Компиляция исходников библиотеки
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция тестов
$(TOBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TOBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(TOBJ_DIR):
	mkdir -p $@

# Сборка исполняемого файла тестов
$(TEST_BIN): $(OBJ_TEST_FILES) $(STATIC_LIB)
	$(CXX) $(OBJ_TEST_FILES) $(STATIC_LIB) -o $@ $(TESTFLAGS)

test: $(TEST_BIN)
	./$(TEST_BIN)

# Полная пересборка
rebuild:
	$(MAKE) clean
	$(MAKE) all

# Проверка памяти
valgrind: $(TEST_BIN)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=1 ./$(TEST_BIN)

# Компиляция исходников с покрытием
$(COV_OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) --coverage -c $< -o $@

# Сборка тестов с покрытием
$(GCOV_BIN): $(COV_OBJ_FILES)
	mkdir -p $(REPORT_DIR)
	$(CXX) --coverage $^ -o $@ $(TESTFLAGS)

# Генерация отчёта о покрытии
gcov_report:
	rm -rf $(REPORT_DIR)
	mkdir -p $(REPORT_DIR)
	$(MAKE) $(GCOV_BIN)
	./$(GCOV_BIN)
	lcov --capture --directory . --output-file $(COVERAGE_INFO) --ignore-errors mismatch --quiet
	lcov --remove $(COVERAGE_INFO) '/usr/*' -o $(COVERAGE_INFO)

	genhtml $(COVERAGE_INFO) --output-directory $(HTML_REPORT_DIR) --quiet
	@echo "Отчёт создан: $(HTML_REPORT_DIR)/index.html"

# Проверка форматирования
style:
	clang-format -style=Google -n $(SRC_FILES) $(TEST_FILES) *.hpp $(TEST_DIR)/*.hpp

# Исправление форматирования
fix-style:
	clang-format -style=Google -i $(SRC_FILES) $(TEST_FILES) *.hpp $(TEST_DIR)/*.hpp

# Очистка результатов сборки
clean:
	rm -rf $(OBJ_DIR) $(TOBJ_DIR) $(STATIC_LIB) 
		$(TEST_BIN) $(REPORT_DIR) 
		coverage.info *.gcda *.gcno *.gcov