VPATH=src:obj
OBJDIR=obj
all: optics main.o optics.o Point.o Reader.o 
%.o: %.cc 
	mkdir -p $(OBJDIR)
	g++ -O2 -c $< -o $(OBJDIR)/$@  `root-config --cflags --libs`
optics: main.o optics.o Point.o Reader.o
	g++ -O2 -o $@ $^ `root-config --cflags --libs`
clean:
	rm ./*~ ./$(OBJDIR)/*.o ./optics

