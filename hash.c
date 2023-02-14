#include hash.h
unsigned long hash_key(const char* word){
  unsigned long val=0;
  for(i=0;i<strlen(word);i++){
    val=  word[i] + FACTOR*val;
  };
  return  val % SIZE
};

