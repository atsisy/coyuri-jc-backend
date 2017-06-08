#include "types.hpp"

MochiGoma *create_mochigoma(){
      MochiGoma *new_mochi = (MochiGoma *)malloc(sizeof(MochiGoma));
      for(u8_t i = 0;i < _MOCHIGOMA_LIMIT;++i){
            new_mochi->tegoma[i] = EMPTY;
      }
      new_mochi->pointer = 0;
      return new_mochi;
}
