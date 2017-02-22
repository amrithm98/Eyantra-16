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

int notes[] = {20,16,30,13,24,18,29,26,8,6};//{20,16,30,13,24,18,26,29,7,1};
int noteCount = 10;

struct path {
	int nextNode, note, distance;
	int subPath[40];
	int subPathCount;
} botA[10], botB[10];
int pathLenA, pathLenB;

struct botStatus {
	int ready;
	int node;
	int nextNode;
} botAstat, botBstat;

char share[8];
/* SHARE VALUES (Basic)
	0 - botAstat.node
	1 - botAstat.ready
	2 - notes covered by botA
	3 - share ready of botA
	4 - botBstat.node
	5 - botBstat.ready
	6 - notes covered by botB
	7 - share ready of botB
*/