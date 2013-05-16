int markZeroes(int matrix[][], int m, int n)
{
  int i,j;
  bool zeroRows[m], zeroCols[n];

  for(i = 0; i < m; i++)
  {
    for(j = 0; j < n; j++)
      {
	if(0 == matrix[i][j])
	  {
	    zeroRows[i] = true;
	    zeroCols[j] = true;
	  }
      }
  }
  return 0;
}
