#include <stdio.h>
#include <string.h>
#define MAX_T 1000
#define MAX_W 30
#define max(a,b) ((a)>(b))?(a):(b)

int maxPlum[MAX_T+1][3][MAX_W+1]; // now, my position, available move
int T, W;
int plumTree[MAX_T];

int main(){
	memset(maxPlum, -1, sizeof(maxPlum));
	scanf("%d %d",&T, &W);
	for(int i=1; i<=T ; i++){
		scanf("%d",&plumTree[i]);
	}
	
	maxPlum[0][1][0] = 0;
	for(int i=1; i<=T ; i++){
		for(int j=0; j<=i && j<=W ; j++){ // j 는 와리가리 한 횟수
			if(plumTree[i]==1){ // 1번 자두나무에서 떨어질 경우
				maxPlum[i][1][j] = max(maxPlum[i-1][1][j], maxPlum[i-1][2][j-1])+1;
				maxPlum[i][2][j] = maxPlum[i-1][2][j];
			}
			else{
				maxPlum[i][1][j] = maxPlum[i-1][1][j];
				maxPlum[i][2][j] = max(maxPlum[i-1][1][j-1], maxPlum[i-1][2][j])+1;
			}
		}
	}
	int maxking=0;
	for(int i=1; i<=W; i++){
		maxking = max(maxking, maxPlum[T][1][i]);
		maxking = max(maxking, maxPlum[T][2][i]);
	}

	printf("# of max plum is : %d\n\n\n", maxking);

	for(int i=1; i<=T; i++){
		for(int j=1; j<=2; j++){
			printf("maxPlum[%d][1][%d] : %d\n",i, j, maxPlum[i][1][j]);
			printf("maxPlum[%d][2][%d] : %d\n",i, j, maxPlum[i][2][j]);
		}
	}
	return 0;
}
