#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int ** board;
int** createBoard(int,int,int);  
int printBoard(int);
void trominoTile(int);
int trominoTileRec(int,int,int);
int cnt=0;
void putTromino(int,int,int,int,int,int);
void freeMemory(int);
/*
* Main function where the execution starts.
*/
int main() {
	char ch;
	float error;
	int i,k,interror,size=1,x,y,j;
	takesize: printf("\nEnter the size of the chess board(eg:4 is 4X4):");
	scanf("%d",&size);
	error=log2(size);
	interror=error;
	if(interror!=error || size<2)
	{
		printf("The size should be log of base 2:\n");
		goto takesize;
	}
	takecordinate:printf("\nEnter the x and y cordinates of the defetive part of chess board(eg:x=3 y=4)\n x:");
	scanf("%d",&x);
	printf(" y:");
	scanf("%d",&y);
	if(x>size-1 || y>size-1)
	{
		printf("Enter the correct x and y cordinates\n");
		goto takecordinate;
	}
	board = createBoard(size,x,y);
	trominoTile(size);
	printf("\n\n");
	printBoard(size);
	freeMemory(size);
	printf("Do you want another chess board (y/n):");
	ch=getch();
	if(ch=='y'|| ch=='Y')
	goto takesize;	
	return 0;
}

/*Wrapper class which calls trominoTileRec*/
void trominoTile(int size) {
  	trominoTileRec(size,0,0);
}

/*TrominoTile Recursive function*/
int trominoTileRec(int n,int x,int y) {
	int i,j,hr,hc;	
	if(n == 2){
		cnt++;
		for(i=0;i<n;i++) {
			for(j=0;j<n;j++){
				if(board[x+i][y+j]==0)
					board[x+i][y+j]=cnt;
			}
		}
		return 0;
	}
	//Search the hole's location
	for(i=x;i<n;i++) {
		for(j=y;j<n;j++){
			if(board[i][j]==-1) {
				hr=i; hc=j;
			}
		}
	}

	//If missing Tile is in 1st quadrant
	if(hr< x + n/2 && hc < y+ n/2) {
		putTromino(x+n/2,y+n/2 - 1,x+n/2,y+n/2,x+n/2-1,y+n/2);		
	}
	//If missing Tile is in 2nd quadrant
	else if(hr < x + n/2 && hc >= y + n/2) {
		putTromino(x+n/2,y+ n/2-1,x+n/2,y+n/2,x+n/2-1,y+n/2-1);		
	}
	//If missing Tile is in 3rd quadrant
	else if(hr>=x+ n/2 && hc < y + n/2) {
		putTromino(x+n/2-1,y+n/2,x+n/2,y+n/2,x+n/2-1,y+n/2-1);		
	}
	//If missing Tile is in 4th quadrant
	else if(hr >= x + n/2 && hc >= y + n/2) {
		putTromino(x+n/2-1, y+ n/2,x+n/2,y+n/2-1,x+n/2-1,y+n/2-1);		
	}
	trominoTileRec(n/2, x, y);
	trominoTileRec(n/2, x, y+n/2);
	trominoTileRec(n/2, x+n/2, y);
	trominoTileRec(n/2, x+n/2, y+n/2);
	
	return 0;

}

void putTromino(int x1,int y1,int x2,int y2,int x3, int y3) {
	cnt++;	
	board[x1][y1] = cnt;
	board[x2][y2] = cnt;
	board[x3][y3] = cnt;
}
/*Create the Borad and initialize all except hole to zero*/
int **createBoard(int n,int x,int y)
{
	int ** array = (int**)malloc(n*sizeof(int *));	
	int i,j;
	for(i = 0;i < n; i++) 
	{
	    array[i] = (int*)malloc(n*sizeof(int));
   	 	for(j = 0; j < n; j++) 
			{
			if((i==x) && (j==y))
				array[i][j]=-1;
			else
	        		array[i][j] = 0;
	    	}
	}
	return array;
}

/*Prints the Board*/
int printBoard(int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++) {
			if(board[i][j]== -1)
			{
			printf(" X\t");
		    continue;
			}
			printf(" %d\t",board[i][j]);
		}
		printf("\n");
	}
}
/*free the memory*/
void freeMemory(int n){	
	free(board);
	cnt=0;
}
