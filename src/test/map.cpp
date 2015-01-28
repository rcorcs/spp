#include <iostream>
#include <list>
#include <thread>

#include "../spp.h"

int applyInt(int x){
   return x+1;
}

double applyDouble(double x){
   return x*2.0+0.5;
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

void testInlineMapInt(int n){
   int x[n];
   for(int i = 0; i<n; i++){
      x[i] = i;
   }
   int *y = spp::Map<int>::map(applyInt, x, n);
   std::cout << "y = ";
   for(int i = 0; i<n; i++){
      std::cout << y[i] << "; ";
      std::cout.flush();
   }
   std::cout << std::endl;
   delete y;
}

void testNestedMap(){
   spp::Fork fork;
   fork.add([](){ testMapInt(100); });
   fork.add([](){ testMapDouble(100); });
   fork.join();
}

int main(){
   std::cout << "Testing Map<int>" << std::endl;
   testMapInt(10);
   std::cout << "Testing Map<double>" << std::endl;
   testMapDouble(15);
   std::cout << "Testing ForkJoin nesting Map" << std::endl;
   testNestedMap();
   std::cout << "Testing Inline Map<int>" << std::endl;
   testInlineMapInt(20);
   return 0;
}
