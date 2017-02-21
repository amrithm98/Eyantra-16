struct vertices {
	int x, y; // co-ordinates
	int edgeCount;
	int edgeIndices[6];
} nodes[49];

struct edges {
	int start, end;
	int obstacle;
	int startCompass;
	int leftSpeedRatio, rightSpeedRatio;
	int distance;
} edgeList[63];

int notes[] = {20,16,30,13,24,18,26,29,7,1};
int noteCount = 10;

struct path {
	int nextNode, note;
	int subPath[40];
	int subPathCount;
} botA[10], botB[10];
int pathLenA, pathLenB;

struct botStatus {
	int ready;
	int node;
} botAstat, botBstat;