#define SIZE 98317
#define FACTOR 37
struct  node{
  int key;
  int value;
};
unsigned long hash_key(const char* word);
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);
int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);
