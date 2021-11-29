CC	=	g++
CFLAGS	=	-W	-Wall	-ansi	-std=c++11	-g
LIBS	=
LDFLAGS	= `sdl2-config --cflags --libs`
EXEC	=	main
INCLUDES=  vehicule.hpp
SRC	=	main.cpp vehicule.cpp
OBJ	=	$(SRC:.cpp=.o)

all:	$(EXEC)
main:	$(OBJ)
	$(CC)	$(CFLAGS)	$(INCLUDES)	-o	$@	$^	$(LIBS)	$(LDFLAGS)
%.o:	%.c
	$(CC)	$(CFLAGS)	-o	$@	-c	$<
clean:
	rm	-rf	*.o	*~
rmall:	clean
	rm	-rf	$(EXEC)
