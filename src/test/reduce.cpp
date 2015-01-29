#include <iostream>
#include <list>
#include <thread>


#include "../spp.h"

int addInt(int a, int b){
   return a+b;
}

double addDouble(double a, double b){
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

void testReduceDouble(int n){
   double x[n];
   for(int i = 0; i<n; i++){
      x[i] = i+0.5;
   }
   spp::Reduce<double> reduce(addDouble, x, n);
   reduce.join();
   std::cout << "y = " << reduce.result() << std::endl;
}

void testInlineReduceInt(int n){
   int x[n];
   for(int i = 0; i<n; i++){
      x[i] = i;
   }
   int y = spp::Reduce<int>::reduce(addInt, x, n);
   std::cout << "y = " << y << std::endl;
}

void testNestedReduce(){
   spp::Fork fork;
   fork.add([](){ testReduceInt(100); });
   fork.add([](){ testReduceDouble(100); });
   fork.join();
}

int main(){
   std::cout << "Testing Reduce<int>" << std::endl;
   testReduceInt(101);
   std::cout << "Testing Reduce<double>" << std::endl;
   testReduceDouble(101);
   std::cout << "Testing ForkJoin nesting Reduce" << std::endl;
   testNestedReduce();
   std::cout << "Testing Inline Reduce<int>" << std::endl;
   testInlineReduceInt(101);
   return 0;
}
