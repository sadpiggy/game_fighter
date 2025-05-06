rm -rf build
cmake -B build
cmake --build build
cp ./build/FightGame ./game