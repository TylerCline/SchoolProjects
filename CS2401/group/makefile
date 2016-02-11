#Curtis Lewis, Shelby Harris, Tyler Cline

a.out: main.o roads.o trucks.o
  g++ main.cc roads.cc trucks.cc
roads.o: roads.h roads.cc trucks.h
  g++ -c roads.cc
trucks.o : trucks.h trucks.cc roads.h
  g++ -c trucks.cc
main.o : roads.h trucks.h
  g++ -c main.cc
