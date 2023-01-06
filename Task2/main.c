#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_STRING_LEN 100
#define STEVILO_POSKUSOV 10

// CRKE PO STEVILU POJEVITEV: a: 38, e: 30, i: 27, o: 23, r: 22, n: 19, l: 17, p: 17, t: 17, v: 13, j: 11, k: 11, s: 11, z: 8, d: 8, m: 7, b: 5, g: 5, u: 4, f: 2, c: 2
// NAJBOLJSA RESITEV: aeiornlpt
// NAJSLABSA RESITEV: xqwyvjkszdmbgufc

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
	"   |      |   \n"
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

// 37 moznih besed, ki jih program nakjucno izbere
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
	"prisega",
	"priznat",
	"propad",
	"razpakirati",
};


char* pridobi_skrito_besedo(char beseda[]);
bool izpolni_besedo(char skrita_beseda[], char beseda[], char crka);
void izpisi_iskano_besedo(char skrita_beseda[]);
int str_len(char word[]);
bool dovoljen_znak(char znak);
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

	while (true) {
		char odgovor[10];
		char c;
	
		printf("Stevilo poskusov: %i\n", STEVILO_POSKUSOV);
		printf("Preostali poskusi: %i\n", STEVILO_POSKUSOV - stevilo_napacnih_vnosov);
		printf("Napacni vnosi: %i, %s\n", stevilo_napacnih_vnosov, napacni_vnosi);
		printf("Iskana beseda: ");
		izpisi_iskano_besedo(skrita_beseda);
		// slikica
		printf("\n%s\n\n", slikice[stevilo_napacnih_vnosov]);
		printf("Vnesi crko: ");
		scanf(" %c", &c);
		fflush(stdin);

		// pogoj izpolnjen ce je crka dovoljen znak IN ce crka ni v besedi IN ce je crka ze med napacnimi vnosi
		if (dovoljen_znak(c)) {
			if (izpolni_besedo(skrita_beseda, beseda, c) == false && preveri_napacen_vnos(napacni_vnosi, c)) {
				napacni_vnosi[stevilo_napacnih_vnosov] = c;
				napacni_vnosi[stevilo_napacnih_vnosov + 1] = '\0';
				stevilo_napacnih_vnosov++;
			}
		} else {
			printf("NAPACEN VNOS!\n");
		}

		if (strcmp(beseda, skrita_beseda) == 0) {
			printf("\n---------------------\n");
			printf("|       ZMAGA!      |\n");
			printf("---------------------\n");
			break;
		} else if (stevilo_napacnih_vnosov == STEVILO_POSKUSOV) {
			printf("\n---------------------\n");
			printf("|    KONEC IGRE!    |\n");
			printf("---------------------\n");
			break;
		}
		printf("\n\n");
	}

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

bool dovoljen_znak(char znak) {
	if (znak >= 'A' && znak <= 'Z') // ce je znak velika pretvori v majhno
		znak += 32;
	if (!(znak >= 'a' && znak <= 'z')) // preveri ce je ni znak me 'a' in 'z'
		return false;
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
	for (int i = 0; napacni_vnosi[i] != '\0'; i++)
		if (napacni_vnosi[i] == crka)
			return false;
	return true;
}

void izpisi_iskano_besedo(char *skrita_beseda) {
	for (int i = 0; skrita_beseda[i] != '\0'; i++)
		printf("%c ", skrita_beseda[i]);
}

// vrne dolzino stringa
int str_len(char word[]) {
	int i = 0;
	while (word[i] != '\0')
		i++;
	return i;
}