#ifndef __SPP_REDUCE__
#define __SPP_REDUCE__

#include "fork.h"

namespace spp{

template<typename Type>
class Reduce{
public:
   Reduce(Type (*func)(Type, Type), Type *data, int len){
      this->func = func;
      nthreads = 4;
      tmpOut = new Type[nthreads];
      void (*call_back)(Type (*func)(Type, Type), Type *in, Type *out, int begin, int end) = [](Type (*func)(Type, Type), Type *in, Type *out, int begin, int end){
         *out = in[begin];
         for(int i = begin+1; i<end; i++){
            *out = func(*out, in[i]);
         }
      };
      for(int i = 0; i<nthreads; i++){
         this->fork.add(call_back, func, data, &(tmpOut[i]), int(i*(float(len)/float(nthreads))), int((i+1)*(float(len)/float(nthreads))));
      }
   }

   void join(){
      this->fork.join();
      output = tmpOut[0];
      for(int i = 1; i<nthreads; i++){
         output = func(output, tmpOut[i]);
      }
      delete tmpOut;
   }

   Type result(){
      return output;
   }

   static Type reduce(Type (*func)(Type, Type), Type *data, int len){
      Reduce<Type> r(func, data, len); 
      r.join(); 
      return r.result();
   } 
private:
   Fork fork;
   Type (*func)(Type, Type);
   Type output;
   Type *tmpOut;
   int nthreads;
};

}//end of spp namespace
#endif
