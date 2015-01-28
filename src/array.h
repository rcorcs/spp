#ifndef __SPP_ARRAY__
#define __SPP_ARRAY__

namespace spp {

template<typename Type>
class Array{
public:
   Array(int len){
      this->array = new Type[len];
      this->len = len;
   }

   Array slice(int offset, int len){
      Array arr(this->array+offset*sizeof(Type), len);
      return arr;
   }

   int size(){
      return this->len;
   }

   Type get(int index){
      return this->array[index];
   }

   void set(int index, Type data){
      this->array[index] = data;
   }
private:
   Array(Type *array, int len){
      this->array = array;
      this->len = len;
   }
   Type *array;
   int len;
};

}
#endif
