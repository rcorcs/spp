#include <iostream>
#include <list>
#include <thread>


#include "../spp.h"

int add2(int a){
   return a+2;
}

int add5(int a){
   return a+5;
}

void testForkJoin(){
   spp::Pipeline<int> pipeline;
   pipeline.add(add2);
   pipeline.add(add5);
   std::cout << pipeline.process(10) << std::endl;
}

int main(){
   std::cout << "Testing ForkJoin" << std::endl;
   testForkJoin();
   return 0;
}
