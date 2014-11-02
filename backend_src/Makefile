OPT=-g -Wall -fPIC
LOPT= -shared
TARGET=lib-backend.so

build: backend
	g++ $(LOPT) *.o -o $(TARGET)

backend: backend.cpp
	g++ $(OPT) -c backend.cpp

clean:
	rm -f *.o $(TARGET)


