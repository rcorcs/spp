#include <iostream>
#include <list>
#include <thread>


#include "../spp.h"

void helloworld_thread(){
   std::cout << "Hello, World!" << std::endl;
}

void count_thread(){
   static int count = 0;
   std::cout << "Counting " << (count++) << "..." << std::endl;
}

void printHello(const char *name){
   std::cout << "Hello " << name << std::endl;
}

void testForkJoin(){
   spp::Fork fork;
   fork.add(helloworld_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.add(printHello, "Rodrigo Rocha");
   fork.add(printHello, "Algorithmic Skeletons");
   fork.join();
}

int main(){
   std::cout << "Testing ForkJoin" << std::endl;
   testForkJoin();
   return 0;
}
