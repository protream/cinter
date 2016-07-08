.PHONY: test test-stack

test:
	@make test-stack

test-stack:
	@cc -o test.out src/stack.h src/stack.c
	@./test.out
	@rm test.out
