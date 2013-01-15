#!/bin/bash
clang++ src/private_storage.cpp src/granfs_node.cpp src/capfs_node.cpp src/testmain.cpp -Iinc -lboost_filesystem -lboost_system -o testmain -Werror
