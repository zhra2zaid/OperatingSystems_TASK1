.PHONY: all
all: task0 task1 task2 task3 task4 

task0:  friendschild.c  
	gcc -o friends friendschild.c

task1:  main2_1.c
	gcc -o process1 main2_1.c

task2:  main2_2.c
	gcc -o process2 main2_2.c 

task3:  main2_3.c
	gcc -o process3 main2_3.c 

task4:  main2_4.c
	gcc -o together main2_4.c

.PHONY: clean
clean: 
	-rm process1 process2 process3  2>/dev/null
