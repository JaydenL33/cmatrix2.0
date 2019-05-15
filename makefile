# makefile for Encryption testing on crypto branch! See the github:
# https://github.com/rlcaust/Fund-O-C

##############################################
# Defining make macros:
# wildcard function from make, searches through
# pwd for files matching *.c
#
# SRC:.c=.o is a pattern naming all *.c files found
# to *.o files
##############################################
LINK_TARGET = main.exe
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -ansi

##############################################
# 	Auto clean (on make)
##############################################
clean:
	rm -f $(OBJS) $(LINK_TARGET)
	echo Clean complete!

##############################################
#	 Compile all (make all)
##############################################
all : $(LINK_TARGET)
	
# $@ is target & $^ is dependency(s)
$(LINK_TARGET) : $(OBJS)
	gcc $(CFLAGS) -o $@ $^ -lm
	echo All done!

# use macro : pattern match to compile src
# again, $^ matches dependency(s)
#$(OBJS): lec3.c
#	gcc -c $(CFLAGS) $^ -lm
