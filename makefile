
clear: run
	rm -f PVZ.o Game.o Zombie.o Seed_Packet.o Sun_Packet.o Sun.o Row.o Block.o

run: PVZ
	./PVZ

PVZ: PVZ.o Game.o Zombie.o Seed_Packet.o Sun_Packet.o Sun.o Row.o Block.o
	g++ PVZ.o Game.o Zombie.o Seed_Packet.o Row.o Block.o Sun_Packet.o Sun.o -o PVZ -lsfml-graphics -lsfml-window -l sfml-system
	
Seed_Packet.o: Seed_Packet.cpp Seed_Packet.hpp
	g++ -c $<

Sun_Packet.o: Sun_Packet.cpp Sun_Packet.hpp Sun.hpp Seed_Packet.hpp
	g++ -c $<

Sun.o: Sun.cpp Sun.hpp Seed_Packet.hpp
	g++ -c $<

Row.o: Row.cpp Row.hpp Block.hpp Zombie.hpp Sun_Packet.hpp Sun.hpp Seed_Packet.hpp
	g++ -c $<

Block.o: Block.cpp Block.hpp Zombie.hpp Sun_Packet.hpp Sun.hpp Seed_Packet.hpp
	g++ -c $<

PVZ.o: PVZ.cpp Game.hpp
	g++ -c $<

Game.o: Game.cpp Game.hpp
	g++ -c $<

Zombie.o: Zombie.cpp Zombie.hpp Sun_Packet.hpp Sun.hpp Seed_Packet.hpp
	g++ -c $<

