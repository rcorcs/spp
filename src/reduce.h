#ifndef __SPP_REDUCE__
#define __SPP_REDUCE__

#include <list>
#include <thread>

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
         std::thread *t = new std::thread(call_back, func, data, &(tmpOut[i]), int(i*(float(len)/float(nthreads))), int((i+1)*(float(len)/float(nthreads))));
         this->threads.push_back(t);
      }
   }

   void join(){
      for(std::list<std::thread*>::iterator it = this->threads.begin(); it!=this->threads.end(); it++){
         (*it)->join();
         delete (*it);
      }
      this->threads.clear();
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
   std::list<std::thread*> threads;
   Type (*func)(Type, Type);
   Type output;
   Type *tmpOut;
   int nthreads;
};

}//end of spp namespace
#endif
