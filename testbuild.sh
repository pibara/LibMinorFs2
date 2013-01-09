#!/bin/bash
g++ src/stublib.cpp src/testmain.cpp -Iinc -lboost_filesystem -lboost_system -o testmain -Werror
