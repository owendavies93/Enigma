CC       = g++
CPPFLAGS = -c -Wall

# rules for exec
enigma: Main.o enigma.o reflector.o rotor.o plugboard.o networked.o server.o client.o

# rules for *.o
Main.o:      Main.cpp
enigma.o:    enigma.cpp
plugboard.o: plugboard.cpp
reflector.o: reflector.cpp
rotor.o:     rotor.cpp
networked.o: networked.cpp
server.o:	 server.cpp
client.o:	 client.cpp

clean:
	rm -rf enigma *.o tests tests.hi

.phony: clean
