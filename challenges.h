#ifndef __CHALLENGES_H__
#define __CHALLENGES_H__

#include <stdlib.h>
#include <stdio.h>

#define CHALLENGES_NUMBER 12

typedef struct challenge_t {
	char *hint;
	void (*challenge)(void);
	char *research;
	char *ans;
} challenge_t;

void run_challenges(FILE * input);

#endif