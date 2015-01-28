#ifndef __SPP_STENCIL__
#define __SPP_STENCIL__

#include <list>
#include <list>

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
         std::thread *t = new std::thread(call_back, func, data, output, int(i*(float(len)/float(nthreads))), int((i+1)*(float(len)/float(nthreads))));
         this->threads.push_back(t);
      }
   }

   void join(){
      for(std::list<std::thread*>::iterator it = this->threads.begin(); it!=this->threads.end(); it++){
         (*it)->join();
         delete (*it);
      }
      this->threads.clear();
   }

   Type *result(){
      return output;
   }
private:
   std::list<std::thread*> threads;
   Type *output;
   int nthreads;
};

}//end of spp namespace
#endif
