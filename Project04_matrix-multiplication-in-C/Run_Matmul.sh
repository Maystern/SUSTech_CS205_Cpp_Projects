sudo apt-get install libopenblas-dev
cd build
rm -rf *
cmake ..
make
cd bin
mv matmulTest ..
cd ..
mv matmulTest ..