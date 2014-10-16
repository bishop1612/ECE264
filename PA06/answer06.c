#include "answer06.h"
#include <stdio.h>
//
void print_d(char** maze, int row, int col, char dir, int w, int h){
	int iter = 0;
	int inrow = row;
	int incol = col;
	if(dir == 'S' || dir == 'N'){
		do
		{
			if(col != 0){
				if(maze[row][col - 1] == ' '){
					printf("%c %d\n", dir, iter);
					print_d(maze,row,col,'W',w,h);
				}
			}
			if(col != w - 1){
				if(maze[row][col + 1] == ' '){
					printf("%c %d\n", dir, iter);
					print_d(maze,row,col,'E',w,h);
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
		while(maze[row][col] !=  'X' || row == h - 1 || row != 0);
		if(dir == 'S'){
			printf("N %d\n",iter);
		}
		else{
			printf("S %d\n",iter);
		}
		
	}
	if(dir == 'W' || dir == 'E'){
		do
		{
			if(row != 0){
				if(maze[row - 1][col] == ' '){
					printf("%c %d\n", dir, iter);
					print_d(maze,row,col,'N',w,h);
				}
			}
			if(row != h-1){
				if(maze[row + 1][col] == ' '){
					printf("%c %d\n", dir, iter);
					print_d(maze,row,col,'S',w,h);
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
		while(maze[row][col] !=  'X' || col != 0 || col != w-1);
		
		if(dir == 'E'){
			printf("W %d\n",iter);
		}
		else{
			printf("E %d\n",iter);
		}
	}
	if(row != 0 && col != (w+1)/2)
	{
		print_d(maze,row,col,dir,w,h);
	}
}

void print_directions(char** maze, int w, int h) {
	int row = 0;
	int col = (w + 1)/2;
	char dir = 'S';
	print_d(maze,row,col,dir,w,h);
}