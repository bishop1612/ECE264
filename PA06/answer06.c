#include "answer06.h"
#include <stdio.h>
//
void print_d(char** maze, int row, int col, char dir, int w, int h){
	int iter = 1; //iter stores the current path of the cursor
	int sumiter = 1; //Sumiter is used to make the cursor to go back to it's original path
	
	//For south and north check nearby columns
	if(dir == 'S' || dir == 'N'){
		while(row <= h - 1 && row >= 0 && maze[row][col] !=  'X')
		{
			//If space is ' ' then call the function again with new direction
			
			//Checking for space in the east side
			if(col != w - 1){
				if(maze[row][col + 1] == ' '){
					if(iter != 0){
						printf("%c %d\n", dir, iter);
					}
					print_d(maze,row,col+1,'E',w,h);
					iter = 0;
				}
			}

			//Checking for space in the West side
			if(col != 0){
				if(maze[row][col - 1] == ' '){
					if(iter != 0){
						printf("%c %d\n", dir, iter);
					}//
					print_d(maze,row,col-1,'W',w,h);
					iter = 0;
				}
			}

			
			//Increment/Decrement rows based on direction
			if(dir == 'S'){
				row++;
			}
			else{
				row--;
			}

			iter++;
			sumiter++;
		}
		//Print statement if the cursor has but has not found any space
		if(iter - 1 != 0){
			printf("%c %d\n", dir, iter - 1);
		}
		//Prints the original track
		if(dir == 'S'){
			printf("N %d\n",sumiter-1);
		}
		else{
			printf("S %d\n",sumiter-1);
		}
		
	}

	//For west and east check nearby rows
	if(dir == 'W' || dir == 'E'){
		while(col >= 0 && col <= w-1 && maze[row][col] !=  'X' )
		{
			//Checking for space in the West side
			if(row != 0){
				if(maze[row - 1][col] == ' '){
					if(iter != 0){
						printf("%c %d\n", dir, iter);
					}
					print_d(maze,row-1,col,'N',w,h);
					iter = 0;
				}
			}

			//Checking for space in the West side
			if(row != h-1){
				if(maze[row + 1][col] == ' '){
					if(iter != 0){
						printf("%c %d\n", dir, iter);
					}
					print_d(maze,row+1,col,'S',w,h);
					iter = 0;
				}
			}

			//Increment/decrement columns based on direction
			if(dir == 'W'){
				col--;
			}
			else{
				col++;
			}
			iter++;
			sumiter++;
		}
		
		//Print the statement if the cursor has not found any space
		if(iter - 1 != 0){
			printf("%c %d\n", dir, iter - 1);
		}
		
		//Prints the original track
		if(dir == 'E'){
			printf("W %d\n",sumiter-1);
		}
		else{
			printf("E %d\n",sumiter-1);
		}
	}
}

void print_directions(char** maze, int w, int h) {
	int row = 0;
	int col = 0;
	
	//Checking for the initial space
	while(maze[row][col] != ' '){
		col++;
	}
	row = 1;
	char dir = 'S';
	//Sending it to the function from first row
	print_d(maze,row,col,dir,w,h);
}