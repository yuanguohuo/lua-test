INCPATH= \
	 -I/usr/local/luajit-2.1/include/luajit-2.1 \


LIBPATH= \
	 -L/usr/local/luajit-2.1/lib \

LIBS= \
      -lluajit-5.1

SRC= \
     libwatermelon.c  \


BIN= \
     libwatermelon.so
     

all:
	gcc -fPIC -shared -Wall $(INCPATH) $(LIBPATH) $(LIBS) $(SRC) -o $(BIN)

clean:
	rm -f $(BIN)
