int updateShareA() {
	int temp, test;
	temp = (share & 128) >> 7;
	if (temp == 1) { // Bot A
		if ((share & 127) == 127) {
			return -1; // obstacle
		}
		pathLenB = (share & 112) >> 4;
		botB[pathLenB-1].subPathCount = share & 15;
		test = 0;
		test = test | botA[pathLenA-1].subPathCount;
		test = test | (pathLenA << 4);
		share = test;
		printf("<><><>EXITING FROM A%d\n", share);
		return 1;
	}
	return 0;
}

int updateShareB() {
	int temp, test;
	temp = (share & 128) >> 7;
	if (temp == 0) { // Bot A
		if ((share & 127) == 127) {
			return -1; // obstacle
		}
		printf("<<<<<TTTT>>>>>%d ", share);
		pathLenA = (share & 112) >> 4;
		printf("%d\n", pathLenA);
		botA[pathLenA-1].subPathCount = share & 15;
		test = 128;
		test = test | botB[pathLenB-1].subPathCount;
		test = test | (pathLenB << 4);
		share = test;
		printf("<><><>EXITING FROM B%d %d %d %d\n", share, test, pathLenB, botB[pathLenB-1].subPathCount);
		return 1;
	}
	return 0;
}