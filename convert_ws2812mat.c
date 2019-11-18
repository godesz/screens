#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define size_m 8

int convert_xy2l(int x, int y)
{
int value = 0;
value += y * size_m + ((y%2)?7-x:x);
//if (y%2 == 0) value += x;
//else value += (7-x);
return value;
}

int main()
{
srand(time(NULL));
int a = rand()%9, b = rand()%9;

for(b=0;b<8;b++)
for(a=0;a<8;a++)
printf("(%d,%d) to %d\n", a, b, convert_xy2l(a,b)); 


return 0;
}
