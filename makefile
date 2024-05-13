out_path = ./outputs/

clear: run
	rm -f PVZ

run: PVZ
	./PVZ
		
./outputs/Seed_Packet.o: Seed_Packet.cpp Seed_Packet.hpp Headers.hpp
	g++ -c $< -o $@

./outputs/Sun_Packet.o: Sun_Packet.cpp Sun_Packet.hpp Headers.hpp
	g++ -c $< -o $@

./outputs/Sun.o: Sun.cpp Sun.hpp Headers.hpp
	g++ -c $< -o $@

./outputs/Row.o: Row.cpp Row.hpp Headers.hpp Block.hpp
	g++ -c $< -o $@

./outputs/Block.o: Block.cpp Block.hpp Headers.hpp Plant.hpp
	g++ -c $< -o $@

./outputs/Game.o: Game.cpp Game.hpp Headers.hpp Row.hpp Block.hpp Zombie.hpp Sun_Packet.hpp Sun.hpp Seed_Packet.hpp Plant.hpp Pea.hpp Setting.hpp
	g++ -c $< -o $@

./outputs/Zombie.o: Zombie.cpp Zombie.hpp Headers.hpp Pea.hpp
	g++ -c $< -o $@

./outputs/Pea.o: Pea.cpp Pea.hpp Headers.hpp Plant.hpp
	g++ -c $< -o $@

./outputs/Plant.o: Plant.cpp Plant.hpp Headers.hpp Block.hpp
	g++ -c $< -o $@

./outputs/Invasive_Plant.o: Invasive_Plant.cpp Invasive_Plant.hpp Headers.hpp Block.hpp Plant.hpp
	g++ -c $< -o $@

./outputs/Sun_Plant.o: Sun_Plant.cpp Sun_Plant.hpp Headers.hpp Block.hpp Plant.hpp
	g++ -c $< -o $@

./outputs/Defender_Plant.o: Defender_Plant.cpp Defender_Plant.hpp Headers.hpp Block.hpp Plant.hpp
	g++ -c $< -o $@

./outputs/Setting.o: Setting.cpp Setting.hpp Headers.hpp
	g++ -c $< -o $@

PVZ: $(out_path)PVZ.o $(out_path)Defender_Plant.o $(out_path)Game.o $(out_path)Sun_Plant.o $(out_path)Setting.o $(out_path)Zombie.o $(out_path)Seed_Packet.o $(out_path)Sun_Packet.o $(out_path)Sun.o $(out_path)Row.o $(out_path)Block.o $(out_path)Pea.o $(out_path)Plant.o $(out_path)Invasive_Plant.o
	g++ $^ -o PVZ -lsfml-graphics -lsfml-window -l sfml-system

./outputs/PVZ.o: PVZ.cpp Game.hpp
	g++ -c $< -o $@