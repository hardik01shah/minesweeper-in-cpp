#include<iostream>
#include<stdlib.h>
#include <time.h>

using namespace std;

int main()
{
	srand(time(0));
	int upper=7,lower=0,xrand,yrand,mine_count=0;
	int i,j,a,b;
	int A[8][8];

	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		A[i][j]=-2;
	}

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

	//print grid
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
	}

	return 0;
}