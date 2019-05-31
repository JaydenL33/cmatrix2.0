# makefile for Encryption testing on crypto branch! See the github:
# https://github.com/rlcaust/Fund-O-C
# Author: Albert Ferguson

################################################################################
# Defining make macros:
#
# wildcard function from make, searches through
# current directory for files matching *.c
#
# SRC:.c=.o is a pattern naming all *.c files found
# to *.o files
#
# $@ is target & $^ is dependency(s)
################################################################################

# primary link target and source file
LINK_TARGET = main.out
LINK_SRC  = $(LINK_TARGET:.out=.c)

# lib directory macros
STATIC_LIBS = libs
STATIC_CRYPTO = $(STATIC_LIBS)/Crypto
STATIC_RAINDROPS = $(STATIC_LIBS)/PrintRaindrops
STATIC_UTIL = $(STATIC_LIBS)/Util

# src and target macros
CRYPTO_SRC = $(wildcard $(STATIC_CRYPTO)/*.c)
CRYPTO_TARGET = libCrypto.a
RAINDROPS_SRC = $(wildcard $(STATIC_RAINDROPS)/*.c)
RAINDROPS_TARGET = libRaindrops.a
UTIL_SRC = $(wildcard $(STATIC_UTIL)/*.c)
UTIL_TARGET = libUtil.a

# object files
OBJS = $(LINK_SRC:.c=.o)

# clean targets, any object and/or compiled libs
CLEAN_OBJS = $(wildcard *.o)
CLEAN_LIBS = $(CRYPTO_TARGET) $(RAINDROPS_TARGET) $(UTIL_TARGET)

# compile flags
LIBFLAGS = ar -rcs
CCFLAGS = gcc -g -Wall -Werror -ansi

################################################################################
#	 Compile all (default make command)
################################################################################
.PHONY : all
all : $(LINK_TARGET)
	@echo $(OSFLAG)

$(LINK_TARGET) : libraries
	$(CCFLAGS) -o $@ $(LINK_SRC) $(CRYPTO_TARGET) $(UTIL_TARGET) $(RAINDROPS_TARGET)
	@echo ============== All done! ========================

################################################################################
#	Compile libraries (static),
# 	compile each of the three libraries required
################################################################################
libraries : $(UTIL_SRC:.c=.o) $(CRYPTO_SRC:.c=.o) $(RAINDROPS_SRC:.c=.o)
	$(LIBFLAGS) $(UTIL_TARGET) $(UTIL_SRC:.c=.o)
	$(LIBFLAGS) $(CRYPTO_TARGET) $(CRYPTO_SRC:.c=.o)
	$(LIBFLAGS) $(RAINDROPS_TARGET) $(RAINDROPS_SRC:.c=.o)
	@echo ============== Libraries compilled! =============

$(UTIL_SRC:.c=.o) : $(STATIC_UTIL)
	$(CCFLAGS) -c $(wildcard $^/*.c) -o $@

$(CRYPTO_SRC:.c=.o) : $(STATIC_CRYPTO)
	$(CCFLAGS) -c $(wildcard $^/*.c) -o $@

$(RAINDROPS_SRC:.c=.o) : $(STATIC_RAINDROPS)
	$(CCFLAGS) -c $(wildcard $^/*.c) -o $@

################################################################################
#	Clean directory
################################################################################
.PHONY : clean
clean :
	rm -f $(CLEAN_OBJS) $(LINK_TARGET) $(STATIC_LIB_TARGET)
	rm -f $(wildcard $(STATIC_CRYPTO)/*.o)
	rm -f $(wildcard $(STATIC_RAINDROPS)/*.o)
	rm -f $(wildcard $(STATIC_UTIL)/*.o)
	@echo ============== Clean all complete! ==============

