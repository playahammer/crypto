#include "strhash.h"

int main(int argc, char **argv)
{
      char *test_str = "123";
      printf("Test value: %s\n", test_str);
      printf("BKDRHash: %d\n", bkdr_hash(test_str));
      printf("APHash: %d\n", ap_hash(test_str));
      printf("JSHash: %d\n", js_hash(test_str)); 
      printf("RSHash: %d\n", rs_hash(test_str));
      printf("SDBMHash: %d\n", sdbm_hash(test_str));
      printf("PWJHash: %d\n", pjw_hash(test_str));
      printf("ELFHash: %d\n", elf_hash(test_str));
      printf("DJBHash: %d\n", djb_hash(test_str));
      printf("DEKHash: %d\n", dek_hash(test_str, 3));
      printf("BPHash: %d\n", bp_hash(test_str, 3));
      printf("FNVHash: %d\n", fnv_hash(test_str));
      printf("JAVAHash: %d\n", java_hash(test_str));
      
      return 0;
}