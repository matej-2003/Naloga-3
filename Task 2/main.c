#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// ascii grafika je nla kopirana iz spletne strani https://ascii.co.uk/art/hangman 14.1.2023
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

char* seznam_besed[] = {
	"bolezen", "čisto", "enolončnica", "epidemija", "fakulteta", "fingiran", "futuristično", "graciozen", "iskrena", "izjemen", "koalicija", "list",
	"madžarska", "moški", "mračno", "nadaljevati", "najmanj", "naključno", "odbor", "označeno", "parlament", "poreklo", "potovanja", "pravilo",
	"pregledati", "prestol", "previden", "previden", "prisega", "priznat", "propad", "razpakirati", "republika", "ročaj", "roka", "šepav",
	"september", "sestava", "široko", "slovenija", "smešno", "sodelovanje", "spektakularno", "strašljivo", "strmo", "upornik", "vbrizgati",
	"velikan", "volitve", "zadovoljivo", "zamenjati", "žilav", "zmešana", 
};

bool izpolni_besedo(char skrita_beseda[], char beseda[], char crka);
void izpisi_besedo(char skrita_beseda[]);
int str_len(char word[]);
bool preveri_napacen_vnos(char napacni_vnosi[], char crka);

int main() {
	srand(time(NULL));

	int index = rand() % (sizeof(seznam_besed) / sizeof(char*));
	char* beseda = seznam_besed[index];
	char* skrita_beseda = malloc(sizeof(char) * str_len(beseda));
	int i = 0;
	for (;beseda[i]!='\0'; i++)
		skrita_beseda[i] = '_';
	skrita_beseda[i + 1] = '\0';
	// strcpy(skrita_beseda, beseda);
	int stevilo_napacnih_vnosov = 0;
	char napacni_vnosi[127];
	
	do {
		char odgovor[10];
		char c;

		printf("Iskana beseda: ");
		izpisi_besedo(skrita_beseda);
		printf("\n");
		printf("Napacni vnosi: %s\n", napacni_vnosi);

		printf("%s\n\n", slikice[stevilo_napacnih_vnosov]);
		
		printf("Vnesi crko: ");
		fgets(odgovor, 10, stdin);
		fflush(stdin);
		if (sscanf(odgovor, "%c", &c) != 1) {
			break;
		}
		
		if (izpolni_besedo(skrita_beseda, beseda, c) == false && preveri_napacen_vnos(napacni_vnosi, c)) {
			printf("%i, %s\n", stevilo_napacnih_vnosov, napacni_vnosi);
			napacni_vnosi[stevilo_napacnih_vnosov] = c;
			napacni_vnosi[stevilo_napacnih_vnosov + 1] = '\0';
			stevilo_napacnih_vnosov++;
		}
	} while (stevilo_napacnih_vnosov < 10 && strcmp(beseda, skrita_beseda) != 0);

	printf("Iskana beseda: ");
	izpisi_besedo(beseda);
	printf("\n");

	// while (1) {
	// 	int index = rand() % (sizeof(seznam_besed) / sizeof(char*));
	// 	printf("%s\n", seznam_besed[index]);
	// 	sleep(0.1);
	// }
	// for (int i=0; i<10; i++) {
	// 	printf(slikice[i]);
	// 	fgets(0, 10, stdin);
	// }
}


bool izpolni_besedo(char skrita_beseda[], char beseda[], char crka) {
	bool vsebuje = false;
	for (int i=0; beseda[i] != '\0'; i++) {
		if (beseda[i] == crka) {
			skrita_beseda[i] = crka;
			vsebuje = true;
		}
	}
	return vsebuje;
}

bool preveri_napacen_vnos(char napacni_vnosi[], char crka) {
	for (int i=0; napacni_vnosi[i] != '\0'; i++)
		if (napacni_vnosi[i] == crka)	
			return false;
	return true;
}

void izpisi_besedo(char* skrita_beseda) {
	for (int i=0; skrita_beseda[i] != '\0'; i++)
		printf("%c ", skrita_beseda[i]);
}

int str_len(char word[]) {
	int i = 0;
	while (word[i]!='\0')
		i++;
	return i;
}