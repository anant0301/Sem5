
q2: q2_main.o queue_functions.o producer.o consumer.o 
	gcc -o q2  q2_main.o queue_functions.o producer.o consumer.o -lpthread 

q2_main.o: q2_main.c 
	gcc -c q2_main.c 

queue_functions.o: queue_functions.c 
	gcc -c queue_functions.c 

producer.o: producer.c 
	gcc -c producer.c 

consumer.o: consumer.c 
	gcc -c consumer.c 


clean:
	rm ./*.o