#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

const int PRITLICJE = 0;
const int KLET = -3;
const int MAX_STRING_LEN = 100;
const int STEVILO_NADSTROPJI = 5;

void izpisi_nadstropje(int n);
char* nadstropje(int n);
bool izstop();
int vnesi_destinacijo();
int preveri_vnos(char *str);

int main() {
	int trenutno_nadstropje = PRITLICJE;
	int destinacija;

	while (true) {
		printf("Trenutno nadstropje: %s\n", nadstropje(trenutno_nadstropje));
		destinacija = vnesi_destinacijo();

		if (destinacija - trenutno_nadstropje < 0) {
			for (;trenutno_nadstropje>destinacija; trenutno_nadstropje--)
				printf("%s->", nadstropje(trenutno_nadstropje));
		} else {
			for (;trenutno_nadstropje<destinacija; trenutno_nadstropje++)
				printf("%s->", nadstropje(trenutno_nadstropje));
		}
		printf("%s\n", nadstropje(trenutno_nadstropje));

		printf("Trenutno nadstropje: %s\n", nadstropje(trenutno_nadstropje));
		
		if (izstop()) {
			printf("Izstopili ste na %s nadstropju\n", nadstropje(trenutno_nadstropje));
			break;
		}
		printf("--------------------------\n\n");
	}
}
int preveri_vnos(char str[]) {
	// pravilen vnos je B3-B1, P, 1-5
	int n = 0;
	if ((str[0] == 'B' && sscanf(str, "B%i", &n) == 1) || (str[0] == 'B' && sscanf(str, "b%i", &n) == 1)) {
		return -n;
	} else if (str[0] == 'P' || str[0] == 'p') {
		return 0;
	} else if (sscanf(str, "%i", &n) == 1) {
		return n;
	}
	return KLET - 1;
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
	int destinacija = -1;
	char odgovor[3];
	do {
		printf("Vnesite destinacijo: ");
		fgets(odgovor, sizeof(odgovor), stdin);
		// sscanf(odgovor, "%i", &destinacija);
		fflush(stdin);
		destinacija = preveri_vnos(odgovor);

		if (destinacija >= KLET && destinacija <= STEVILO_NADSTROPJI) 
			return destinacija;
		else
			printf("Napaka: vnesete lahko samo stevila od %i do %i, P-pritlicje in B1, B2, B3 za klet\n", 1, STEVILO_NADSTROPJI);
			// break;
	} while (true);
}

void izpisi_nadstropje(int n) {
	if (n < 0)
		printf("B%i", -n);
	else if (n == 0) {
		printf("P");
	} else {
		printf("%i", n);
	}
}

char* nadstropje(int n) {
	char* str = malloc(3 * sizeof(char));
	if (n < 0) {
		sprintf(str, "B%i", -n);
	} else if (n == 0) {
		sprintf(str, "P");
	} else {
		sprintf(str, "%i", n);
	}
	return str;
}