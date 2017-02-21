void addToArr(int array[], int a, int b, int c, int d, int e, int f) {
	array[0] = a; array[1] = b; array[2] = c;
	array[3] = d; array[4] = e; array[5] = f;
}

int getNodesOfNote(int note, int nodeList[]) {
	if (note < 25) {
		nodeList[0] = note - 1;
		return 1;
	} else {
		switch(note) {
			case 25: addToArr(nodeList,0,24,25,26,0,0); return 4;
			case 26: addToArr(nodeList,24,25,27,28,29,30); return 6;
			case 27: addToArr(nodeList,4,27,28,31,0,0); return 4;
			case 28: addToArr(nodeList,8,32,33,34,0,0); return 4;
			case 29: addToArr(nodeList,32,33,35,36,37,38); return 6;
			case 30: addToArr(nodeList,12,35,36,39,0,0); return 4;
			case 31: addToArr(nodeList,16,40,41,42,0,0); return 4;
			case 32: addToArr(nodeList,40,41,43,44,45,46); return 6;
			case 33: addToArr(nodeList,20,43,44,47,0,0); return 4;
		}
	}
	return 0;
}

int getOtherSide(int edgeIndex, int oneEnd) {
	if (edgeList[edgeIndex].start != oneEnd)
		return edgeList[edgeIndex].start;
	return edgeList[edgeIndex].end;
}

void removeFromList(int list[],int listLen,int pos) {
	int i;
	for (i = pos; i < listLen-1; i++) {
		list[i] = list[i+1];
	}
}

void addToList(int list[],int listLen,int pos,int el) {
	int i;
	for (i = listLen-1; i >= pos; i--) {
		list[i+1] = list[i];
	}
	list[pos] = el;
}

void addPath(struct path bot[], int pos, int src, int dest) {
	int dests[6], destsCount, prevNode[49], dist[49], list[50], listLen = 0, i, j, k, x;
	bot[pos].note = dest;
	destsCount = getNodesOfNote(dest, dests);
	for (i = 0; i < 49; i++)
		prevNode[i] = -1;
	for (i = 0; i < 49; i++)
		dist[i] = 32767;
	addToList(list, listLen++, 0, src);
	dist[src] = 0;
	while (listLen > 0) {
		for (i = 0; i < destsCount; i++) {
			if (prevNode[i] != -1) {
				for (j = 0; j < listLen; j++) {
					if (dist[list[j]] >= dist[dests[i]])
						removeFromList(list, listLen--, j);
				}
			}
		}
		for (i = 0; i < listLen; i++) {
			k = list[i];
			removeFromList(list, listLen--, i--);
			for (j = 0; j < nodes[k].edgeCount; j++) {
				if (edgeList[nodes[k].edgeIndices[j]].obstacle == 1)
					continue;
				x = getOtherSide(nodes[k].edgeIndices[j], k);
				if (dist[x] > dist[k] + edgeList[nodes[k].edgeIndices[j]].distance) {
					dist[x] = dist[k] + edgeList[nodes[k].edgeIndices[j]].distance;
					prevNode[x] = k;
					addToList(list, listLen++, ++i, x);
				}
			}
		}
	}
	for (x = 0, i = 1; i < destsCount; i++) {
		if (dist[dests[i]] < dist[dests[x]])
			x = i;
	}
	bot[pos].nextNode = dests[x];
	for (i = dests[x], bot[pos].subPathCount = 0; prevNode[i] != -1; i = prevNode[i])
		bot[pos].subPath[bot[pos].subPathCount++] = i;
}