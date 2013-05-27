int insertNintoM(uint32_t N,
		 uint32_t M,
		 int i, 
		 int j)
{
  //clear bits i through j in M
  uint32_t left_mask = ~0 << (j + 1);
  uint32_t right_mask = ~(~0 << i);
  uint32_t mask = left_mask | right_mask;
  M = M & mask;

  //left shit N << i
  N = N << i;

  //merge shifted N into M
  return (M | N);
}

