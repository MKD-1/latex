mkdir -p build
FILE="$1"
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ -Wall -Wextra -Wfatal-errors -Wconversion -std=c++17 build/temp.cpp -o build/test-compiles.exe && rm -f build/test-compiles.exe build/temp.cpp
