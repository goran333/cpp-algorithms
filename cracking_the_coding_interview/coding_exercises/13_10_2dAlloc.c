int **my2dAlloc(int rows, int cols)
{
  int **2dptr = NULL;

  2dptr = malloc(rows * sizeof(int *));
  for(int i = 0; i < rows; ++i)
    {
      2dptr[i] = malloc(cols * sizeof(int));
    }

  return (2dptr);
}

void my2dFree(int **2dptr, int rows)
{
  if(NULL != 2dptr)
    {
      for(int i = 0; i < rows; ++i)
	{
	  free(2dptr[i]);
	  2dptr[i] = NULL;
	}
      free(2dptr);
      2dptr = NULL;
    }
}
