echo "Generating googletest libraly"
clang++ -std=c++1y -pthread -g -Wall -Wextra -isystem tests/googletest/googletest/include -isystem tests/googletest/googletest/ -c -o tests/gtest-all.o tests/googletest/googletest/src/gtest-all.cc
echo "Done compiling gtest-all.cc"
ar -rv tests/libgtest.a tests/gtest-all.o
echo "Done archiving gtest-all.o"
echo "Compiling unit tests..."
clang++ -std=c++1y -pthread -g -Wall -Wextra -isystem tests/googletest/googletest/include -c -o tests/main.o tests/main.cpp
echo "Done compiling main.cpp"
clang++ -std=c++1y -pthread -g -Wall -Wextra -isystem tests/googletest/googletest/include -c -o tests/node_test.o tests/node_test.cpp
echo "Done compiling node_test.cpp"
clang++ -std=c++1y -pthread -g -Wall -Wextra -isystem tests/googletest/googletest/include -c -o tests/ksom_test.o tests/ksom_test.cpp
echo "Done compiling ksom_test.cpp"
clang++ -std=c++1y -g -Wall -Wextra -o tests/gtest tests/main.o tests/node_test.o tests/ksom_test.o -pthread -Ltests/ -lgtest
echo "Running unit tests..."
tests/gtest -v
result=$?
rm -r tests/gtest tests/main.o tests/node_test.o tests/ksom_test.o tests/gtest-all.o tests/libgtest.a
echo "Unit tests completed : $result"
exit $result
