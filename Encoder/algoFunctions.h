#include "algoFunctionsHelper.h"

void updatePaths() {
	int i, j = botAstat.node;
	pathLenA = noteCount;
	for (i = noteCount - 1; i >=0; i--) {
		printf("Adding note %d\n", notes[i]);
		addPath(botA, i, j, notes[i]);
		if (botA[i].subPathCount > 0)
			j = botA[i].subPath[0];
	}
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