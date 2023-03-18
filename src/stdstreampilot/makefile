CC = g++
TARGET = ftxui

all:
	$(CC) -o $(TARGET).o -c $(TARGET).cpp --std=c++20
	$(CC) -o $(TARGET) $(TARGET).o ftxui/libftxui-component.a ftxui/libftxui-dom.a ftxui/libftxui-screen.a
