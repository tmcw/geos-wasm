FLAGS=`geos-config --cflags`
LIBS=`geos-config --clibs`


cc $LIBS hello_world.c $FLAGS -o hello_world
emcc $LIBS hello_world.c $FLAGS -o hello_world
