#ifndef __SPP_PIPELINE__
#define __SPP_PIPELINE__

#include <list>

#include "fork.h"

namespace spp {

template<typename Type>
class Pipeline{
public:
   void add( Type (*filter)(Type) ){
      this->filters.push_back(filter);
   }
   
   Type process(Type data){
      void (*call_back)(std::list<Type (*)(Type)>& filters, Type data, Type& res)
                   = [](std::list<Type (*)(Type)>& filters, Type data, Type& res){
         res = data;
         for(auto it = filters.begin(); it!=filters.end(); it++){
            Type (*fn)(Type) = (*it);
            res = fn(res);
         }
      };
      Type res;
      call_back(filters, data, res); //TODO fix the following fork call
      //fork.add(call_back, filters, data, res);
      //fork.join();
      return res;
   }

private:
   std::list<Type (*)(Type)> filters;
   //Fork fork;
};

}//end of spp namespace
#endif

