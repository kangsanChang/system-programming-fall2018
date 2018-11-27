#include <stdio.h>
#include <string.h>

#define max(a,b) ((a)>(b)) ? (a) : (b)
#define change(a) ((a) == 1) ? 2 : 1
int plumTree[1001];
int T,W;
int getMaxPlum(int myPos, int now, int cnt);

int savemax[3][1001][31];

int main() {
	memset(savemax, -1, sizeof(savemax));
	int myPos = 1;
	scanf("%d %d",&T ,&W);
	for(int i=1; i<=T; i++){
		scanf("%d", &plumTree[i]);
	}
	int max = getMaxPlum(myPos, 1, W);
	printf("# of Max Plum : %d\n", max);
	for(int i=1; i<=T; i++){
		for(int j=1; j<=W; j++){
			printf("max[1][%d][%d] : %d\n",i,j, savemax[1][i][j]);
		}
	}
	for(int i=1; i<=T; i++){
		for(int j=1; j<=W; j++){
			printf("max[2][%d][%d] : %d\n",i,j, savemax[2][i][j]);
		}
	}
}

int getMaxPlum(int myPos, int now, int cnt){
	if(savemax[myPos][now][cnt] != -1)
		return savemax[myPos][now][cnt];
	if(now>T || cnt<0)
		return 0;
	if(plumTree[now] != myPos)
		return savemax[myPos][now][cnt] = max(getMaxPlum(change(myPos), now+1, cnt-1)+1, getMaxPlum(myPos, now+1, cnt));
	else
		return getMaxPlum(myPos, now+1, cnt)+1;
}
