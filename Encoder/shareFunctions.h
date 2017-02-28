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

char createShare(char driver, int pathLen, int subPathCount) {
	char x = subPathCount;
	pathLen &= 7;
	pathLen = pathLen << 4;
	x = x | pathLen;
	x = x | subPathCount;
	return x;
}

void extractShare(char x) {
	int a, b;
	a = x & 15;
	x = x & 112;
	x = x >> 4;
}

int updateShareA() {
	int temp;
	temp = (share & 128) >> 7;
	if (temp == 1) { // Bot A
		if ((share & 127) == 127) {
			return -1; // obstacle
		}
		pathLenB = (share & 112) >> 4;
		botB[pathLenB-1].subPathCount = share & 15;
		share = 0;
		share = share | botA[pathLenA-1].subPathCount;
		share = share | (pathLenA << 4);
		return 1;
	}
	return 0;
}

int updateShareB() {
	int temp;
	temp = (share & 128) >> 7;
	if (temp == 0) { // Bot A
		if ((share & 127) == 127) {
			return -1; // obstacle
		}
		pathLenA = (share & 112) >> 4;
		botA[pathLenA-1].subPathCount = share & 15;
		share = 128;
		share = share | botB[pathLenB-1].subPathCount;
		share = share | (pathLenB << 4);
		return 1;
	}
	return 0;
}

void changeReadyA(char share[], int val) {
	botAstat.ready = val;
	share[1] = val;
}

void changeReadyB(char share[], int val) {
	botBstat.ready = val;
	share[5] = val;
}