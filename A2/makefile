FCC = gcc
LDC = gcc
LD_FLAG = -g
FLAG = -g
PROG1 = mpi_a.cx
PROG2 = mpi_c.cx
RM = /bin/rm

OBJS = mvp-student.o

all: $(PROG1) $(PROG2)

$(PROG1): $(PROG1)
    $(LDC) $(LD_FLAG) $(OBJS) -o $*.c

$(PROG2): $(PROG2)
    $(LDC) $(LD_FLAG) $(OBJS) -o $*.c

%.o: %.c
    $(FCC) $(FLAG) -c $*.c

clean: 
    $(RM) -rf *.o $(PROG1)
    $(RM) -rf *.o $(PROG2)