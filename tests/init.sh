#!/bin/sh
clang++ -std=c++1y -isystem googletest/googletest/include -isystem googletest/googletest/ -pthread -c googletest/googletest/src/gtest-all.cc && \
    ar -rv libgtest.a gtest-all.o && \
    rm -f gtest-all.o
