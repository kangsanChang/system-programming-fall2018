#include <stdio.h>
#include <string.h>

#define max(a,b) ((a)>(b)) ? (a) : (b)

int plumTree[1001];
int T,W;
int getMaxPlum(int myPos, int now, int cnt);

int main() {
	memset(plumTree, -1, sizeof(plumTree));
	int myPos = 1;
	scanf("%d %d",&T ,&W);
	for(int i=1; i<=T; i++){
		scanf("%d", &plumTree[i]);
	}
	int max = getMaxPlum(myPos, 1, W);
	printf("# of Max Plum : %d\n", max);
}

int getMaxPlum(int myPos, int now, int cnt){
	if(now>T || cnt<0)
		return 0;
	if(plumTree[now] != myPos)
		return max(getMaxPlum(myPos^1, now+1, cnt-1)+1, getMaxPlum(myPos, now+1, cnt));
	else
		return getMaxPlum(myPos, now+1, cnt)+1;
}
