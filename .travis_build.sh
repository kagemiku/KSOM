echo "Compiling unit tests..."
clang++ -std=c++1y -pthread -g -Wall -Wextra -c -o tests/main.o tests/main.cpp
echo "Done compiling main.cpp"
clang++ -std=c++1y -pthread -g -Wall -Wextra -c -o tests/node_test.o tests/node_test.cpp
echo "Done compiling node_test.cpp"
clang++ -std=c++1y -pthread -g -Wall -Wextra -c -o tests/ksom_test.o tests/ksom_test.cpp
echo "Done compiling ksom_test.cpp"
clang++ -std=c++1y -g -Wall -Wextra -o tests/gtest tests/main.o tests/node_test.o tests/ksom_test.o -lgtest -pthread
echo "Running unit tests..."
tests/gtest -v
result=$?
rm -r tests/gtest tests/main.o tests/node_test.o tests/ksom_test.o
echo "Unit tests completed : $result"
exit $result
