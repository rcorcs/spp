#ifndef __SPP_FORK__
#define __SPP_FORK__

#include <list>
#include <thread>

namespace spp {

class Fork{
public:

/*   void add( void (*call_back)() ){
      std::thread *t = new std::thread(call_back);
      this->threads.push_back(t);
   }
*/
   template<typename Fn, typename... Args>
   void add(Fn&& fn, Args&&... args){
      std::thread *t = new std::thread(fn, args...);
      this->threads.push_back(t);
   }

   void join(){
      for(std::list<std::thread*>::iterator it = this->threads.begin(); it!=this->threads.end(); it++){
         (*it)->join();
         delete (*it);
      }
      this->threads.clear();
   }
private:
   std::list<std::thread*> threads;
};

}//end of spp namespace
#endif

