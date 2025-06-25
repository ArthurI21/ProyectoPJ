#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DINERO_INICIAL 2000
#define MAX_CARTAS 10

typedef struct {
    int *mano;
    int cartas_en_mano;
    int total;
} Jugador;

void barajar(int mazo[]) {
    for (int i = 0; i < 52; i++) {
        mazo[i] = i;
    }
    srand(time(NULL));
    for (int i = 0; i < 51; i++) {
        int r = i + rand() % (52 - i);
        int temp = mazo[i];
        mazo[i] = mazo[r];
        mazo[r] = temp;
    }
}

void conv(int n, char *out) {
    int rank = n % 13 + 1;
    char suits[] = {'\x04', '\x05', '\x06', '\x03'}; // ♦♣♠♥
    char rank_str[3];

    switch (rank) {
        case 1: strcpy(rank_str, "A"); break;
        case 11: strcpy(rank_str, "J"); break;
        case 12: strcpy(rank_str, "Q"); break;
        case 13: strcpy(rank_str, "K"); break;
        default: sprintf(rank_str, "%d", rank);
    }

    sprintf(out, "%s%c", rank_str, suits[n / 13]);
}

int hand_value(int *hand, int count) {
    int total = 0, aces = 0;
    for (int i = 0; i < count; i++) {
        int rank = hand[i] % 13 + 1;
        if (rank == 1) {
            aces++;
            total += 11;
        } else if (rank > 10) {
            total += 10;
        } else {
            total += rank;
        }
    }
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    return total;
}

void guardar_historial(int apuesta, const char *resultado, int dinero_final) {
    FILE *f = fopen("historial.txt", "a");
    if (!f) {
        printf("No se pudo abrir historial.txt\n");
        return;
    }
    time_t now = time(NULL);
    fprintf(f, "Fecha: %s", ctime(&now));
    fprintf(f, "Apuesta: $%d, Resultado: %s, Dinero final: $%d\n\n", apuesta, resultado, dinero_final);
    fclose(f);
}

void esperar_enter() {
    printf("\nPresiona ENTER para continuar...\n");
    getchar(); getchar(); // limpiar buffer de scanf y esperar enter
}

void limpiar_pantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    int mazo[52], apuesta = 0, turno;
    long int dinero_total = DINERO_INICIAL;
    Jugador jugador, dealer;

    jugador.mano = malloc(sizeof(int) * MAX_CARTAS);
    dealer.mano = malloc(sizeof(int) * MAX_CARTAS);

    while (dinero_total > 0) {
        esperar_enter();
        barajar(mazo);
        limpiar_pantalla();

        printf("Tu dinero: $%ld\n", dinero_total);
        printf("Apuestas: Minimo:$100 Maximo: $5000\n");
        printf("Introduce tu apuesta: ");
        if (scanf("%d", &apuesta) != 1) {
            printf("Entrada invalida.\n");
            break;
        }

        if (apuesta < 100) apuesta = 100;
        else if (apuesta > 5000) apuesta = 5000;
        if (apuesta > dinero_total) apuesta = dinero_total;

        limpiar_pantalla();
        printf("Has apostado: $%d\n\n", apuesta);

        jugador.cartas_en_mano = dealer.cartas_en_mano = 2;
        jugador.mano[0] = mazo[0];
        jugador.mano[1] = mazo[1];
        dealer.mano[0] = mazo[51];
        dealer.mano[1] = mazo[50];
        turno = 2;

        while (1) {
            jugador.total = hand_value(jugador.mano, jugador.cartas_en_mano);
            dealer.total = hand_value(dealer.mano, dealer.cartas_en_mano);

            printf("Dealer muestra: ");
            char card_str[5];
            conv(dealer.mano[1], card_str);
            printf("|??| |%s|\n", card_str);

            printf("Tus cartas: ");
            for (int i = 0; i < jugador.cartas_en_mano; i++) {
                conv(jugador.mano[i], card_str);
                printf("|%s| ", card_str);
            }
            printf("\nTu suma: %d\n", jugador.total);

            if (jugador.total >= 21 || jugador.cartas_en_mano >= MAX_CARTAS)
                break;

            int decision = 0;
            printf("¿Quieres otra carta? (1 = si, 0 = no): ");
            if (scanf("%d", &decision) != 1 || decision == 0) break;

            jugador.mano[jugador.cartas_en_mano++] = mazo[turno++];
        }

        while (dealer.total < 17 && dealer.cartas_en_mano < MAX_CARTAS) {
            dealer.mano[dealer.cartas_en_mano++] = mazo[turno++];
            dealer.total = hand_value(dealer.mano, dealer.cartas_en_mano);
        }

        printf("\nCartas del dealer: ");
        for (int i = 0; i < dealer.cartas_en_mano; i++) {
            char card_str[5];
            conv(dealer.mano[i], card_str);
            printf("|%s| ", card_str);
        }
        printf("\nSuma del dealer: %d\n", dealer.total);

        printf("Tu suma: %d\n", jugador.total);

        if (jugador.total > 21) {
            printf("Te pasaste. Pierdes $%d\n", apuesta);
            dinero_total -= apuesta;
            guardar_historial(apuesta, "Perdio", dinero_total);
        } else if (dealer.total > 21 || jugador.total > dealer.total) {
            printf("¡Ganaste $%d!\n", apuesta);
            dinero_total += apuesta;
            guardar_historial(apuesta, "Gano", dinero_total);
        } else if (dealer.total == jugador.total) {
            printf("Empate.\n");
            guardar_historial(apuesta, "Empate", dinero_total);
        } else {
            printf("Pierdes $%d\n", apuesta);
            dinero_total -= apuesta;
            guardar_historial(apuesta, "Perdio", dinero_total);
        }
    }

    printf("\nTe has quedado sin dinero :'(\n");
    free(jugador.mano);
    free(dealer.mano);
    return 0;
}
