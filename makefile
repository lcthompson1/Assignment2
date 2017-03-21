SOBJS = integer.o sll.o test-sll.o
DOBJS = integer.o dll.o test-dll.o
STOBJS = integer.o stack.o test-stack.o dll.o
QOBJS = integer.o queue.o test-queue.o sll.o
OBJS = sll.o dll.o stack.o queue.o sqsort.o integer.o real.o scanner.o comparator.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g

all : bstrees

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o: real.c real.h
	gcc $(OOPTS) real.c

scanner.o: scanner.c scanner.h
	gcc $(OOPTS) scanner.c

comparator.o: comparator.c comparator.h
	gcc $(OOPTS) comparator.c

bst.o: bst.h bst.c
	gcc -Wall -Wextra -g -c -std=c99 bst.c

bstrees.o: bstrees.c
	gcc -Wall -Wextra -g -c -std=c99 bstrees.c

bstrees: bstrees.o bst.o integer.o scanner.o
	gcc -Wall -Wextra -g -o bstrees -g bstrees.o bst.o integer.o scanner.o


clean :
	rm -f $(SOBJS) $(DOBJS) $(STOBJS) $(QOBJS) $(OBJS) bstrees bst.o bstrees.o

test :
