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

// Calculate hand value considering Ace as 1 or 11
int hand_value(int hand[], int count)
{
  int total = 0;
  int aces = 0;
  for (int i = 0; i < count; i++)
  {
    int rank = hand[i] % 13 + 1;
    if (rank == 1)
    {
      aces++;
      total += 11;
    }
    else if (rank > 10)
      total += 10;
    else
      total += rank;
  }
  while (total > 21 && aces > 0)
  {
    total -= 10;
    aces--;
  }
  return total;
}
 
int main()
{
  int m[52],s_jugador=0,s_dealer=0,apuesta=0,c,i;
  int mano_jugador[10],mano_dealer[10],turno,d,p;
  long int dinero_total=dinero;
   while (1)
      {
    system("pause");
    barajar(m);
    system("cls");
    s_dealer=0;s_jugador=0;
    printf ( "Tu dinero: $%d \n", dinero_total );
    printf ( "________________\n");
    if (dinero_total <= 0) break;
    printf ( "Apuestas: Minimo:$100 Maximo: $5000 \n\n" );
    printf ( "Introduce tu apuesta: " );
    scanf ( "%d", &apuesta );
