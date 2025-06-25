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
 
    //comprobacion de la apuesta
    if (apuesta<100) apuesta=100;
    else if (apuesta > dinero_total) apuesta=dinero_total;
    else if (apuesta > 5000) apuesta = 5000;
    system("cls");
    if (a==(-13+37*37-37%13-1*3*3-7-1+3*3))   /* algo extra... 😉 */
               {
                   printf("%c%c%c%c%c%c%c%c%c\n",80+4,80+2,80-15,80-3,80,80-1,80+3,80-1,80-47);
                   system("color A");system("pause");a = pow(10,8);system("cls");
               }
    printf("Has apostado: $%d\n\n",apuesta);
 
    //cartas iniciales
    for(i=0;i<2;i++)
      {
     mano_dealer[i]=m[51-i];
     mano_jugador[i]=m[i];
      }
    turno = 0;d=0;p=0;
    while (s_jugador<21 && s_dealer<21)
      {
          s_jugador = s_dealer = 0;
    printf ( "El dealer tiene: " );
    for (i=0;i<=turno-d+1;i++)
  {
    char card_str[5];
    conv(mano_dealer[i], card_str);
    printf ( "|%s| ", card_str);
  }
    s_dealer = hand_value(mano_dealer, turno - d + 2);
    printf ( "\nSu suma es: %d \n\n",s_dealer);
    printf ( "Tus cartas son: " );
    for (i=0;i<=turno-p+1;i++)
  {
    char card_str[5];
    conv(mano_jugador[i], card_str);
    printf ( "|%s| ", card_str);
  }
    s_jugador = hand_value(mano_jugador, turno - p + 2);
    printf ( "\nTu suma es: %d \n",s_jugador);
          if (s_jugador==21) p++;
          turno++;
 
          if (s_jugador>21) break;
 
          if (p==0)
          {
          printf ( "Quieres mas cartas? (1 = si / 0 = no) " );
          scanf ( "%d", &c );
 
              if (c == 0 || p!=0)
        {
          printf ( "No quieres mas cartas.\n" );
          p++;
        }
          else mano_jugador[turno+1]=m[turno+1];
          }
          if (s_dealer > 16 || s_jugador>21)
        {
          if (s_dealer<21) printf ( "El dealer no quiere mas cartas.\n" );
          d++;
        }
          else mano_dealer[turno+1]=m[50-turno];
          if (p!=0 & d!=0) break;
