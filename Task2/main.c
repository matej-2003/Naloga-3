#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


#define MAX_STRING_LEN 100

// 1. ascii grafika je kopirana iz spletne strani https://ascii.co.uk/art/hangman 14.1.2023
char slikice[10][16 * 8] = {
	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"________      \n",

	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"              \n"
	"__/|\\__      \n",

	"              \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"__/|\\__      \n",

	"   ________   \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"__/|\\__      \n",

	"   ________   \n"
	"   |/         \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"__/|\\__      \n",

	"   ________   \n"
	"   |/     |   \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"__/|\\__      \n",

	"   ________   \n"
	"   |/     |   \n"
	"   |     (_)  \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"   |          \n"
	"__/|\\__      \n",

	"   ________   \n"
	"   |/     |   \n"
	"   |     (_)  \n"
	"   |      |  \n"
	"   |      |   \n"
	"   |          \n"
	"   |          \n"
	"__/|\\__      \n",

	"   ________   \n"
	"   |/     |   \n"
	"   |     (_)  \n"
	"   |     \\|/ \n"
	"   |      |   \n"
	"   |          \n"
	"   |          \n"
	"__/|\\__      \n",

	"   ________   \n"
	"   |/     |   \n"
	"   |     (_)  \n"
	"   |     \\|/ \n"
	"   |      |   \n"
	"   |     / \\ \n"
	"   |          \n"
	"__/|\\__      \n",
};

// 38 moznih besed, ki jih program nakjucno izbere
// program je char pointer array, ker so besede razlicne dolzine in string array ni mogoc
char *seznam_besed[] = {
	"bolezen",
	"epidemija",
	"fakulteta",
	"fingiran",
	"graciozen",
	"iskrena",
	"izjemen",
	"koalicija",
	"list",
	"nadaljevati",
	"najmanj",
	"odbor",
	"zadovoljivo",
	"republika",
	"roka",
	"september",
	"sestava",
	"slovenija",
	"sodelovanje",
	"spektakularno",
	"strmo",
	"upornik",
	"vbrizgati",
	"velikan",
	"volitve",
	"zamenjati",
	"parlament",
	"poreklo",
	"potovanja",
	"pravilo",
	"pregledati",
	"prestol",
	"previden",
	"previden",
	"prisega",
	"priznat",
	"propad",
	"razpakirati",
};


char* pridobi_skrito_besedo(char beseda[]);
bool izpolni_besedo(char skrita_beseda[], char beseda[], char crka);
void izpisi_besedo(char skrita_beseda[]);
int str_len(char word[]);
bool preveri_napacen_vnos(char napacni_vnosi[], char crka);
void izpisi_napacne_vnose(char napacni_vnosi[]);


int main() {
	srand(time(NULL));

	int index = rand() % (sizeof(seznam_besed) / sizeof(char *)); // pridobi random stevilo med 0 in dolzino seznama besed
	char* beseda = seznam_besed[index];						  // nakljucna beseda
	// skrita beseda je char array eneke velikosti, kot beseda, program dinamicno pridobi spomin, ker je beseda nakljucno izbrana
	char* skrita_beseda = pridobi_skrito_besedo(beseda);

	// strcpy(skrita_beseda, beseda);
	int stevilo_napacnih_vnosov = 0;
	char* napacni_vnosi = malloc(sizeof(char) * MAX_STRING_LEN); // string, ki hrani napacne znake
	napacni_vnosi[0] = '\0';

	do {
		char odgovor[10];
		char c;

		printf("Iskana beseda: ");
		izpisi_besedo(skrita_beseda);
		printf("\nNapacni vnosi: %s\n", napacni_vnosi);
		printf("%s\n\n", slikice[stevilo_napacnih_vnosov]);
		printf("Vnesi crko: ");
		fgets(odgovor, 10, stdin);
		fflush(stdin);
		if (sscanf(odgovor, " %c", &c) != 1) {
			break;
		}

		if (izpolni_besedo(skrita_beseda, beseda, c) == false && preveri_napacen_vnos(napacni_vnosi, c)) {
			printf("Stevilo napacnih vnosov: %i, %s\n", stevilo_napacnih_vnosov + 1, napacni_vnosi);
			napacni_vnosi[stevilo_napacnih_vnosov] = c;
			napacni_vnosi[stevilo_napacnih_vnosov + 1] = '\0';
			stevilo_napacnih_vnosov++;
		}

		if (strcmp(beseda, skrita_beseda) == 0) {
			printf("---------------------\n");
			printf("|       ZMAGA!      |\n");
			printf("---------------------\n");
			break;
		} else if (stevilo_napacnih_vnosov >= 9) {
			printf("---------------------\n");
			printf("|    KONEC IGRE!    |\n");
			printf("---------------------\n");
			break;
		}
	} while (true);

	printf("Iskana beseda: %s\n", beseda);
	free(skrita_beseda);
}

// vrne string skrita_beseda, ki jo dobi iz beseda
char* pridobi_skrito_besedo(char *beseda) {
	char *skrita_beseda = malloc(sizeof(char) * str_len(beseda)); // skrita beseda je prikazana beseda, ki jo uporabnik isce
	int i = 0;
	for (; i < str_len(beseda); i++)
		skrita_beseda[i] = '_';	 // zanka gre skozi vse crke v izbrani besedi in nastavi znake v skriti_besedi na '_'
	skrita_beseda[i + 1] = '\0'; // nastavi zadni znak na '\0', ki zaznamuje konec stringa
	return skrita_beseda;
}

bool izpolni_besedo(char skrita_beseda[], char beseda[], char crka) {
	bool vsebuje = false;
	for (int i = 0; beseda[i] != '\0'; i++) {
		if (beseda[i] == crka) {
			skrita_beseda[i] = crka;
			vsebuje = true;
		}
	}
	return vsebuje;
}

void izpisi_napacne_vnose(char napacni_vnosi[]) {
	for (int i = 0; napacni_vnosi[i] != '\0'; i++)
		printf("%c, ", napacni_vnosi[i]);
}

// true - vnos je napacen
bool preveri_napacen_vnos(char napacni_vnosi[], char crka) {
	if (crka >= 'A' && crka <= 'Z') // ce je crka celika pretvori v majhno
		crka += 32;
	if (crka < 'a' && crka > 'z') // preveri ce je ni crka me a in z
		return true;
	for (int i = 0; napacni_vnosi[i] != '\0'; i++)
		if (napacni_vnosi[i] == crka)
			return false;
	return true;
}

void izpisi_besedo(char *skrita_beseda) {
	for (int i = 0; skrita_beseda[i] != '\0'; i++)
		printf("%c ", skrita_beseda[i]);
}

int str_len(char word[]) {
	int i = 0;
	while (word[i] != '\0')
		i++;
	return i;
}