SRC=src/
OBJ=obj/
INCLUDE=include/

all: main

main: $(OBJ)wavsound.o $(OBJ)wavparse.o
	g++ $(OBJ)wavsound.o $(OBJ)wavparse.o -lSDL -lopenal -o main $(SRC)main.cpp -I $(INCLUDE)


$(OBJ)wavparse.o: $(SRC)wavparse.cpp $(INCLUDE)wavparse.h
	g++ -c $(SRC)wavparse.cpp -lSDL -lopenal -o $(OBJ)wavparse.o -I $(INCLUDE)

$(OBJ)wavsound.o: $(SRC)wavsound.cpp $(INCLUDE)wavsound.h $(OBJ)
	g++ -c $(SRC)wavsound.cpp -lSDL -lopenal -o $(OBJ)wavsound.o -I $(INCLUDE)

$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm $(OBJ)wavsound.o 
	rm $(OBJ)wavparse.o
	rm main 
