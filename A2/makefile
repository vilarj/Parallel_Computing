FCC = gcc
LDC = gcc
LD_FLAG = -g
FLAG = -g
PROG = mpi_a.cx
RM = /bin/rm

OBJS = mvp-student.o

all: $(PROG)

$(PROG): $(PROG)
    $(LDC) $(LD_FLAG) $(OBJS) -o $*.c

%.o: %.c
    $(FCC) $(FLAG) -c $*.c

clean: 
    $(RM) -rf *.o $(PROG)