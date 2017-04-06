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

sll.o: sll.h sll.c
	gcc -Wall -Wextra -g -c -std=c99 sll.c

queue.o: queue.h queue.c
	gcc -Wall -Wextra -g -c -std=c99 queue.c

bstrees.o: bstrees.c
	gcc -Wall -Wextra -g -c -std=c99 bstrees.c

rbt.o: rbt.h rbt.c
	gcc -Wall -Wextra -g -c -std=c99 rbt.c

vbst.o: vbst.h vbst.c
	gcc -Wall -Wextra -g -c -std=c99 vbst.c

bstrees: bstrees.o bst.o integer.o scanner.o queue.o sll.o rbt.o vbst.o
	gcc -Wall -Wextra -g -o bstrees -g bstrees.o bst.o integer.o scanner.o queue.o sll.o rbt.o vbst.o


clean :
	rm -f $(SOBJS) $(DOBJS) $(STOBJS) $(QOBJS) $(OBJS) bstrees bst.o bstrees.o

test :
	./bstrees -v sampleCorpus1.txt sampleCommands1.txt myOutput1.txt
	./bstrees -v sampleCorpus2.txt sampleCommands2.txt myOutput2.txt
	./bstrees -v sampleCorpus3.txt sampleCommands3.txt myOutput3.txt
	./bstrees -v sampleCorpus4.txt sampleCommands4.txt myOutput4.txt
	./bstrees -v sampleCorpus4.txt sampleCommands5.txt myOutput9.txt
	./bstrees -r sampleCorpus1.txt sampleCommands1.txt myOutput5.txt
	./bstrees -r sampleCorpus2.txt sampleCommands2.txt myOutput6.txt
	./bstrees -r sampleCorpus4.txt sampleCommands4.txt myOutput8.txt
	./bstrees -v corpus0.txt commands0.txt myExtraOutput1.txt
	./bstrees -r corpus0.txt commands0.txt myExtraOutput2.txt
	./bstrees -v corpus1.txt commands1.txt myExtraOutput3.txt
	./bstrees -r corpus1.txt commands2.txt myExtraOutput4.txt
	./bstrees -v corpus2.txt commands3.txt myExtraOutput5.txt
	./bstrees -r corpus2.txt commands4.txt myExtraOutput6.txt
	./bstrees -v corpus3.txt commands5.txt myExtraOutput7.txt
	./bstrees -r corpus3.txt commands5.txt myExtraOutput8.txt
	diff myOutput1.txt out1.txt
	diff myOutput3.txt out3.txt
	diff myOutput4.txt out4.txt
	diff myOutput5.txt out5.txt
	diff myOutput6.txt out6.txt
	diff myOutput8.txt out8.txt
	diff myExtraOutput1.txt output1.txt
	diff myExtraOutput2.txt output2.txt
	diff myExtraOutput3.txt output3.txt
	diff myExtraOutput4.txt output4.txt
	diff myExtraOutput5.txt output5.txt
	diff myExtraOutput6.txt output6.txt
	diff myExtraOutput7.txt output7.txt
	diff myExtraOutput8.txt output8.txt
