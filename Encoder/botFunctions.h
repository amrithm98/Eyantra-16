void startBot() {
	printf("Bot started\n");
	sleep(1);
}

void stopBot(char reason[]) {
	printf("Bot stopped, reason: %s\n", reason);
}

int obstacleDetect() {
	return 0;
}

void setObstacle(int from, int to) {
	//
}

void goFromTo(int from, int to) {
	printf("Going from %d to %d\n", from, to);
	botAstat.node = to;
	sleep(1);
}

void playNote() {
	printf("Note played\n");
	sleep(1);
}