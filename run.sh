mkdir build
cd build
cmake ..
make
clear
./ADS 50 --dynamic
cd ..
rm -r ./build/CMakeFiles