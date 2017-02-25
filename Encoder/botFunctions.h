// #include "botVariables.h"
// #include "botPrints.h"
// #include "botFunctionsHelper.h"

void lineFollow(int dist) {
	if (dist == -1) sleep(1);
}

void rotateAngles(x) {}
void moveForward() {}
void moveBackward() {}

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

int goFromToA(int from, int to, char driver, char *share) {
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
	// 1. Rotate angle if any
	if (angle > 1 || angle < -1) {
		rotateAngles(angle);
		moveBackward();
		lineFollow(botDistance);
		moveForward();
		if (obstacleDetect()) {
			setObstacle(1,2);
			rotateAngles(-angle);
			return 0;
		}
	}
	updateShareA(share);
	if (to == botBstat.node) {
		stopBot("Collision", driver);
		while (to == botBstat.node) {
			if (botAstat.ready == 0) {
				rotateAngles(-angle);
				botBstat.ready = 0;
				while (botBstat.ready == 0);
				return 0;
			}
			updateShareA(share);
		}
		startBot(driver);
	}
	botAstat.node = to;
	updateShareA(share);
	botAstat.compass = temp;
	// 2. Follow line
	lineFollow(-1);
	// 3. Check for obstacle
	if (obstacleDetect()) {
		setObstacle(to,2);
	}
	printf("%c Going from %d to %d by %d\n", driver, from, to, angle);
	return 1;
	// sleep(1);
}

int goFromToB(int from, int to, char driver, char *share) {
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
	// 1. Rotate angle if any
	if (angle > 1 || angle < -1) {
		rotateAngles(angle);
		moveBackward();
		lineFollow(botDistance);
		moveForward();
		if (obstacleDetect()) {
			setObstacle(1,2);
			rotateAngles(-angle);
			return 0;
		}
	}
	updateShareB(share);
	if (to == botAstat.node) {
		stopBot("Collision", driver);
		while (to == botAstat.node) {
			if (botBstat.ready == 0) {
				rotateAngles(-angle);
				botAstat.ready = 0;
				while (botAstat.ready == 0);
				return 0;
			}
			updateShareB(share);
		}
		startBot(driver);
	}
	botBstat.node = to;
	updateShareB(share);
	botBstat.compass = temp;
	// 2. Follow line
	lineFollow(-1);
	// 3. Check for obstacle
	if (obstacleDetect()) {
		setObstacle(1,2);
	}
	printf("%c Going from %d to %d by %d\n", driver, from, to, angle);
	return 1;
	// sleep(1);
}

void playNote(char driver) {
	sleep(1);
}