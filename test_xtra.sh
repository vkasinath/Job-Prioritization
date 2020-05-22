#!/bin/bash
#'sed -i 's/\r$//' filename'

echo 'compiling...'
g++ -ggdb -lm -o t.exe job_extra.cpp main_extra.cpp ElegantQueue.cpp -Wall

echo 'test1.txt test1.out'
./t.exe test1.txt test1.out
diff -s test1.out out_test1.txt

echo 'test2.txt test2.out'
./t.exe test2.txt test2.out
diff -s test2.out out_test2.txt

echo 'test3.txt test3.out'
./t.exe test3.txt test3.out
diff -s test3.out out_test3.txt

echo 'test4.txt test4.out'
./t.exe test4.txt test4.out
diff -s test4.out out_test4.txt

