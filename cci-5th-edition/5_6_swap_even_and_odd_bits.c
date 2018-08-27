static const uint32_t oddMask = 0xAAAAAAAA; //1010 1010 1010 ...
static const uint32_t evenMask = 0x55555555; //0101 0101 0101 ...

//brute force, operate on pair of bits

void swapEvenOddBits(uint32_t N)
{
  return (((N & oddMask) >> 1) | ((N & evenMask) << 1));
}
