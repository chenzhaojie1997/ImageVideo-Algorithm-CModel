#include "../../comm/comm.h"

int main() {
   const char* name = "D:\\learn\\project\\github\\ImageVideo-Algorithm-CModel\\data\\set14\\man.bmp";
   int height = 512;
   int width  = 512;

   BOOL bState = SUCCESS;

   char* data = (char*)malloc(height * width * 3 * sizeof(char));
   if (NULL == data) {
      printf("[ERROR]: @main data null\n");
      return FAILURE;
   }

   bState = ReadBmp(data, name, height, width);
   bState = WriteBmp(data, "D:\\learn\\project\\github\\ImageVideo-Algorithm-CModel\\run\\test\\test.bmp", height, width);
   printf("%d\n", bState);
   return SUCCESS;
}