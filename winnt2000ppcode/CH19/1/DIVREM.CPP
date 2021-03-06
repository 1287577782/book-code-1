====================== Listing 6 ======================
int divrem(int *u, int v, int m); // divrem prototype

char* LargeInt::binToDec(char* dest, int lim) const {
   LargeInt copy = *this;   // convert this copy
   int* copyAdr = copy.adr; // this will be changed
   int copyLen  = copy.len; // this will be changed
   int binDec; // holds one 10^PackFactor binary digit
   char* initDest = dest;
   int blkCnt, i, j;

   // special case of 0
   if (sign == 0) {
      strcpy(dest, "0");
      return initDest;
   }
   // convert to string in blocks of PackFactor
   blkCnt = 0;
   while (*copyAdr != 0  ||  copyLen > 1) {
      binDec = divrem(copyAdr, intTenTo9, copyLen);
      if (copyLen > 1  &&  *copyAdr == 0) {
         copyAdr++;
         copyLen--;
      }
      if (lim - (PackFactor + 1) > 0) { // 1 for '\0'
         sprintf(dest, "%09u", binDec);
         lim  -= PackFactor;
         dest += PackFactor;
      }
      else
         return 0; // short of room for output string
      blkCnt++;
   } // on exit, dest points at null byte
   lim--; // account for the null byte

   // swap output in blkCnt groups of size PackFactor
   i = 0; // subscript of beginning of 1st block
   j = (blkCnt - 1) * PackFactor; // last block
   blkCnt &= -2; // only need an even number of swaps
   while (blkCnt > 1) {
      swap9(initDest + i, initDest + j);
      blkCnt -= 2;
      i += PackFactor;
      j -= PackFactor;
   }
//
// Code to remove leading zeros and possibly insert
// minus sign belongs here
//
   return initDest;
}

inline void swap9(char* s1, char* s2) {
   char hold;

   for (int i = 0; i < PackFactor; i++) {
      hold  = s1[i];
      s1[i] = s2[i];
      s2[i] = hold;
   }
}
