#include "answer06.h"
#include <stdio.h>
//
void print_d(char** maze, int row, int col, char dir, int w, int h){
	int iter = 1;
	int prviter = 1;
	//int inrow = row;
	//int incol = col;
	if(dir == 'S' || dir == 'N'){
		while(row <= h - 1 && row >= 0 && maze[row][col] !=  'X')
		{
			if(col != 0){
				if(maze[row][col - 1] == ' '){
					//if(prviter + 1)
					if(prviter + 1 != iter){
						printf("%c %d\n", dir, iter - prviter + 1);
					}
					else{
						printf("%c %d\n", dir, iter);
					}
					//}
					prviter = iter;
					print_d(maze,row,col-1,'W',w,h);
				}
			}
			if(col != w - 1){
				if(maze[row][col + 1] == ' '){
					if(prviter + 1 != iter){
						printf("%c %d\n", dir, iter - prviter + 1);
					}
					else{
						printf("%c %d\n", dir, iter);
					}
					prviter = iter;
					print_d(maze,row,col+1,'E',w,h);
				}
			}
			if(dir == 'S'){
				row++;
			}
			else{
				row--;
			}
			iter++;
		}
		if(prviter + 1 != iter){
			printf("%c %d\n", dir, iter - prviter);
		}
		if(dir == 'S'){
			printf("N %d\n",iter-1);
		}
		else{
			printf("S %d\n",iter-1);
		}
		
	}
	if(dir == 'W' || dir == 'E'){
		while(col >= 0 && col <= w-1 && maze[row][col] !=  'X' )
		{
			if(row != 0){
				if(maze[row - 1][col] == ' '){
					if(prviter + 1 != iter){
						printf("%c %d\n", dir, iter - prviter + 1);
					}
					else{
						printf("%c %d\n", dir, iter);
					}
					prviter = iter;
					print_d(maze,row-1,col,'N',w,h);
				}
			}
			if(row != h-1){
				if(maze[row + 1][col] == ' '){
					if(prviter + 1 != iter){
						printf("%c %d\n", dir, iter - prviter + 1);
					}
					else{
						printf("%c %d\n", dir, iter);
					}
					prviter = iter;
					print_d(maze,row+1,col,'S',w,h);
				}
			}
			if(dir == 'W'){
				col--;
			}
			else{
				col++;
			}
			iter++;
		}
		//printf("%c %d\n", dir, iter - 1);
		if(prviter + 1 != iter){
			printf("%c %d\n", dir, iter - prviter);
		}
		if(dir == 'E'){
			printf("W %d\n",iter-1);
		}
		else{
			printf("E %d\n",iter-1);
		}
	}
}

void print_directions(char** maze, int w, int h) {
	int row = 1;
	int col = (w + 1)/2;
	char dir = 'S';
	//printf("\n");
	print_d(maze,row,col,dir,w,h);
}