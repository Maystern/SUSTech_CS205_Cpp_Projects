cd build
rm -rf *
cmake ..
make
cd bin
mv matrixClassTest ..
cd ..
mv matrixClassTest ..