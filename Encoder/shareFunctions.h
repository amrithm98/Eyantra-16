void receiveAB(char share[]) {
	int n, m, i, j;
	share[7] = 3;
	while (share[3] == 0);
	pathLenB = share[7];
	share[3] = 0;
	n = pathLenB;
	for (i = 0; i < n; i++) {
		while (share[3] == 0);
		botB[i].nextNode = share[7];
		share[3] = 0;
		while (share[3] == 0);
		botB[i].note = share[7];
		share[3] = 0;
		while (share[3] == 0);
		botB[i].distance = share[7];
		share[3] = 0;
		while (share[3] == 0);
		botB[i].subPathCount = share[7];
		share[3] = 0;
		m = botB[i].subPathCount;
		for (j = 0; j < m; j++) {
			while (share[3] == 0);
			botB[i].subPath[j] = share[7];
			share[3] = 0;
		}
		while (share[3] == 0);
	}
	share[7] = 1;
}

void receiveBA(char share[]) {
	int n, m, i, j;
	share[7] = 3;
	while (share[3] == 0);
	pathLenA = share[7];
	share[3] = 0;
	n = pathLenA;
	for (i = 0; i < n; i++) {
		while (share[3] == 0);
		botA[i].nextNode = share[7];
		share[3] = 0;
		while (share[3] == 0);
		botA[i].note = share[7];
		share[3] = 0;
		while (share[3] == 0);
		botA[i].distance = share[7];
		share[3] = 0;
		while (share[3] == 0);
		botA[i].subPathCount = share[7];
		share[3] = 0;
		m = botA[i].subPathCount;
		for (j = 0; j < m; j++) {
			while (share[3] == 0);
			botA[i].subPath[j] = share[7];
			share[3] = 0;
		}
		while (share[3] == 0);
	}
	share[7] = 1;
}

void transferAB(char share[]) {
	int i, j;
	share[3] = 0;
	share[7] = 2;
	while (share[7] != 3);
	share[7] = pathLenB;
	share[3] = 1;
	while (share[3] == 1);
	for (i = 0; i < pathLenB; i++) {
		share[7] = botB[i].nextNode;
		share[3] = 1;
		while (share[3] == 1);
		share[7] = botB[i].note;
		share[3] = 1;
		while (share[3] == 1);
		share[7] = botB[i].distance;
		share[3] = 1;
		while (share[3] == 1);
		share[7] = botB[i].subPathCount;
		share[3] = 1;
		while (share[3] == 1);
		for (j = 0; j < botB[i].subPathCount; j++) {
			share[7] = botB[i].subPath[j];
			share[3] = 1;
			while (share[3] == 1);
		}
	}
	share[3] = 1;
}

void transferBA(char share[]) {
	int i, j;
	share[3] = 0;
	share[7] = 2;
	while (share[7] != 3);
	share[7] = pathLenA;
	share[3] = 1;
	while (share[3] == 1);
	for (i = 0; i < pathLenA; i++) {
		share[7] = botA[i].nextNode;
		share[3] = 1;
		while (share[3] == 1);
		share[7] = botA[i].note;
		share[3] = 1;
		while (share[3] == 1);
		share[7] = botA[i].distance;
		share[3] = 1;
		while (share[3] == 1);
		share[7] = botA[i].subPathCount;
		share[3] = 1;
		while (share[3] == 1);
		for (j = 0; j < botA[i].subPathCount; j++) {
			share[7] = botA[i].subPath[j];
			share[3] = 1;
			while (share[3] == 1);
		}
	}
	share[3] = 1;
}

void initShare(char share[]) {
	share[0] = 0; botAstat.node = 0;
	share[1] = 0; botAstat.ready = 0;
	share[2] = 0;
	share[3] = 1;
	// Below actually belongs to only botB
	share[4] = 12; botBstat.node = 12;
	share[5] = 0; botBstat.ready = 0;
	share[6] = 0;
	share[7] = 1;
}

void updateShareA(char share[]) {
	if (share[3] == 1) {
		botBstat.node = share[4];
		botAstat.ready = share[1];
		share[0] = botAstat.node;
		if (share[6] != 0) {
			noteCount -= share[6];
			share[6] = 0;
		}
	} else if (share[7] == 2) {
		receiveBA(share);
	}
}

void updateShareB(char share[]) {
	if (share[7] == 1) {
		botAstat.node = share[0];
		botBstat.ready = share[5];
		share[4] = botBstat.node;
		if (share[2] != 0) {
			noteCount -= share[2];
			share[2] = 0;
		}
	} else if (share[7] == 2) { // other bot ready for communication
		receiveAB(share);
	}
}

void changeReadyA(char share[], int val) {
	botAstat.ready = val;
	share[1] = val;
}

void changeReadyB(char share[], int val) {
	botBstat.ready = val;
	share[5] = val;
}