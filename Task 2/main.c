#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// ascii grafika je nla kopirana iz spletne strani https://ascii.co.uk/art/hangman 14.1.2023
char* slikice[] = {
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

char* besede[] = {
	"volitve", "poreklo", "enolončnica", "zadovoljivo", "naključno", "upornik", "strašljivo", "vbrizgati", "graciozen", "razpakirati", "velikan", "nadaljevati",
	"ročaj", "smešno", "iskrena", "izjemen", "previden", "fingiran", "moški", "previden", "propad", "šepav", "spektakularno", "futuristično", "žilav", "prestol",
	"roka", "potovanja", "mračno", "list", "čisto", "široko", "sodelovanje", "odbor", "fakulteta", "parlament", "sestava", "koalicija", "republika", "slovenija",
	"prisega", "epidemija", "bolezen", "september", "najmanj", "madžarska", "zamenjati", "označeno", "pregledati", "pravilo", "strmo", "zmešana", "priznati"
};

int main() {
	srand(time(NULL));

	while (1) {
		int index = rand() % (sizeof(besede) / sizeof(char*));
		printf("%s\n", besede[index]);
		sleep(0.1);
	}
	// for (int i=0; i<10; i++) {
	// 	printf(slikice[i]);
	// 	fgets(0, 10, stdin);
	// }
}