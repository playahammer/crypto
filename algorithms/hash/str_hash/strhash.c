#include "strhash.h"

int bkdr_hash(void * ptr)
{
      assert(ptr);

      const int seed = 131;

      int hash = 0;
      
      char * char_ptr = (char *)ptr;
      while (*char_ptr)
      {
            hash = hash * seed + *char_ptr++;
            
      }
      
      return (hash & 0x7fffffff);
}

int ap_hash(void * ptr)
{
      assert(ptr);

      char * char_ptr = (char *) ptr;

      int i = 0;

      int hash = 0;
      while (*char_ptr)
      {
            if ((i & 1) == 0)
                  hash ^= (hash << 7) ^ (*char_ptr++) ^ (hash >> 3);
            else 
                  hash ^= ~((hash << 11) ^ (*char_ptr++) ^ (hash >> 5)); 
            i++;
      }
      return (hash & 0x7fffffff);
}

int js_hash(void * ptr)
{
      assert(ptr);

      int hash = 0;

      char * char_ptr = (char *)ptr;

      while (*char_ptr)
            hash ^= (hash << 5) + (*char_ptr++) + (hash >> 2);

      return (hash & 0x7fffffff);
}

int rs_hash(void * ptr)
{
      assert(ptr);

      int a = 63689;
      const int b = 378551;
      
      char * char_ptr = (char *)ptr;

      int hash = 0;

      while (*char_ptr)
      {
            hash = hash * a + *char_ptr++;
            a *= b;
      }
      return (hash & 0x7fffffff);
}

int sdbm_hash(void * ptr)
{
      assert(ptr);
      
      int hash = 0;

      char * char_ptr = (char *)ptr;
      
      while (*char_ptr)
            hash = (*char_ptr++) + (hash << 6) + (hash << 16) - hash;

      return (hash & 0x7fffffff);
}


int pjw_hash(void * ptr)
{
      assert(ptr);

      int bits_in_unsigned_int = 32;
      int three_quarters       = 24;
      int one_eighth           = 4;
      int high_bits            = (int) (0xffffffff << (bits_in_unsigned_int - one_eighth));
      int hash                 = 0;
      int test                 = 0;

      char * char_ptr = (char *)ptr;
      while (*char_ptr)
      {
            hash = (hash << one_eighth) + *char_ptr++;

            if((test = hash & high_bits) != 0){
                  hash = ((hash ^ (test >> three_quarters)) & (~high_bits));
            }
      }
      return (hash & 0x7fffffff);
}


int elf_hash(void * ptr)
{
      assert(ptr);

      int hash = 0;
      int x = 0;

      char * char_ptr = (char *)ptr;

      while (*char_ptr)
      {
            hash = (hash << 4) + *char_ptr++;

            if ((x & hash & 0xf0000000) != 0)
            {
                  hash ^= x >> 24;
                  hash &= ~x;
            }
            
      }
      
      return (hash & 0x7fffffff);
}


int djb_hash(void * ptr)
{
      assert(ptr);
      
      char * char_ptr = (char *) ptr;
      
      int hash = 5381;

      while (*char_ptr)
            hash += (hash << 5) + *char_ptr++;
      
      return (hash & 0x7fffffff);
}


int dek_hash(void * ptr, size_t len)
{
      assert(ptr);

      char * char_ptr = (char *) ptr;

      int hash = len;

      while (*char_ptr) 
            hash = (hash << 5) ^ (hash >> 27) ^ (*char_ptr++);
      
      return (hash & 0x7fffffff);
      
}


int bp_hash(void * ptr, size_t len)
{
      assert(ptr);

      char * char_ptr = (char *)ptr;

      int hash = len;

      while (*char_ptr)
            hash = (hash << 7) ^ *char_ptr++;
      
      return (hash & 0x7fffffff);
}


int fnv_hash(void * ptr)
{
      assert(ptr);

      int fnv_prime = 0x811c9dc5;
      int hash = 0;

      char * char_ptr = (char *)ptr;
      while (*char_ptr)
      {
            hash *= fnv_prime;
            hash ^= *char_ptr++;
      }
      return (hash & 0x7fffffff);
}


int java_hash(void * ptr)
{
      assert(ptr);
       
      int hash = 0;

      char * char_ptr = (char *) ptr;
      while (*char_ptr) 
            hash = hash * 31 + *char_ptr++;
      
      return (hash & 0x7fffffff);
}