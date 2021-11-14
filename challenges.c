#include <stdio.h>
#include "challenges.h"

char *challenge_header = "------------- DESAFIO -------------",
     *research_header = "----- PREGUNTA PARA INVESTIGAR -----";

static challenge_t challenges[CHALLENGES_NUMBER] = {
	{
		.hint = "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\nDeberán estar atentos a los easter eggs.\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\n'",
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
		.challenge = NULL,
		.research =
			"¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
		.ans = "fk3wfLCm3QvS\n",
	},
	{
		.hint = "respuesta = strings:277\n",
		.challenge = NULL,
		.research =
			"¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
		.ans = "too_easy\n",
	},
	{
		.hint = ".data .bss .comment ? .shstrtab .symtab .strtab\n",
		.challenge = NULL,
		.research =
			"Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?",
		.ans = ".RUN_ME\n",
	},
	{
		.hint = "Filter error\n",
		.challenge = NULL,
		.ans = "K5n2UFfpFMUN\n",
		.research =
			"¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
	},
	{
		.hint = "¿? \n",
		.challenge = NULL,
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
		.challenge = NULL,
		.research =
			"¿Cuáles son las características del protocolo SCTP?",
		.ans = "chin_chu_lan_cha\n",
	},
	{
		.hint = "b gdbme y encontrá el valor mágico\n",
		.challenge = NULL,
		.research = "¿Qué es un RFC?",
		.ans = "gdb_rules\n",
	},
	{
		.hint = "Me conoces\n",
		.challenge = NULL,
		.research = "¿Se divirtieron?",
		.ans = "normal\n",
	}
};

void run_challenges()
{
	for (int i = 0; i < CHALLENGES_NUMBER; i++) {
		printf("%s\n%s\n\n", challenge_header, challenges[i].hint);
		if (challenges[i].research != NULL) {
			printf("%s\n%s\n\n", research_header,
			       challenges[i].research);
		}
	}
}