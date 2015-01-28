#include <iostream>
#include <list>
#include <thread>


#include "spp.h"

void helloworld_thread(){
   std::cout << "Hello, World!" << std::endl;
}

void count_thread(){
   static int count = 0;
   std::cout << "Counting " << (count++) << "..." << std::endl;
}

int applyInt(int x){
   return x+1;
}

double applyDouble(double x){
   return x*2.0+0.5;
}

void testForkJoin(){
   spp::Fork fork;
   fork.add(helloworld_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.add(count_thread);
   fork.join();
}

void testMapInt(int n){
   int x[n];
   for(int i = 0; i<n; i++){
      x[i] = i;
   }
   spp::Map<int> map(applyInt, x, n);
   map.join();
   std::cout << "y = ";
   for(int i = 0; i<n; i++){
      std::cout << map.result()[i] << "; ";
      std::cout.flush();
   }
   std::cout << std::endl;
   delete map.result();
}

void testMapDouble(int n){
   double x[n];
   for(int i = 0; i<n; i++){
      x[i] = (double)i;
   }
   spp::Map<double> map(applyDouble, x, n);
   map.join();
   std::cout << "y = ";
   for(int i = 0; i<n; i++){
      std::cout << map.result()[i] << "; ";
      std::cout.flush();
   }
   std::cout << std::endl;
   delete map.result();
}

int addInt(int a, int b){
   return a+b;
}

void testReduceInt(int n){
   int x[n];
   for(int i = 0; i<n; i++){
      x[i] = i;
   }
   spp::Reduce<int> reduce(addInt, x, n);
   reduce.join();
   std::cout << "y = " << reduce.result() << std::endl;
}

int main(){
   std::cout << "Testing ForkJoin" << std::endl;
   testForkJoin();
   std::cout << "Testing Map<int>" << std::endl;
   testMapInt(10);
   std::cout << "Testing Map<double>" << std::endl;
   testMapDouble(15);
   std::cout << "Testing ForkJoin nesting Map" << std::endl;
   spp::Fork fork;
   fork.add([](){ testMapInt(1000); });
   fork.add([](){ testMapDouble(1000); });
   fork.join();
   std::cout << "Testing Reduce<int>" << std::endl;
   testReduceInt(101);
   return 0;
}
