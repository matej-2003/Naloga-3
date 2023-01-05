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
	"volitve", "poreklo", "enolončnica", "zadovoljivo", "naključno", "upornik", "strašljivo", "vbrizgati", "graciozen", "razpakirati", "velikan", "nadaljevati",
	"ročaj", "smešno", "iskrena", "izjemen", "previden", "fingiran", "moški", "previden", "propad", "šepav", "spektakularno", "futuristično", "žilav", "prestol",
	"roka", "potovanja", "mračno", "list", "čisto", "široko", "sodelovanje", "odbor", "fakulteta", "parlament", "sestava", "koalicija", "republika", "slovenija",
	"prisega", "epidemija", "bolezen", "september", "najmanj", "madžarska", "zamenjati", "označeno", "pregledati", "pravilo", "strmo", "zmešana", "priznati"
};

bool izpolni_besedo(char* skrita_beseda, char* beseda, char crka);
void izpisi_besedo(char* skrita_beseda);
int str_len(char word[]);

int main() {
	srand(time(NULL));

	int index = rand() % (sizeof(seznam_besed) / sizeof(char*));
	char* beseda = seznam_besed[0];
	char* skrita_beseda = malloc(sizeof(char) * str_len(beseda));
	for (int i=0; beseda[i]!='\0'; i++)
		skrita_beseda[i] = '_';
	// strcpy(skrita_beseda, beseda);
	int stevilo_napacnih_vnosov = 0;
	char napacni_vnosi[127];


	char odgovor[10];
	
	do {
		char c;

		printf("Iskana beseda: ");
		izpisi_besedo(skrita_beseda);
		printf("\n");
		printf("Napacni vnosti: %s\n", napacni_vnosi);

		printf("%s\n\n", slikice[stevilo_napacnih_vnosov]);
		
		printf("Vnesi crko: ");
		fgets(odgovor, 10, stdin);
		if (sscanf(odgovor, "%c", &c) != 1) {
			continue;
		}
		fflush(stdin);
		
		if (izpolni_besedo(skrita_beseda, beseda, c) == false) {
			stevilo_napacnih_vnosov++;
			napacni_vnosi[stevilo_napacnih_vnosov] = c;
		}
	} while (stevilo_napacnih_vnosov < 10 && strcmp(beseda, skrita_beseda) != 0);

	printf("Iskana beseda: ");
	izpisi_besedo(skrita_beseda);
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


bool izpolni_besedo(char* skrita_beseda, char* beseda, char crka) {
	bool vsebuje = false;
	for (int i=0; beseda[i] != '\0'; i++) {
		if (beseda[i] == crka) {
			skrita_beseda[i] = crka;
			vsebuje = true;
		}
	}
	return vsebuje;
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