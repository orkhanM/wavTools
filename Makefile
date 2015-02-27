wavsound=src/wavsound/
wavparse=src/wavparse/

all: main

main: $(wavsound)wavsound.o $(wavparse)wavparse.o
	g++ $(wavsound)wavsound.o $(wavparse)wavparse.o -lSDL -lopenal -o main main.cpp

$(wavparse)wavparse.o: $(wavparse)wavparse.cpp $(wavparse)wavparse.h
	g++ -c $(wavparse)wavparse.cpp -lSDL -lopenal -o $(wavparse)wavparse.o

$(wavsound)wavsound.o: $(wavsound)wavsound.cpp $(wavsound)wavsound.h
	g++ -c $(wavsound)wavsound.cpp -lSDL -lopenal -o $(wavsound)wavsound.o

clean:
	rm $(wavsound)wavsound.o 
	rm $(wavparse)wavparse.o
	rm main 
