#ifndef __SPP_PIPELINE__
#define __SPP_PIPELINE__

#include <list>
#include <thread>

namespace spp {

template<typename Type>
class Pipeline{
public:
   Pipeline(){
   }

   void add( Type (*filter)(Type) ){
      this->filters.push_back(filter);
   }
   
   Type process(Type data){
      
      std::thread t( [](std::list<Type(*)(Type)> &list, Type data){
                        } );
   }

   void join(){
      for(std::list<std::thread*>::iterator it = this->threads.begin(); it!=this->threads.end(); it++){
         (*it)->join();
         delete (*it);
      }
      this->threads.clear();
   }
private:
   std::list<Type (*)(Type)> filters;
   std::list<std::thread*> threads;
};

}//end of spp namespace
#endif

