#include "botVariables.h"
#include "botPrints.h"
#include "botFunctionsHelper.h"

void startBot(char driver) {
	printf("Bot %c started\n", driver);
	sleep(1);
}

void stopBot(char reason[], char driver) {
	printf("%c Bot stopped, reason: %s\n", driver, reason);
}

int obstacleDetect() {
	return 0;
}

void setObstacle(int from, int to) {
	//
}

void goFromTo(int from, int to, char driver) {
	printf("%c Going from %d to %d\n", driver, from, to);
	botAstat.node = to;
	sleep(1);
}

void playNote(char driver) {
	// sleep(1);
}