//MINESWEEPER_V2.0
//Editted 21/03/2020 by huntsman01
//Updates: grid changes each time a new game is played, grid is formed by placing mines at random positions

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int A[8][8];
int B[8][8];
int end_game,flag_count,quit;

void zeros(int x, int y)
{
	int i,j;

	for(i=-1;i<=1;i++)
	{
		for(j=-1;j<=1;j++)
		{
			if((x+i)>=0 && (x+i)<=7 && (y+j)>=0 && (y+j)<=7 && B[x+i][y+j]==9)
			{
				if(A[x+i][y+j]==0)
				{
					B[x+i][y+j]=0;
					end_game++;
					zeros(x+i,y+j);
				}

				else
				{
					B[x+i][y+j]=A[x+i][y+j];
					end_game++;
				}
			}
		}
	}
}

void initialize()
{	
	srand(time(0));
	int i,j,a,b;
	int upper=7,lower=0,xrand,yrand,mine_count=0;

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			A[i][j]=-2;
			B[i][j]=9;
		}
	}

	end_game=0;
	flag_count=0;
	quit=0;

	cout<<"    MINESWEEPER v_1.0    "<<endl<<endl;

	cout<<"Input format: "<<endl;
	cout<<"FOR OPERATION:Input 'f' if you want to flag a position, 'o' if you want to open a position or 'u' if you want to unflag a flagged block."<<endl;
	cout<<"FOR ROW/COLUMN: Input the coordinate where you want to open or place a flag/unflag."<<endl;
	cout<<"Example: "<<endl;
	cout<<"Operation: f"<<endl;
	cout<<"Row[0,7]: 0"<<endl;
	cout<<"Column[0,7]: 7"<<endl;
	cout<<"This implies you want to flag the block in row 0 and column 7."<<endl;
	cout<<"Input 'e' in OPERATION to exit the game."<<endl<<endl;

	cout<<"- in the board implies that position has not been opened yet."<<endl;
	cout<<"* in the board implies a flagged position."<<endl;
	cout<<"Numbers surrounding the board are to assist the player in determining the coordinates of the desired position."<<endl;


	for(i=0;i<10;i++)
	{
		xrand = (rand() % (upper - lower + 1)) + lower; 
        yrand = (rand() % (upper - lower + 1)) + lower; 
    	
    	A[xrand][yrand]=-1;
	}
	
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(A[i][j]==-2)
			{	
				mine_count=0;
				for(a=-1;a<=1;a++)
				{
					for(b=-1;b<=1;b++)
					{
						if((i+a)>=0 && (i+a)<=7 && (j+b)>=0 && (j+b)<=7 && (a!=0 || b!=0))
						{
							if(A[i+a][j+b]==-1)
							{
								mine_count++;
							}
						}
					}
				}
			A[i][j]=mine_count;
			}
		}
	}

	/*print the board(this is the solution)
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{	
			if(A[i][j]==-1)	//-1 implies a flag
				cout<<"* ";
			else					
				cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}*/

}

void print_grid()
{
	int i,j;

	cout<<"  ";
	for(i=0;i<8;i++)
	{
		cout<<" "<<i;
	}
	cout<<endl;
	cout<<"   ";
	for(i=0;i<8;i++)
	{
		cout<<"~ ";
	}
	cout<<endl;

	for(i=0;i<8;i++)
	{
		cout<<i<<"| ";
		for(j=0;j<8;j++)
		{	
			if(B[i][j]==9)			//9 implies boack has not been opened
				cout<<"- ";
			else if(B[i][j]==10)	//10 implies user has marked that block as flag
				cout<<"* ";
			else					//The block has been opened and it is not a mine.
				cout<<B[i][j]<<" ";
		}
		cout<<"|"<<i;
		cout<<endl;
	}

	cout<<"   ";
	for(i=0;i<8;i++)
	{
		cout<<"~ ";
	}
	cout<<endl;
	cout<<"  ";
	for(i=0;i<8;i++)
	{
		cout<<" "<<i;
	}
	cout<<endl;
}

int main()
{
	int i,j;
	int x,y;
	char operation,again;

	do
	{
		initialize();

		while(end_game!=64)
		{
			cout<<endl<<"Current Board: "<<endl;

			print_grid();
			cout<<"Positions filled: "<<end_game<<endl;
			cout<<"Flags available: "<<10-flag_count<<endl;

			cout<<"Input: "<<endl;
			cout<<"Operation(o/f/u/e): ";
			cin>>operation;

			if(operation=='e')
			{
				cout<<"You chose to quit the game"<<endl;
				quit++;
				break;
			}

			cout<<"Row[0,7]: ";
			cin>>x;
			cout<<"Column[0,7]: ";
			cin>>y;

			if(x<0 || x>7 || y<0 || y>7)
			{
				cout<<"Enter valid co-ordinate....from 1 to the row size/column size of the grid"<<endl;
				continue;
			}

			if(B[x][y]!=9 && B[x][y]!=10)
			{
				cout<<"This block has already been opened or flagged. Re-enter."<<endl;
				continue;
			}
			
			if(operation=='f')
			{	
				if(B[x][y]!=9)
				{
					cout<<"The block you wish to flag has already been opened or is flagged, please choose another block"<<endl;
					continue;
				}

				else if(flag_count<=10)
				{
					B[x][y]=10;
					end_game++;
					flag_count++;
				}

				else
				{
					cout<<"Your flags have finished....you just have "<<10<<" flags at your disposal."<<endl;
					continue;
				}
			}

			else if(operation=='o')
			{
				if(B[x][y]!=9)
				{
					cout<<"The block you wish to open has already been opened or is flagged, please choose another block"<<endl;
					continue;
				}

				else if(A[x][y]==0)
				{
					B[x][y]=0;
					end_game++;
					zeros(x,y);	
				}

				else if(A[x][y]==-1)
					break;

				else
				{
					B[x][y]=A[x][y];
					end_game++;
				}
			}

			else if(operation=='u')
			{
				if(B[x][y]!=10)
				{
					cout<<"The co-ordinate you have entered does not contain a flag....please re-enter"<<endl;
					continue;
				}

				else
				{
					B[x][y]=9;
					end_game--;
				}
			}

			else
			{
				cout<<"Enter valid Operation i.e. 'f' for flag, 'o' for operation, 'u' to unflag or 'e' to exit"<<endl;
				continue;

			}
		}

		cout<<endl<<"   GAME OVER   "<<endl;

		if(end_game==64)
			cout<<"You win."<<endl;
		else if(quit!=1)
			cout<<"You lose. You stepped on a mine."<<endl;

		do
		{	
			cout<<endl;
			cout<<"Do you wish to play again? (y/n)"<<endl;
			cout<<"Enter valid character:(y/n) ";
			cin>>again;

			cout<<endl;
		}while(again!='y' && again!='n');
	}while(again=='y');

	cout<<"   MINESWEEPER v_2.0"<<endl;
	cout<<"   By huntsman01"<<endl<<endl;

	return 0;
}



	