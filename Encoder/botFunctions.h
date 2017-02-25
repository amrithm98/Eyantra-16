// #include "botVariables.h"
// #include "botPrints.h"
// #include "botFunctionsHelper.h"

int complementAngle(int angle) {
	if (angle > 180) return angle - 360;
	else if (angle <= -180) return angle + 360;
	else return angle;
}

void startBot(char driver) {
	printf("Bot %c started\n", driver);
	// moveForward();
	sleep(1);
}

void stopBot(char reason[], char driver) {
	printf("%c Bot stopped, reason: %s\n", driver, reason);
	// stop();
}

int obstacleDetect() {
	return 0;
}

void setObstacle(int from, int to) {
	//
}

void goFromToA(int from, int to, char driver) {
	int angle, temp, i;
	for (i = 0; i < nodes[from].edgeCount; i++) {
		if (edgeList[nodes[from].edgeIndices[i]].start == from && edgeList[nodes[from].edgeIndices[i]].end == to) {
			angle = edgeList[nodes[from].edgeIndices[i]].startCompass;
		} else if (edgeList[nodes[from].edgeIndices[i]].end == from && edgeList[nodes[from].edgeIndices[i]].start == to) {
			angle = complementAngle(180 + edgeList[nodes[from].edgeIndices[i]].startCompass);
		}
	}
	temp = angle;
	if (botAstat.compass <= angle + 15 && botAstat.compass >= angle - 15) {
		if (angle % 5 == 3 || angle % 5 == -3) angle = 1;
		else if (angle % 5 == 2 || angle % 5 == -2) angle = -1;
		else angle = 0;
	} else {
		angle = complementAngle(angle - botAstat.compass);
	}
	botAstat.compass = temp;
	printf("%c Going from %d to %d by %d\n", driver, from, to, angle);
	sleep(1);
}

void goFromToB(int from, int to, char driver) {
	int angle, temp, i;
	for (i = 0; i < nodes[from].edgeCount; i++) {
		if (edgeList[nodes[from].edgeIndices[i]].start == from && edgeList[nodes[from].edgeIndices[i]].end == to) {
			angle = edgeList[nodes[from].edgeIndices[i]].startCompass;
		} else if (edgeList[nodes[from].edgeIndices[i]].end == from && edgeList[nodes[from].edgeIndices[i]].start == to) {
			angle = complementAngle(180 + edgeList[nodes[from].edgeIndices[i]].startCompass);
		}
	}
	temp = angle;
	if (botBstat.compass <= angle + 15 && botBstat.compass >= angle - 15) {
		if (angle % 5 == 3 || angle % 5 == -3) angle = 1;
		else if (angle % 5 == 2 || angle % 5 == -2) angle = -1;
		else angle = 0;
	} else {
		angle = complementAngle(angle - botBstat.compass);
	}
	botBstat.compass = temp;
	printf("%c Going from %d to %d by %d\n", driver, from, to, angle);
	sleep(1);
}

void playNote(char driver) {
	sleep(1);
}