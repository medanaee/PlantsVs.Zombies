
clear: run
	rm -f PVZ.o Game.o Zombie.o

run: sfml-app
	./sfml-app

sfml-app: PVZ.o Game.o Zombie.o
	g++ PVZ.o Game.o Zombie.o -o sfml-app -lsfml-graphics -lsfml-window -l sfml-system
	
PVZ.o: PVZ.cpp Game.hpp
	g++ -c PVZ.cpp

Game.o: Game.cpp Game.hpp
	g++ -c Game.cpp

Zombie.o: Zombie.cpp Zombie.hpp
	g++ -c $<

