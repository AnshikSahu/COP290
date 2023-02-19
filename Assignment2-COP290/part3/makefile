list:
	arch -x86_64 gcc -o obj/list_test test/list_test.c src/list.c -I include/
	./obj/list_test  
hashmap:
	arch -x86_64 gcc -o obj/hashmap_test test/hashmap_test.c src/list.c src/mythread.c src/hm.c  -I include/
	./obj/hashmap_test
doc:
	doxygen Doxyfile
clean:
	rm -f obj/*
	rm -fr doc/*
test:
	gcc -g3 -o obj/main.o test/main_pthreads.c src/list.c src/hm.c src/mythread.c -I include/ -pthread
	./obj/main.o data/in1.txt data/in2.txt data/in3.txt data/in4.txt

.PHONY: all test clean
