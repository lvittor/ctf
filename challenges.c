#include "challenges.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#define PI 3.14159265

static const char *challenge_header = "------------- DESAFIO -------------",
		  *research_header = "----- PREGUNTA PARA INVESTIGAR -----";

static const char *string_for_challenge_5 = "too_easy";
static const int DUMMY __attribute__((section(".RUN_ME")));
static const char *COW =
	"_______________________\n< ESTO ES UN EASTER_EGG >\n-----------------------\n     \\  ^__^\n    \\  (oo)\\_______\n        (__)\\       )\\/\\ \n            ||----w |\n            ||     ||";
static const char *GOODBYE_MESSAGE =
	"Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto";

static void fd13_challenge(void);
static void filter_challenge(void);
static void quine_challenge(void);
static void normal_challenge(void);
static void b_black_challenge(void);
static void gdbme_challenge(void);

static challenge_t challenges[CHALLENGES_NUMBER] = {
	{
		.hint = "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\nDeberán estar atentos a los easter eggs.\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'",
		.challenge = NULL,
		.research =
			"¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
		.ans = "entendido\n",
	},
	{
		.hint = "The Wire S1E5\n5295 888 6288\n",
		.challenge = NULL,
		.research =
			"¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
		.ans = "itba\n",
	},
	{
		.hint = "https://ibb.co/tc0Hb6w\n",
		.challenge = NULL,
		.research =
			"¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?",
		.ans = "M4GFKZ289aku\n",
	},
	{
		.hint = "EBADF... \n",
		.challenge = fd13_challenge,
		.research =
			"¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
		.ans = "fk3wfLCm3QvS\n",
	},
	{
		.hint = "respuesta = strings:98\n",
		.challenge = NULL,
		.research =
			"¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
		.ans = "too_easy\n",
	},
	{
		.hint = ".got .got.plt .data ? .bss .comment .debug_aranges\n",
		.challenge = NULL,
		.research =
			"Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?",
		.ans = ".RUN_ME\n",
	},
	{
		.hint = "Filter error\n",
		.challenge = filter_challenge,
		.research =
			"¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
		.ans = "K5n2UFfpFMUN\n",
	},
	{
		.hint = "¿? \n",
		.challenge = b_black_challenge,
		.research =
			"¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?",
		.ans = "BUmyYq5XxXGt\n",
	},
	{
		.hint = "Latexme\n\nSi\n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\\frac{u'}{u})\nentonces\ny = \n",
		.challenge = NULL,
		.research =
			"Sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?",
		.ans = "u^v\n",
	},
	{
		.hint = "quine\n",
		.challenge = quine_challenge,
		.research =
			"¿Cuáles son las características del protocolo SCTP?",
		.ans = "chin_chu_lan_cha\n",
	},
	{
		.hint = "b gdbme y encontrá el valor mágico\n",
		.challenge = gdbme_challenge,
		.research = "¿Qué es un RFC?",
		.ans = "gdb_rules\n",
	},
	{
		.hint = "Me conoces\n",
		.challenge = normal_challenge,
		.research = "¿Se divirtieron?",
		.ans = "normal\n",
	}
};

static void clear_screen(void)
{
	printf("\e[1;1H\e[2J");
}

void run_challenges(FILE *input)
{
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	ssize_t line_size;

	for (int i = 0; i < CHALLENGES_NUMBER; i++) {
		int ans;
		do {
			clear_screen();
			printf("%s\n%s\n\n", challenge_header,
			       challenges[i].hint);
			if (challenges[i].challenge != NULL)
				challenges[i].challenge();
			if (challenges[i].research != NULL) {
				printf("%s\n%s\n\n", research_header,
				       challenges[i].research);
			}
			line_size = getline(&line_buf, &line_buf_size, input);
			if (line_size == -1)
				return;
			ans = strcmp(line_buf, challenges[i].ans);
			if (ans != 0) {
				printf("La respuesta '%s' es incorrecta\n",
				       line_buf);
				sleep(2);
			}
		} while (ans != 0);
	}
	clear_screen();
	printf("%s\n", GOODBYE_MESSAGE);
}

static void fd13_challenge(void)
{
	int ret = write(13, "La respuesta es fk3wfLCm3QvS\n", 29);
	if (ret == -1)
		perror("write");
}

static void quine_challenge(void)
{
	int res = system("gcc quine.c -o quine");
	if (!res) {
		printf("¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

		res = system("./quine | diff quine.c -");
		res ? printf("diff encontró diferencias\nENTER para reintentar\n\n") :
		      printf("La respuesta es chin_chu_lan_cha\n");
	}
}

static void b_black_challenge(void)
{
	printf("\033[30;40mLa respuesta es: BUmyYq5XxXGt\033[0m\n");
}

static void gdbme_challenge(void)
{
	(getpid() != 0x12345678) ? printf("ENTER PARA REINTENTAR\n") :
				   printf("La respuesta es gdb_rules");
}

double rand_gen()
{
	return ((double)(rand()) + 1.) / ((double)(RAND_MAX) + 1.);
}

// https://www.tutorialspoint.com/generate-random-numbers-following-a-normal-distribution-in-c-cplusplus
double normal_random()
{
	double v1 = rand_gen();
	double v2 = rand_gen();
	return cos(2 * PI * v2) * sqrt(-2. * log(v1));
}

static void normal_challenge(void)
{
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
		printf("%g ", normal_random());
	printf("\n");
}

static void filter_challenge(void)
{
	char *ans = "La respuesta es K5n2UFfpFMUN\n";
	srand(time(NULL));
	while (*ans) {
		if (normal_random() < 0.4) {
			write(1, ans++, 1);
		} else
			while (normal_random() < 0.6) {
				char rand_char =
					(char)(normal_random() * ('z' - 'A') +
					       'A');
				write(2, &rand_char, 1);
			}
	}
	return;
}
