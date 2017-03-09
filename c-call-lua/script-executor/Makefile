INCPATH= \
	 -I/usr/local/luajit-2.1/include/luajit-2.1 \

LIBPATH= \
	 -L/usr/local/luajit-2.1/lib \


LIBS= \
      -lluajit-5.1


SRC= \
     executor.c  \
     sdump.c     \


BIN= \
     executor 

all:
	gcc $(INCPATH) $(LIBPATH) $(LIBS) $(SRC) -o $(BIN)


clean:
	rm -f $(BIN)
