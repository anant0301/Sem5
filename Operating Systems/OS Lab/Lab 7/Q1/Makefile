
q1: q1_main.o queue_functions.o producer.o consumer.o 
	gcc -o q1  q1_main.o queue_functions.o producer.o consumer.o -lpthread 

q1_main.o: q1_main.c 
	gcc -c q1_main.c 

queue_functions.o: queue_functions.c 
	gcc -c queue_functions.c 

producer.o: producer.c 
	gcc -c producer.c 

consumer.o: consumer.c 
	gcc -c consumer.c 


clean:
	rm ./*.o