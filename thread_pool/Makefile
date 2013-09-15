OBJ_DIR = obj
BIN_DIR = bin
TARGET = threadpool
CC=g++
CFLAGS=-Wall -g -ggdb	
LFLAGS=-L /usr/local/lib -lboost_system -lboost_date_time -lboost_thread
INCLUDES= -I/usr/local/include -I. -Isrc/
VPATH= . src/

default: help

help:
	@echo "+-------------------------------------------------------------------------+"
	@echo "| make all             - Builds everything"
	@echo "| make build_$(TARGET) - Builds the $(TARGET) target"
	@echo "| make clean           - Cleans everything" 
	@echo "+-------------------------------------------------------------------------+"

$(OBJ_DIR)/%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

OBJECTS_TO_BUILD += \
	$(OBJ_DIR)/Main.o \
	$(OBJ_DIR)/ThreadPool.o \
	$(OBJ_DIR)/WorkerThread.o

create_build_dirs:
	mkdir -p obj
	mkdir -p bin

remove_build_dirs:
	rm -rf obj
	rm -rf bin

clean: remove_build_dirs

all: build_$(TARGET)

build_$(TARGET): create_build_dirs $(TARGET)

$(TARGET): $(OBJECTS_TO_BUILD)
	@echo "building target $(TARGET) ..."
	$(CC) $^ -o $@ $(LFLAGS)
	@mv $@ $(BIN_DIR)/
	@echo "COMPLETE - target available at $(BIN_DIR)/$@"
