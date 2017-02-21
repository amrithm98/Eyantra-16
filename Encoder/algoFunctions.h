#include "algoFunctionsHelper.h"

void updatePaths() {
	int i, j, k, a = botAstat.node, b = botBstat.node, x;
	struct path temp;
	j = k = 0;
	for (i = noteCount - 1; i >=0; i--) {
		printf("Adding note %d\n", notes[i]);
		addPath(botA, j, a, notes[i]);
		addPath(botB, k, b, notes[i]);
		if (botA[j].distance <= botB[k].distance) {
			j++;
			if (botA[j].subPathCount > 0)
				a = botA[j].subPath[0];
		} else {
			k++;
			if (botB[k].subPathCount > 0)
				b = botB[k].subPath[0];
		}
	}
	temp = botA[j-1];
	for (i = j-2; i >=0 ; i--) {
		botA[i+1] = botA[i];
	}
	botA[0] = temp;
	temp = botB[k-1];
	for (i = k-2; i >=0 ; i--) {
		botB[i+1] = botB[i];
	}
	botB[0] = temp;
	pathLenA = j;
	pathLenB = k;
	// addPath(botA, 0, 0, 20);
	// pathLenA = 5;
	// botA[4].nextNode = 1;
	// botA[3].nextNode = 27;
	// botA[2].nextNode = 25;
	// botA[1].nextNode = 26;
	// botA[0].nextNode = 22;
	// botA[4].subPathCount = 1;
	// botA[4].subPath[0] = 1;
	// botA[3].subPathCount = 2;
	// botA[3].subPath[0] = 27;
	// botA[3].subPath[1] = 2;
	// botA[2].subPathCount = 2;
	// botA[2].subPath[0] = 25;
	// botA[2].subPath[1] = 24;
	// botA[1].subPathCount = 1;
	// botA[1].subPath[0] = 26;
	// botA[0].subPathCount = 1;
	// botA[0].subPath[0] = 22;
}