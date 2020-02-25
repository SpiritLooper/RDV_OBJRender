CC = g++
CFLAGS = -Wall -g
EXEC_NAME = obj_render.out
INCLUDES =
LIBS =
OBJ_FILES = matrix.o camera.o image.o model.o obj_render.o
BUILD = build

all : prebuild $(EXEC_NAME)

prebuild : 
	@if [ ! -d ${BUILD} ]; then mkdir ${BUILD} ; fi

clean :
	rm -r ${BUILD}

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)
	@mv ${OBJ_FILES} ${EXEC_NAME} ${BUILD}

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
