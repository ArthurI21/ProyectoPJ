#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define dinero 2000   //dinero inicial
#define a apuesta
 
void cambio(int m[])   // 0 1 2 3 pasan a |2| , 4 5 6 7 = |3| ,etc.
{
  int i,j,k,f=2;
 
  for (k=1;k<14;k++)
  {
    for (j=4*k-4;j<4*k;j++)
      for (i=0;i<52;i++)
        if (m[i]==j) m[i]=f;
    f++;
    }
}
 
void barajar(int m[])
{
    int r,i,temp;
    srand(time(NULL));
    for (i=0; i<52; i++) m[i] = i;
        for (i=0; i<(52-1); i++)
      {
            r = i + (rand() % (52-i));
            temp = m[i];
        m[i] = m[r];
        m[r] = temp;
      }
    cambio(m);
}
 
#include <string.h>

void conv(int n, char *out)
{
  int rank = n % 13 + 1;
  char rank_str[3];
  char suits[] = {'♦', '♣', '♠', '♥'}; // ♦♣♠♥
  char suit = suits[n / 13];

  switch(rank)
  {
    case 1: strcpy(rank_str, "A"); break;
    case 11: strcpy(rank_str, "J"); break;
    case 12: strcpy(rank_str, "Q"); break;
    case 13: strcpy(rank_str, "K"); break;
    default:
      snprintf(rank_str, sizeof(rank_str), "%d", rank);
  }
  snprintf(out, 5, "%s%c", rank_str, suit);
}

