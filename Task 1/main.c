#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include<stdlib.h>

const int PRITLICJE = 0;
const int MAX_STRING_LEN = 100;
const int STEVILO_NADSTROPJI = 5;

bool izstop();
int vnesi_destinacijo();

int main() {
	int trenutno_nadstropje = PRITLICJE;
	int destinacija;

	while (true) {
		printf("Trenutno nadstropje: %i\n", trenutno_nadstropje);
		destinacija = vnesi_destinacijo();

		if (destinacija - trenutno_nadstropje < 0) {
			for (;trenutno_nadstropje>destinacija; trenutno_nadstropje--)
				printf("%i->", trenutno_nadstropje);
		} else {
			for (;trenutno_nadstropje<destinacija; trenutno_nadstropje++)
				printf("%i->", trenutno_nadstropje);
		}
		printf("%i\n", trenutno_nadstropje);

		printf("Trenutno nadstropje: %i\n", trenutno_nadstropje);
		
		if (izstop()) {
			printf("Izstopili ste na %i nadstropju\n", trenutno_nadstropje);
			break;
		}
		// else {
		// 	printf("Vstop...\n");
		// }
	}
}

bool izstop() {
	char odgovor[3];	// size of odgovor 3 = 2 * char + \0
	while (true) {
		printf("Ali zelite izstopiti: ");
		// scanf("%s", odgovor);
		fgets(odgovor, sizeof(odgovor), stdin);
		fflush(stdin);
		if (!strcmp(odgovor, "da") || !strcmp(odgovor, "DA") || !strcmp(odgovor, "Da")) {
			return true;
		} else if (!strcmp(odgovor, "ne") || !strcmp(odgovor, "NE") || !strcmp(odgovor, "Ne")) {
			return false;
		} else {
			printf("Veljaven odgovor: [DA/NE]\n");
		}
	}
}

int vnesi_destinacijo() {
	int destinacija;
	do {
		printf("Vnesite destinacijo: ");
		scanf("%i", &destinacija);
		fflush(stdin);

		if (destinacija >= PRITLICJE && destinacija <= STEVILO_NADSTROPJI) 
			return destinacija;
		else
			printf("Napaka: vnesete lahko samo stevilo med %i in %i\n", PRITLICJE, STEVILO_NADSTROPJI);
			// break;
	} while (true);
}