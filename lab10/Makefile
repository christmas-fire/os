CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread
ATOMIC_FLAGS = -latomic

TARGETS = peterson_classic peterson_atomic lockfree_examples

all: $(TARGETS)

peterson_classic: peterson_classic.c
	$(CC) $(CFLAGS) -o $@ $<

peterson_atomic: peterson_atomic.c
	$(CC) $(CFLAGS) $(ATOMIC_FLAGS) -o $@ $<

lockfree_examples: lockfree_examples.c
	$(CC) $(CFLAGS) $(ATOMIC_FLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

test: all
	@echo "=== Тест классического алгоритма Петерсона ==="
	./peterson_classic
	@echo ""
	@echo "=== Тест алгоритма Петерсона с атомарными операциями ==="
	./peterson_atomic
	@echo ""
	@echo "=== Тест lock-free структур данных ==="
	./lockfree_examples

.PHONY: all clean test
