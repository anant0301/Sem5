# CC=gcc

# all: lab1_file_transfer
	
# lab1_file_transfer: main_linux.o server.o client.o TCP.o UDP.o ACK.o log.o argsetup.h
# 	${CC} -o lab1_file_transfer main_linux.o server.o client.o TCP.o UDP.o ACK.o log.o
# main_linux.o: main_linux.c server.h client.c argsetup.h ACK.h
# 	gcc -c main_linux.c
# server.o: server.c server.h TCP.h UDP.h argsetup.h
# 	gcc -c server.c
# client.o: client.c client.h TCP.h UDP.h argsetup.h
# 	gcc -c client.c
# TCP.o: TCP.c TCP.h log.h argsetup.h
# 	gcc -c TCP.c
# UDP.o: UDP.c UDP.h ACK.h log.h argsetup.h
# 	gcc -c UDP.c
# ACK.o: ACK.c ACK.h argsetup.h
# 	gcc -c ACK.c
# log.o: log.c log.h
# 	gcc -c log.c

# clean:
# 	rm lab1_file_transfer *.o

TARGET_EXEC ?= transfer

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p