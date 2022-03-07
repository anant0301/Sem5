#!/bin/bash

#created by Anant Patel
#COE18B004
all: userver uclient tserver tclient

userver: udpServer.o userverMain.o arithematic.o
	g++ -o userver udpServer.o userverMain.o arithematic.o

uclient:  udpClient.o uclientMain.o
	g++ -o uclient udpClient.o uclientMain.o

tserver: tcpServer.o tserverMain.o arithematic.o
	g++ -o tserver tcpServer.o tserverMain.o arithematic.o

tclient: tcpClient.o tcpclientMain.o
	g++ -o tclient tcpClient.o tcpclientMain.o arithematic.o


arithematic.o: arithematic.cpp
	g++ -c arithematic.cpp
udpServer.o: udpServer.cpp
	g++ -c udpServer.cpp

udpClient.o: udpClient.cpp
	g++ -c udpClient.cpp

userverMain.o: userverMain.cpp
	g++ -c userverMain.cpp

uclientMain.o: uclientMain.cpp
	g++ -c uclientMain.cpp

tcpServer.o: tcpServer.cpp
	g++ -c tcpServer.cpp

tcpClient.o: tcpClient.cpp
	g++ -c tcpClient.cpp

tserverMain.o: tserverMain.cpp
	g++ -c tserverMain.cpp

tclientMain.o: tclientMain.cpp
	g++ -c tclientMain.cpp
