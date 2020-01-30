GCC = g++
FLAGS = -g -Wall
FILES = obj_render.cpp
EXE = obj_render.out
BUILD = build

all: 
	${GCC} ${FLAGS} ${FILES} -o ${EXE}
	@if [ ! -d ${BUILD} ]; then mkdir ${BUILD} ; fi
	@mv ${EXE} ${BUILD}

clean: 
	@rm -rv ${BUILD}