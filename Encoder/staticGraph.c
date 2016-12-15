struct vertice;
struct edge { int obstacle, angle, endA, endB, distance; };
struct vertice { int n, x, y, edgeCount, edgePoints[6]; };
struct vertice verticeList[49];
struct edge edgeList[63];
/*struct path {
	int pathCount;
	int vertices[49],angles[49];
};*/

int isqrt(int i) {
	int x =
	(verticeList[edgeList[i].endB].y - verticeList[edgeList[i].endA].y) *
	(verticeList[edgeList[i].endB].y - verticeList[edgeList[i].endA].y) +
	(verticeList[edgeList[i].endB].x - verticeList[edgeList[i].endA].x) *
	(verticeList[edgeList[i].endB].x - verticeList[edgeList[i].endA].x);
	int op = x, res = 0, one = 1 << 30;
	while (one > op) one >>= 2;
	while (one != 0) {
		if (op >= res + one) {
			op -= res + one;
			res += one << 1;
		}
		res >>= 1;
		one >>= 2;
	}
	return res;
}

void addToArr(int finalDest[], int a, int b, int c, int d, int e, int f) {
	finalDest[0] = a; finalDest[1] = b; finalDest[2] = c;
	finalDest[3] = d; finalDest[4] = e; finalDest[5] = f;
}

int getFinalDest(int dest, int finalDest[]) {
	int arr[6],i;
	if (dest < 25) {
		finalDest[0] = dest;
		return 1;
	} else {
		switch(dest) {
			case 25: addToArr(finalDest,1,2,24,25,26,27); break;
			case 26: addToArr(finalDest,25,26,28,29,30,31); break;
			case 27: addToArr(finalDest,4,5,6,28,29,32); break;
			case 28: addToArr(finalDest,8,9,10,33,34,35); break;
			case 29: addToArr(finalDest,33,34,36,37,38,39); break;
			case 30: addToArr(finalDest,12,13,14,36,37,40); break;
			case 31: addToArr(finalDest,16,17,18,41,42,43); break;
			case 32: addToArr(finalDest,41,42,44,45,46,47); break;
			case 33: addToArr(finalDest,20,21,22,44,45,48); break;
		}
		return 6;
	}
}

int getOtherSide(int tempE, int tempG) {
	if (edgeList[tempE].endA != tempG) return edgeList[tempE].endA;
	return edgeList[tempE].endB;
}

void dequeue(int q[],int qLen,int n) {
	int i;
	for (i = n; i < qLen-1; i++) {
		q[i] = q[i+1];
	}
}

void enqueue(int q[],int qLen,int n,int x) {
	int i;
	for (i = qLen-1; i >= n; i--) {
		q[i+1] = q[i];
	}
	q[n] = x;
}

int mainFun(int src,int dest) {
	//EXCEPT src,dest and finalDest, all will be counted from 0
	int verticeXY[98] = {57,275,63,219,84,169,117,121,164,89,216,65,271,59,328,63,381,88,426,125,463,168,480,221,489,276,480,330,458,384,425,425,381,458,328,484,273,489,214,485,161,461,116,428,83,382,63,333,116,223,146,278,114,329,147,167,209,167,241,217,206,272,240,112,397,164,333,166,302,115,429,225,397,277,336,276,304,223,430,329,305,439,334,382,398,386,241,437,214,382,240,333,302,328,145,382,271,275},
	edgeEnds[126] = {1,2,1,24,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,3,25,25,26,26,27,27,23,25,28,28,29,29,30,30,31,31,26,3,28,32,7,32,29,7,35,35,34,34,33,33,11,33,36,36,37,37,38,38,39,39,34,11,36,37,40,40,15,43,15,43,42,41,42,41,19,42,47,47,46,46,45,45,44,44,41,19,44,45,48,48,23,26,45,29,34,37,42},
	edgeAngles[63] = {82,-82,67,52,37,22,7,-7,-22,-37,-52,-67,-82,-97,-112,-127,-142,-157,-172,172,157,142,127,112,-60,-60,-120,-120,60,0,-60,-120,180,0,60,-120,-60,-60,0,0,-60,-120,180,120,60,-120,-60,-60,0,180,60,-120,120,180,-120,-60,0,120,180,180,-60,0,-120},
	i, j, x, y, z = -1, path[40], finalDest[6], finalDestCount, pathLen, prevPts[49], dist[49], q[50], qLen, compass;
	struct vertice tempV;
	struct edge tempE;
	for (i = 0; i < 49; i++) { //Vertice Initialization
		verticeList[i].n = i;
		verticeList[i].x = verticeXY[2*i];
		verticeList[i].y = verticeXY[2*i+1];
		verticeList[i].edgeCount = 0;
	}
	for (i = 0; i < 63; i++) { //Edge Initialization
		edgeList[i].obstacle = 0;
		edgeList[i].angle = edgeAngles[i];
		edgeList[i].endA = edgeEnds[2*i]-1;
		edgeList[i].endB = edgeEnds[2*i+1]-1;
		edgeList[i].distance = isqrt(i);
		verticeList[edgeList[i].endA].edgePoints[(verticeList[edgeList[i].endA].edgeCount)++] = i;
		verticeList[edgeList[i].endB].edgePoints[(verticeList[edgeList[i].endB].edgeCount)++] = i;
	}
	finalDestCount = getFinalDest(dest,finalDest);
	/*for (i = 0; i < 49; i++) { //To verify whether input is assigned properly
		tempV = verticeList[i];
		printf("Node %d\n",tempV.n);
		printf("\tCoordinates : %d %d\n",tempV.x,tempV.y);
		printf("\tNumber of edges : %d\n\n",tempV.edgeCount);
		for (j = 0; j < tempV.edgeCount; j++) {
			printf("\tEdge %d\n",j+1);
			tempE = edgeList[tempV.edgePoints[j]];
			printf("\t\tDistance : %d\n",tempE.distance);
			printf("\t\tObstacle : %d\n",tempE.obstacle);
			printf("\t\tAngle : %d\n",tempE.angle);
			printf("\t\tEnd A : %d\n",tempE.endA);
			printf("\t\tEnd B : %d\n",tempE.endB);
		}
		printf("\n\n");
	}*/
	for (i = 0; i < 49; i++) prevPts[i] = -1;
	for (i = 0; i < 49; i++) dist[i] = 50000;
	dist[src - 1] = 0;
	qLen = 1; q[0] = src - 1;
	while ( qLen>0 ) {
		for (i = 0; i < finalDestCount; i++)
			if (prevPts[finalDest[i]-1] != -1) {
				for (j = 0; j < qLen; j++) {
					if ( dist[q[j]] >= dist[finalDest[i]-1] ) {
						dequeue(q,qLen,j); j--; qLen--;
					}
				}
			}
		for (i = 0; i < qLen; i++) {
			x = q[i];
			dequeue(q,qLen,i); i--; qLen--;
			for (j = 0; j < verticeList[x].edgeCount; j++) {
				y = getOtherSide(verticeList[x].edgePoints[j],x);
				if (dist[y] > dist[x] + edgeList[verticeList[x].edgePoints[j]].distance) {
					dist[y] = dist[x] + edgeList[verticeList[x].edgePoints[j]].distance;
					prevPts[y] = x;
					enqueue(q,qLen,i+1,y); qLen++; i++;
				}
			}
		}
	}
	for (x = 0, i = 1; i < finalDestCount; i++) {
		if (dist[finalDest[i]-1] < dist[finalDest[x]-1])
			x = i;
	}
	z = finalDest[x] - 1;
	pathLen = 0; compass = 0;
	lcd_print(1, 13,prevPts[z], 3);
	while (prevPts[z] != -1) {
		path[pathLen++] = z+1;
		tempV = verticeList[z];
		for (i = 0; i < tempV.edgeCount; i++) {
			x = tempV.edgePoints[i];
			if (getOtherSide(x,z) == prevPts[z]) break;
		}
		if (z == edgeList[x].endA) path[pathLen++] = edgeList[x].angle + 180;
		else path[pathLen++] = edgeList[x].angle;
		if (path[pathLen-1] > 180) path[pathLen-1] -= 360;
		else if (path[pathLen-1] <= -180) path[pathLen-1] +=360;
		path[pathLen-1] = -path[pathLen-1];
		z = prevPts[z];
	}
	path[pathLen++] = src;
	for (i = 0; i < pathLen/2; i++) {
		x = path[i];
		path[i] = path[pathLen-i-1];
		path[pathLen-i-1] = x;
	}
	for (i = 1; i < pathLen; i+=2) {
		x = path[i];
		path[i] -= compass;
		if (path[i] >= 180) path[i] -= 360;
		else if (path[i] <= -180) path[i] += 360;
		compass = x;
	}
	//return pathLen;
	//for (i = 0; i < pathLen; i++)
	//	printf("%d ",path[i]);
	//printf("\n");
	return pathLen;
}

/*int main(int argc, char *argv[]) {
	int src = atoi(argv[1]), dest = atoi(argv[2]);
	mainFun(src,dest);
}*/
