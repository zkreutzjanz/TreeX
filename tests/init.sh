echo "Compiling..."
g++ ../src/Main.cpp -o ../bin/treeX
echo "Compiled"
echo "Running..."
../bin/treeX.exe view ../assets/KreutzjansFamilyTree.ged
