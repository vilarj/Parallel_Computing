CC = mpicc
CPP = mpic++
LDC = mpicc
LD_FLAGS = -lm -fopenmp -lstdc++ -lopencv_core -lopencv_highgui -lopencv_imgproc
FLAGS = -fopenmp
CPPFLAGS= -I/usr/include/opencv $(FLAGS)
PARALLEL=A6parallel_starter.cx
RM= /bin/rm


#all rule

POBJS=$(PARALLEL:%.cx=%.o)

TOOLS+=imageTools.o

all: $(PARALLEL)

$(PARALLEL): $(POBJS) $(TOOLS)
	$(LDC)  $^ $(LD_FLAGS) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@
%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $^ -o $@

#clean rule
clean:
	$(RM) -rf *.o *.x *.cx *.mod
