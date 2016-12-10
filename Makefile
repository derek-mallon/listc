.PHONY: tests all docs
tests:
	gcc -o tests/array_test tests/array_tests.c 
	gcc -o tests/objectpool_test tests/objectpool_tests.c 
	./tests/array_test
	./tests/objectpool_test
docs:
	doxygen
install: 
	cp list.h /usr/local/include
remove:
	rm /usr/local/include/list.h
