.PHONY: tests all docs
tests:
	gcc -o array_test tests/array_tests.c 
	gcc -o objectpool_test tests/objectpool_tests.c 
	./tests/array_test
	./tests/objectpool_test
	rm array_test
	rm objectpool_test
docs:
	doxygen
install: 
	cp list.h /usr/local/include
	cp objectpool.h /usr/local/include
remove:
	rm /usr/local/include/list.h
	rm /usr/local/include/objectpool.h
