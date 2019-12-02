#**********************************************************************************
# Author:      Sascha Heinisch
# Date:        28.11.2019
# 
# Description: Make file for circular buffer test. 
#
#**********************************************************************************

CC      = c++
CFLAGS  = -Wall -Wextra -Werror -Wpedantic -std=c++11 -g
OBJ     = main.o

.PHONY: clean

testcb: $(OBJ)
	$(CC) $(CFLAGS) -o testcb $(OBJ) 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJ) testcb
