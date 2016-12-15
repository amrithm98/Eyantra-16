#include <stdio.h>
#include <stdlib.h>

extern uint8_t _end;
extern uint8_t __stack;
struct graph;
int n;

struct edge {
	float distance;
	int obstacle;
	float angle;
	struct graph *end1,*end2;
};

struct graph {
	int n;
	int edgeCount;
	float x,y;
	struct edge **edgeList;
};

struct graph **node;

struct shortestWay {
	int n;
	float distance;
	float angle;
	struct shortestWay *parent;
};

float getDistance(float x1,float y1, float x2, float y2) {
	float num = (y2-y1)*(y2-y1) + (x2-x1)*(x2-x1);
	float m,n;
	n=0.0001;
	for(m=0; m < num; m=m+n) {
		if((m*m)>num) {
			m=m-n;
			break;
		}
	}
	return m;
}

void edgeInit(int a,int b,float c) {
	struct graph *g1,*g2;
	struct edge *newEdge = (struct edge*)malloc(sizeof(struct edge));
	g1 = *(node+a-1);
	g2 = *(node+b-1);
	(g1->edgeCount)++; (g2->edgeCount)++;
	g1->edgeList = (struct edge**)realloc(g1->edgeList,sizeof(struct edge)*(g1->edgeCount));
	g2->edgeList = (struct edge**)realloc(g2->edgeList,sizeof(struct edge)*(g2->edgeCount));
	newEdge->end1 = g1; newEdge->end2 = g2;
	newEdge->obstacle = 0; newEdge->distance = getDistance(g1->x,g1->y,g2->x,g2->y);
	newEdge->angle = c;
	*(g1->edgeList+g1->edgeCount-1) = newEdge;
	*(g2->edgeList+g2->edgeCount-1) = newEdge;
}

struct graph* graphInit(int n,float x,float y) {
	struct graph *newNode = (struct graph*) malloc(sizeof(struct graph));
	newNode->n = n;
	newNode->x = x;
	newNode->y = y;
	newNode->edgeCount = 0;
	newNode->edgeList = NULL;
	return newNode;
}

struct graph* getOtherSide(struct edge *edgeNode,struct graph *One) {
	//printf("%d %d %d\n",edgeNode->end1->n-1,edgeNode->end2->n-1,One->n-1);
	if ( (edgeNode->end1)->n == One->n ) return edgeNode->end2;
	else return edgeNode->end1;
}

int getPow(int a,int b) {
	int res = 1,i;
	for (i = 0; i < b; i++)
		res = res * a;
	return res;
}

int getN(struct graph *g) {
	return g->n;
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
	//printf("q of %d = %d\n",n,x);
}

int getDest(int *list,int dest) {
	if ( dest<25 ) {
		*list = dest;
		return 1;
	}
	switch(dest) {
		case 25:
			*(list) = 1;
			*(list+1) = 2;
			*(list+2) = 25;
			*(list+3) = 26;
			*(list+4) = 27;
			*(list+5) = 24;
			return 6;
		case 27:
			*(list) = 4;
			*(list+1) = 5;
			*(list+2) = 6;
			*(list+3) = 28;
			*(list+4) = 29;
			*(list+5) = 32;
			return 6;
		case 28:
			*(list) = 8;
			*(list+1) = 9;
			*(list+2) = 10;
			*(list+3) = 33;
			*(list+4) = 34;
			*(list+5) = 35;
			return 6;
		case 30:
			*(list) = 12;
			*(list+1) = 13;
			*(list+2) = 14;
			*(list+3) = 36;
			*(list+4) = 37;
			*(list+5) = 40;
			return 6;
		case 31:
			*(list) = 16;
			*(list+1) = 17;
			*(list+2) = 18;
			*(list+3) = 41;
			*(list+4) = 42;
			*(list+5) = 43;
			return 6;
		case 33:
			*(list) = 20;
			*(list+1) = 21;
			*(list+2) = 22;
			*(list+3) = 44;
			*(list+4) = 45;
			*(list+5) = 48;
			return 6;
		case 26:
			*(list) = 25;
			*(list+1) = 26;
			*(list+2) = 28;
			*(list+3) = 29;
			*(list+4) = 30;
			*(list+5) = 31;
			return 6;
		case 29:
			*(list) = 33;
			*(list+1) = 34;
			*(list+2) = 36;
			*(list+3) = 37;
			*(list+4) = 38;
			*(list+5) = 39;
			return 6;
		case 32:
			*(list) = 41;
			*(list+1) = 42;
			*(list+2) = 44;
			*(list+3) = 45;
			*(list+4) = 46;
			*(list+5) = 47;
			return 6;
	}
	return 0;
}

float complement(float x) {
	x += 180;
	if ( x>180 ) x-=360;
	return x;
}

float getAngle(struct edge *e,int n) {
	if (e->end1->n == n) return e->angle;
	else return complement(e->angle);
}

int destReached(int x,int destList[],int destLen) {
	int i;
	for (i = 0; i < destLen; i++) {
		if (x == destList[i]) return 1;
	}
	return 0;
}

struct shortestWay* getShortestWay(int src,int dest) {
	int i,j,qLen=1,q[50],cur,next,k,destLen;
	int destList[10];
	destLen = getDest(destList,dest);
	for (i = 0; i < destLen; i++) {
	//	printf("%d ",destList[i]);
	}
	//printf("\n");
	struct shortestWay **array = (struct shortestWay**)malloc(sizeof(struct shortestWay)*50);
	struct shortestWay *parent;
	struct edge *temp;
	struct graph *tempG;
	q[0] = src-1;
	for (i = 0; i < 50; i++) {
		*(array+i) = (struct shortestWay*)malloc(sizeof(struct shortestWay));
		(*(array+i))->n = i+1;
		(*(array+i))->distance = 50000;
		(*(array+i))->parent = NULL;
	}
	(*(array+src-1))->distance = 0;
	while ( 1 ) {
		printf("Iteration started\n");
		for (i = 0; i < qLen; i++) printf("%d ",q[i]);
		printf("\n");
		for (i = 0; i < destLen; i++) {
			if ( ((*(array+destList[i]-1))->parent)!=NULL ) {
				for (j = 0; j < qLen; j++) {
					if ( (*(array+q[j]))->distance >= (*(array+destList[i]-1))->distance ) {
						dequeue(q,qLen,j); j--; qLen--;
					}
				}
//				printf("Queue : ");
				for (j = 0; j < qLen; j++){ 
					printf("%d ",(*(array+j))->n);
				}
//				printf("\n");
				if ( qLen == 0 ) return *(array+destList[i]-1);
			}
		}
		if ( qLen==0 ) {
			printf("Error\n");
			return *(array+dest-1);
		}
		for (j = 0; j < qLen; j++) {
			//if (destReached(q[j],destList,destLen)) continue;
			cur = q[j];
			dequeue(q,qLen,j); j--; qLen--;
			parent = *(array+cur);
			i = (*(node+cur))->edgeCount;
			printf("Cur = %d\n",cur);
			for (k = 0; k < i; k++) {
				tempG = *(node+cur);
				temp = *((*(node+cur))->edgeList+k);
				tempG = getOtherSide(temp,tempG);
				next = tempG -> n;
//				printf("Next = %d\n",next-1);
				//printf("%d %d\n",cur,next);
//				printf("%f %f %f\n",(*(array+next-1))->distance,parent->distance,temp->distance);
				if ( (*(array+next-1))->distance > parent->distance+temp->distance ) {
					(*(array+next-1))->distance = parent->distance+temp->distance;
					(*(array+next-1))->parent = parent;
					enqueue(q,qLen,j+1,next-1); qLen++; j++;
					//printf("%dsdjsod\n",q[j-1]);
				}
			}
		}
	}
	return *(array+3);
}

int mainFunction(int FinalArr[],float FinalArr1[]) {
	//FILE *fp = fopen("input","r"); //To get input file
	int i,j; //For iterations
//	float x,y; //For graph elements
	int m;
//	int a,b; 
//	float c; //For edge elements
	float gArr[98] = {57,275,63,219,84,169,117,121,164,89,216,65,271,59,328,63,381,88,426,125,463,168,480,221,489,276,480,330,458,384,425,425,381,458,328,484,273,489,214,485,161,461,116,428,83,382,63,333,116,223,146,278,114,329,147,167,209,167,241,217,206,272,240,112,397,164,333,166,302,115,429,225,397,277,336,276,304,223,430,329,305,439,334,382,398,386,241,437,214,382,240,333,302,328,145,382,271,275};
	int eArr1[126] = {1,2,1,24,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,3,25,25,26,26,27,27,23,25,28,28,29,29,30,30,31,31,26,3,28,32,7,32,29,7,35,35,34,34,33,33,11,33,36,36,37,37,38,38,39,39,34,11,36,37,40,40,15,43,15,43,42,41,42,41,19,42,47,47,46,46,45,45,44,44,41,19,44,45,48,48,23,26,45,29,34,37,42};
	float eArr2[63] = {82.500000,-82.500000,67.500000,52.500000,37.500000,22.500000,7.500000,-7.500000,-22.500000,-37.500000,-52.500000,-67.500000,-82.500000,-97.500000,-112.500000,-127.500000,-142.500000,-157.500000,-172.500000,172.500000,157.500000,142.500000,127.500000,112.500000,-60.000000,-60.000000,-120.000000,-120.000000,60.000000,0.000000,-60.000000,-120.000000,180.000000,0.000000,60.000000,-120.000000,-60.000000,-60.000000,0.000000,0.000000,-60.000000,-120.000000,180.000000,120.000000,60.000000,-120.000000,-60.000000,-60.000000,0.000000,180.000000,60.000000,-120.000000,120.000000,180.000000,-120.000000,-60.000000,0.000000,120.000000,180.000000,180.000000,-60.000000,0.000000,-120.000000};
	struct graph *temp;
	struct edge *tempEdge,**tempList;
	struct shortestWay *best,*tempShort;
	n = 49;
	node = (struct graph**)malloc(sizeof(struct graph)*n);

//	return i;
	for (i = 1; i <= n; i++) { //Initialize vertices
		//fscanf(fp,"%d,%d",gArr[(i-1)*2],gArr[(i-1)*2+1]);
		//*(node+i-1) = graphInit(i,gArr[(i-1)*2],gArr[(i-1)*2+1]);
		return i;
	}
	return i;
	m = 63;
	for (i = 0; i < m; i++) {
		//fscanf(fp,"%d %d %f",eArr1[i*2],eArr1[i*2+1],eArr2[i]);
		edgeInit(eArr1[i*2],eArr1[i*2+1],eArr2[i]);
	}
	
/*	for (i = 0; i < n; i++) { //To verify whether input is assigned properly
		temp = *(node+i);
		printf("Node %d\n",temp->n);
		printf("\tCoordinates : %f %f\n",temp->x,temp->y);
		printf("\tNumber of edges : %d\n\n",temp->edgeCount);
		for (j = 0; j < temp->edgeCount; j++) {
			printf("\tEdge %d\n",j+1);
			tempEdge = *(temp->edgeList+j);
			printf("\t\tDistance : %f\n",tempEdge->distance);
			printf("\t\tObstacle : %d\n",tempEdge->obstacle);
			printf("\t\tEnd 1 : %d\n",(tempEdge->end1)->n);
			printf("\t\tEnd 2 : %d\n",(tempEdge->end2)->n);
		}
		printf("\n\n");
	}*/

	best = getShortestWay(25,29);
	for (tempShort = best; tempShort != NULL; tempShort = tempShort->parent) {
		i = tempShort->n;
		printf("Point %d\n",i);
		if ( tempShort->parent ) {
			//printf("Edge of node %d\n",(*(node+i-1))->n);
			tempList = (*(node+i-1))->edgeList;
			for (j = 0; j < (*(node+i-1))->edgeCount; j++) {
				tempEdge = *(tempList+j);
				temp = getOtherSide(tempEdge,*(node+i-1));
				//printf("Angle searching %d %d\n",temp->n,tempShort->parent->n);
				if (temp->n != tempShort->parent->n) continue;
				//printf("Angle found\n");
				tempShort->angle = getAngle(tempEdge,i);
			}
		}
	}
	i = 0;
	while ( best!=NULL ) {
		FinalArr[i] = best->n;
		FinalArr1[i] = best->angle;
		best = best->parent;
		i++;
	}
	for (j = 0; j < i; j++) {
//		printf("%d %f\n",FinalArr[j],FinalArr1[j]);
	}
	//COMPLETED

	return i;
}
