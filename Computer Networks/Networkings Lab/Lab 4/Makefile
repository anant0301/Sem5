
all: server client

server: server_main.o get_quesno.o pass_ques.o reset_quesnoFile.o
	gcc -o server server_main.o get_quesno.o pass_ques.o reset_quesnoFile.o

server_main.o: server_main.c
	gcc -c server_main.c
get_quesno.o: get_quesno.c
	gcc -c get_quesno.c
pass_ques.o: pass_ques.c
	gcc -c pass_ques.c
reset_quesnoFile.o: reset_quesnoFile.c
	gcc -c reset_quesnoFile.c
client: client_main.o
	gcc -o client client_main.o

client_main.o: client_main.c
	gcc -c client_main.c


