.PHONY: clean run all test test_app app

clean:
	rm -f *.out app test
run: app
	./app 2 0
all: test_app app
test: all test_plan.txt
	./test test_plan.txt
test_app: test.c
	gcc test.c -o test
app: main.c
	gcc main.c -o app

