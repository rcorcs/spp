#ifndef __SPP_MAP__
#define __SPP_MAP__

#include "fork.h"

namespace spp{

template<typename Type>
class Stencil{
public:
   Stencil(Type (*func)(Type), Type *data, int len){
      output = new Type[len];
      nthreads = 4;
      void (*call_back)(Type (*func)(Type), Type *in, Type *out, int begin, int end) = [](Type (*func)(Type), Type *in, Type *out, int begin, int end){
         for(int i = begin; i<end; i++){
            out[i] = func(in[i]);
         }
      };
      for(int i = 0; i<nthreads; i++){
         this->fork.add(call_back, func, data, output, int(i*(float(len)/float(nthreads))), int((i+1)*(float(len)/float(nthreads))));
      }
   }

   void join(){
      this->fork.join();
   }

   Type *result(){
      return output;
   }

   static Type *map(Type (*func)(Type), Type *data, int len){
      Map<Type> m(func, data, len);
      m.join();
      return m.result();
   }
private:
   Fork fork;
   Type *output;
   int nthreads;
};

}//end of spp namespace
#endif
