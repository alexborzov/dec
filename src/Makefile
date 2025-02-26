# __GCC__
CC = gcc

# __CFLAGS__
# -lcheck -lpthread -lrt -lm -lsubunit
# gcc -Wall -Wextra -Werror -Wuninitialized -pedantic -std=c11 -DVALGRIND \
# ./__TESTS__/main_suite.o s21_decimal.a -o __TESTS__/main_suite \
# -lcheck -lpthread -lrt -lm -lsubunit


CFLAGS = -Wall -Wextra -Werror -Wuninitialized -Wmaybe-uninitialized -pedantic -std=c11
CFLAGS_T = -Wall -Wextra -Werror -Wuninitialized -Wmaybe-uninitialized -pedantic -std=c11 -fprofile-arcs -ftest-coverage

# __GCOVFLAGS__
ifeq ($(shell uname), Darwin)
    GCOVFLAGS = -lcheck -fprofile-arcs -ftest-coverage
else
    GCOVFLAGS = -lcheck -lsubunit -fprofile-arcs -ftest-coverage
endif

# __RM__
RM = rm -rf

# __LIBRARY_FILE__
LIBRARY = s21_decimal.a

# __FOLDERS__
# __MAIN_FOLDERS__
ARITHMETIC_DIR = arithmetic
COMPARISON_DIR = comparison
CONVERTORS_DIR = convertors
OTHER_DIR = other
# __TESTS_FOLDERS__
TEST_DIR = __TESTS__
# __HELPERS_FOLDERS__
HELPERS_DIR = helpers
# __HEADERS_FOLDERS__
HEADERS_DIR = __HEADERS__

# __ALL_SRC__
ALL_SRC = $(wildcard *.c */*.c */*/*.c *.h */*.h */*/*.h)

# __HEADERS__
HEADERS = s21_decimal.h $(wildcard ./__HEADERS__/*.h)

# __TESTS__
SOURCES_TESTS = $(wildcard ./__TESTS__/*.c)         		\
								$(wildcard ./__TESTS__/arithmetic/*.c) 	\
								$(wildcard ./__TESTS__/comparison/*.c) 	\
								$(wildcard ./__TESTS__/convertors/*.c) 	\
								$(wildcard ./__TESTS__/other/*.c) 			\

# __CORE__
SOURCES_ALL = $(wildcard ./arithmetic/*.c)  \
							$(wildcard ./comparison/*.c)  \
							$(wildcard ./convertors/*.c)  \
							$(wildcard ./other/*.c)  			\
							$(wildcard ./helpers/*.c)  		\

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES_ALL))
TEST_SOURCES = $(wildcard ./__TESTS__/*.c)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)
TEST_EXECUTABLES = $(TEST_SOURCES:.c=)

# __ALL__
all: ${LIBRARY} test # gcov_report

%.o: %.c $(HEADER)
	${CC} $(CFLAGS) -c $< -o $@

$(TEST_EXECUTABLES): $(TEST_OBJECTS) $(LIBRARY)
	${CC} ${CFLAGS} $(TEST_OBJECTS) $(LIBRARY) -o $@ -lcheck -lpthread -lrt -lm -lsubunit

# __LIBRARY__S21_DECIMAL.A__
${LIBRARY}: $(OBJ_LIBRARY) ${HEADERS}
	ar rcs $(LIBRARY) ${OBJ_LIBRARY}
	ranlib $(LIBRARY)
	# ${RM} ./*/*.o

# __TEST__
test: ${LIBRARY} ${TEST_SOURCES}
	$(CC) $(CFLAGS_T) ${TEST_DIR}/main_suite.c ${LIBRARY} -o ${TEST_DIR}/tests.out -lm -lcheck
	ar rcs libs21_decimal_test.a ${OBJ_LIBRARY}
	gcc $(CFLAGS) ${TEST_DIR}/main_suite.c -o ${TEST_DIR}/tests.out $(GCOVFLAGS) -lm -L. -ls21_decimal_test
	./${TEST_DIR}/tests.out || true

# __GCOV_REPORT__
gcov_report: test
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	$(RM) *.gcno *.gcda *.info *.out *.gcov

# __FORMAT__
format:
	cp ./../materials/linters/.clang-format ./
	clang-format -i $(ALL_SRC)

# __CHECK__
check:
	cp ./../materials/linters/.clang-format ./
	clang-format -n $(ALL_SRC)

# valgrind --track-origins=yes ./unit_test floor
# valgrind --track-origins=yes ./unit_test floor
# __LINT__
# lint: CFLAGS += -DVALGRIND # GCOVFLAGS
# lint: clean $(LIBRARY) $(TEST_EXECUTABLES)
# 	for test in $(TEST_EXECUTABLES); do CK_FORK=no valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$$test; done

lint: CFLAGS += -DVALGRIND # GCOVFLAGS
lint: clean $(LIBRARY) $(TEST_EXECUTABLES)
	for test in $(TEST_EXECUTABLES); do \
        CK_FORK=no valgrind \
        --tool=memcheck \
        --leak-check=full \
        --track-origins=yes \
        --show-leak-kinds=all \
        --error-exitcode=1 \
        ./$$test; \
    done

# --log-file=valgrind-$$test.log

# __CPPCHECK__
cppcheck:
	cppcheck --enable=all --check-level=exhaustive --suppress=missingIncludeSystem $(ALL_SRC)

# __REBUILD__
rebuild: clean all

# __CLEAN__
clean:
	$(RM) $(LIBRARY)
	$(RM) $(ARITHMETIC_DIR)/*.gcno $(ARITHMETIC_DIR)/*.gcda $(ARITHMETIC_DIR)/*.out $(ARITHMETIC_DIR)/*.o $(ARITHMETIC_DIR)/**/*.gcno $(ARITHMETIC_DIR)/**/*.gcda $(ARITHMETIC_DIR)/**/*.out $(ARITHMETIC_DIR)/**/*.o
	$(RM) $(COMPARISON_DIR)/*.gcno $(COMPARISON_DIR)/*.gcda $(COMPARISON_DIR)/*.out $(COMPARISON_DIR)/*.o $(COMPARISON_DIR)/**/*.gcno $(COMPARISON_DIR)/**/*.gcda $(COMPARISON_DIR)/**/*.out $(COMPARISON_DIR)/**/*.o
	$(RM) $(CONVERTORS_DIR)/*.gcno $(CONVERTORS_DIR)/*.gcda $(CONVERTORS_DIR)/*.out $(CONVERTORS_DIR)/*.o $(CONVERTORS_DIR)/**/*.gcno $(CONVERTORS_DIR)/**/*.gcda $(CONVERTORS_DIR)/**/*.out $(CONVERTORS_DIR)/**/*.o
	$(RM) $(HELPERS_DIR)/*.gcno $(HELPERS_DIR)/*.gcda $(HELPERS_DIR)/*.out $(HELPERS_DIR)/*.o $(HELPERS_DIR)/**/*.gcno $(HELPERS_DIR)/**/*.gcda $(HELPERS_DIR)/**/*.out $(HELPERS_DIR)/**/*.o
	$(RM) $(OTHER_DIR)/*.gcno $(OTHER_DIR)/*.gcda $(OTHER_DIR)/*.out $(OTHER_DIR)/*.o $(OTHER_DIR)/**/*.gcno $(OTHER_DIR)/**/*.gcda $(OTHER_DIR)/**/*.out $(OTHER_DIR)/**/*.o
	$(RM) $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcda $(TEST_DIR)/*.out $(TEST_DIR)/*.o $(TEST_DIR)/**/*.gcno $(TEST_DIR)/**/*.gcda $(TEST_DIR)/**/*.out $(TEST_DIR)/**/*.o $(TEST_DIR)/main_suite
	$(RM) ./*.gcno ./*.gcda ./*.out ./*.o ./**/*.gcno ./**/*.gcda ./**/*.out ./**/*.o ./*.a
	$(RM) ./coverage_report
	$(RM) .clang-format

# __PHONY__
.PHONY: all test gcov_report format check lint cppcheck rebuild clean
