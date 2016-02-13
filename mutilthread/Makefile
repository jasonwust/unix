cc= gcc
cflag= -Wall -o
src= mthread.c
objs= mthread
libs= -lpthread
$(objs) : $(src)
	$(cc) $(cflag)  $@ $<  $(libs)

clean:
	rm -rf *.o
