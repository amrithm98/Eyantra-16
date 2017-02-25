#include "algoFunctionsHelper.h"

void updatePaths(char share[], char driver) {
	int i, j, k, a = botAstat.node, b = botBstat.node, totalA, totalB, x;
	struct path temp;
	j = k = totalA = totalB = 0;
	for (i = noteCount - 1; i >=0; i--) {
		printf("Adding note %d\n", notes[i]);
		addPath(botA, j, a, notes[i]);
		addPath(botB, k, b, notes[i]);
		printf("Bot A distance = %d\n", totalA + botA[j].distance);
		printf("Bot B distance = %d\n", totalB + botB[k].distance);
		if (totalA + botA[j].distance <= totalB + botB[k].distance) {
			totalA += botA[j].distance;
			if (totalA < totalB) totalA = totalB + 1;
			j++;
			if (botA[j-1].subPathCount > 0)
				a = botA[j-1].subPath[0];
		} else {
			totalB += botB[k].distance;
			if (totalB < totalA) totalB = totalA + 1;
			k++;
			if (botB[k-1].subPathCount > 0)
				b = botB[k-1].subPath[0];
		}
	}
	for (i = 0; i < j/2; i++) {
		temp = botA[i];
		botA[i] = botA[j-i-1];
		botA[j-i-1] = temp;
	}
	for (i = 0; i < k/2; i++) {
		temp = botB[i];
		botB[i] = botB[k-i-1];
		botB[k-i-1] = temp;
	}
	pathLenA = j;
	pathLenB = k;
	if (driver == 'A')
		transferAB(share);
	else
		transferBA(share);
}