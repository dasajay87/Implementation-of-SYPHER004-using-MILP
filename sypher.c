#include<stdio.h>
int next = 0; /* next unused state variable index */
int dummy = 0; /* next unused dummy variable index */
const int ROUNDS =3; /* number of rounds */
//int DBN=3;	/* DBN for PRESENT SBOX */
int i,j,r;
int dummy1=0;

	
void sbox(int a[][4]);

void permutation(int a[][4]);
void DBN(int a[][4]);

//function for bits permutation....
void permutation(int a[4][4])
{
	int temp[4][4];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			temp[j][i]=a[i][j];
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			a[i][j]=temp[i][j];
}

//function for sbox operation
void sbox(int a[4][4])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			printf("x%i - a%i <= 0 \n", a[i][j], dummy);
		}
		printf("x%i + x%i + x%i + x%i - a%i >= 0 \n", a[i][0], a[i][1], a[i][2], a[i][3],dummy);
			
		printf("4 x%i + 4 x%i + 4 x%i + 4 x%i - x%i - x%i - x%i - x%i >= 0\n",a[i][0],a[i][1],a[i][2],a[i][3],next,next+1,next+2,next+3);
		printf("4 x%i + 4 x%i + 4 x%i + 4 x%i - x%i - x%i - x%i - x%i >= 0\n",next,next+1,next+2,next+3,a[i][0],a[i][1],a[i][2],a[i][3]);
		
		//Constraints for Differential Branch number... 
		printf("x%i + x%i + x%i + x%i + x%i + x%i + x%i + x%i - 3 d%i >= 0\n",a[i][0],a[i][1],a[i][2],a[i][3],next,next+1,next+2,next+3, dummy1);
		
		
		printf("d%i - x%i >= 0\n", dummy1,a[i][0]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][1]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][2]);
		printf("d%i - x%i >= 0\n", dummy1,a[i][3]);
		printf("d%i - x%i >= 0\n", dummy1,next);
		printf("d%i - x%i >= 0\n", dummy1,next+1);
		printf("d%i - x%i >= 0\n", dummy1,next+2);
		printf("d%i - x%i >= 0\n", dummy1,next+3);
		
		for(int j=0;j<4;j++)
			a[i][j]=next++;
		
		dummy1++; 
		dummy++;
		
	}
	
}

//function for differential branch number....
void DBN(int a[4][4])
{
	

}

int main() 
{
  	int a[4][4]; /* the bits of the sypher004 input */
  	for (i = 0; i < 4; i++)
    		for (j = 0; j < 4; j++)
      			a[i][j] = next++; /* initialize variable indices */
  

  printf("Minimize\n"); /* print objective function */
  
  for (i=0; i<4*ROUNDS;i++)
  {
  	printf("a%i + ", i);
  }
  printf("a%i\n\n",i);
 
  /* round function constraints */
  printf("Subject To\n"); 
  for (r = 0; r<ROUNDS; r++) { sbox(a); DBN(a); permutation(a);}
  
  for(int i=0;i<15;i++)
  	printf("x%i + ", i);
  printf("x15 >= 1\n");

  printf("Binary\n"); /* binary constraints */
  for (i = 0; i < 16; i++) printf("x%i\n", i);
  for (i = 0; i < 4*ROUNDS; i++) printf("a%i\n",i);
  for (i = 0; i < 4*ROUNDS; i++) printf("d%i\n",i);
  printf ("End\n");

	return 0;
}


