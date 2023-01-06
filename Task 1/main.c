#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

const int PRITLICJE = 0;
const int KLET = -3;
const int MAX_STRING_LEN = 100;
const int STEVILO_NADSTROPJI = 5;

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
		
		// if (izstop()) {
		// 	printf("Izstopili ste na %s nadstropju\n", nadstropje(trenutno_nadstropje));
		// 	break;
		// }
		printf("--------------------------\n\n");
	}
}


// funkcija vrne stevilo od [KLET, STEVILO_NADSTROPJI] = [-3, 5]
// ko je napacen vnos vrne stevilo manjse stevilo od KLET oz. KLET-1, zato da pogoj veljavnosti vnosa v funkciji
// vnesi_destinacijo spodleti, kar pomeni, da funkcija ponovno vprasa uporabnika za vnos
int preveri_vnos(char str[]) {
	// pravilen vnos je B3-B1, P, 1-5
	// preveri če je vnost P ali p
	if (str[0] == 'P' || str[0] == 'p')
		return 0;
	
	int n = 0;
	// preveri vnost za klet od B1, B2, B3
	// int n - pridobi s sscanf in preveri če je me v intevalu [1, KLET]
	if (
		(str[0] == 'B' && sscanf(str, " B%i", &n) == 1) ||	// preveri ce je prvi znak v vnosu 'B' in ce je najdi stevilo, ki mu sledi
		(str[0] == 'b' && sscanf(str, " b%i", &n) == 1)		// preveri ce je prvi znak v vnosu 'b' in ce je najdi stevilo, ki mu sledi
	)
	{
		if (n > 0 && n <= -KLET)	// stevilo, ki mu sledi je pozitivno stevilo v intevalu (0, -KLET], B0 - je neveljaven vnos, ker je nadstropje 0 - oznaceno z znakoma 'P' ali 'p'
			return -n;	// vrni -n, ker funkcija vnesi_destinacijo pricakuje stevilo, ki je v intevalu [KLET, STEVILO_NADSTROPJI] oz. [-3, 5]
		else
			return KLET-1;	// če zgornji pogoj ni izpolnjen vrni stevilo, ki je manjse od KLET oz. KLET-1 -||-
	}
	// ta pogoj se izvede samo, če nista bila izpolnjena prejsna pogoja
	// preveri, če je vnos stevilo, ki je v intervalu [1, STEVILO_NADSTROPJI]
	if (sscanf(str, " %i", &n) == 1 && n > 0 && n <= STEVILO_NADSTROPJI)
		return n;
	
	// če nobeden izmed pogojev ni bil izpolnjen vrni stevilo, ki je manjse od KLET oz. KLET-1 -||-
	return -(KLET + 1);
}

// funkcija vprasa uporabnika, če želi izsopit
// veljaven odgovor je lahko samo DA, Da, da ali NE, Ne, ne
// če uporabni, ne zeli izstopiti lahko samo klikne ENTER in se bo program naprej izvajal
bool izstop() {
	// 
	char odgovor[MAX_STRING_LEN];	// size of odgovor 3 = 2 * char + \0
	while (true) {
		printf("Ali zelite izstopiti: ");
		// uporabljam funkcijo fgets namesto scanf("%s", odgovor);, ker dopusca, da lahko uporabnik vnese samo ENTER in funkcija ne caka na vnos
		fgets(odgovor, sizeof(odgovor), stdin);	// beri vnos iz STDIN in zapisi v spremenljivko odgovor
		fflush(stdin);
		if (!strcmp(odgovor, "da") || !strcmp(odgovor, "DA") || !strcmp(odgovor, "Da")) {
			return true;
		} else if (!strcmp(odgovor, "ne") || !strcmp(odgovor, "NE") || !strcmp(odgovor, "Ne") || !strcmp(odgovor, "")) {
			return false;
		} else {
			printf("Veljaven odgovor: [DA/NE]\n");
		}
	}
}

// ta fukcija vprasa uporabnika po destinaciji oz. 
int vnesi_destinacijo() {
	int destinacija = KLET-1;
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

// ta funkcija prejme stevilo nadstropja in vrne pradstavitev nadstropju v char* oz. vrne string
char* nadstropje(int n) {
	char* str = malloc(5 * sizeof(char));	// dinamicno ustvari char[] veliko 5, da je zadosti veliko
	// uporabi fukcijo sprintf, ki deluje kot printf samo da ne izpise v STDOUT ampak shrani v str
	if (n < 0) sprintf(str, "B%i", -n);	// če je n, manjsi od 0, je dvigalo v kleti in se nadstropja izpisejo z Bn
	else if (n == 0) sprintf(str, "P");	// če je n enak 0 je dvigalo v pretlicju in izpise z P
	else sprintf(str, "%i", n);	// ko je n vecji od 0 izpisi samo stevilo
	return str;
}