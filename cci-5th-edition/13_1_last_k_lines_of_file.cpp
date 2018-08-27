#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

static const int last_k_lines = 3;
static char *all_lines[last_k_lines] = {NULL};

static int init_storage(void)
{
  for(int i = 0; i < last_k_lines; ++i)
    {
      all_lines[i] = (char *)malloc(128);
    }
  return 0;
}

static int shift_lines_up(void)
{
  for(int i = 1; i < last_k_lines; ++i)
    {
      printf("copying line %d to line %d\n",
	     i, i-1);
      strncpy(all_lines[i - 1], all_lines[i], 128);
    }
  return 0;
}

static int store_line(const char *line, int count)
{
  printf("storing line %d\n", count);
  if(count < last_k_lines)
    {
      strncpy(all_lines[count], line, 128);
    }
  else
    {
      shift_lines_up();
      strncpy(all_lines[last_k_lines - 1], line, 128);
    }
  return 0;
}

static int print_lines(void)
{
  for(int i = 0; i < last_k_lines; ++i)
    {
      printf("%s", all_lines[i]);
    }
  return 0;
}

int main()
{
  init_storage();

  //get filename 
  FILE *f = fopen("notes.txt", "r");
  char line[128] = "";

  if(NULL != f)
    {
      int count = 0;
      while(NULL != fgets(line, sizeof(line), f))
	{
	  store_line(line, count);
	  count++;
	}
      fclose(f);
      f = NULL;
    }

  print_lines();

  return 0;
}
