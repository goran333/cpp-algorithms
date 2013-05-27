int noOfBitsRequired(uint32_t N, 
		     uint32_t M)
{
  int count = 0;
  uint32_t temp = N ^ M;
  
  while(temp != 0)
    {
      if(temp & 1)
	count++;

      temp >>=1;
    }

  return (count);
}
