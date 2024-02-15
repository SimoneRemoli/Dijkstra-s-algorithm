#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


long long int dim;
void load_matrix(long long int*);
void mnr(long long int*);


int main(int argc, char **argv)
{
	srand(time(0));
	fprintf(stdout, "Size of matrix row=column:\n");
	printf(">>");
	scanf("%lld",&dim);
	long long int* ptr = malloc(sizeof(long long int)*dim*dim);
	load_matrix(ptr);
	for(long long int i=0;i<dim;i++)
	{
		for(long long int j = 0; j<dim; j++)
		{
			printf("\t %lld ", *(ptr + i*dim + j));
		}
		printf("\n");
		printf("\n");
	}
	mnr(ptr);
	return 0;
}
void load_matrix(long long int* ptr)
{
		srand(time(0));

		long long int* mat = malloc(sizeof(long long int)*dim*dim);
		for(int i=0;i<dim;i++)
		{
			for(int j=0;j<dim;j++)
			{
				if((rand()%10+1)%2==0)
					*(mat + i*dim + j) =-1;
				else
				{
					*(mat + i*dim + j)=rand()%10+1;
				}
			}
		}
		
		for(int i=0;i < dim;i++)
			*(mat + i*dim + i)=0;
		for (int i = 0; i < dim; i++)
		   for (int j = 0; j < dim; j++)
		      *(ptr + j*dim + i) = *(mat + i*dim + j);
		for (int i = 0; i < dim; i++)
			   for (int j = i+1; j < dim; j++)
			      *(ptr + i*dim + j) = *(mat + i*dim + j);
}
void mnr(long long int* ptr)
{
	long long int cost[dim],conosciuti[dim];
		for(int i=0;i<dim;i++)
		{
			cost[i]=10000;
			conosciuti[i]=0;
		}
		int min;
		cost[0]=0;
		conosciuti[0]=1;
		int nodo_attuale = 0;
		int c = 0;
		for(int matrix_type = 0;matrix_type<dim;matrix_type++)
		{
			for(int i=0;i<dim;i++)
			{

				if((*(ptr + i*dim+nodo_attuale)!=-1)&&((*(ptr + i*dim+nodo_attuale)+cost[nodo_attuale])<cost[i]))
						cost[i] = (cost[nodo_attuale]+ *(ptr + i*dim+nodo_attuale));
			}
			min = 10000;
			for(int i=0;i<dim;i++)
			{
				if((cost[i]<min)&&(conosciuti[i]==0))
				{
					min = cost[i];
					c = i;
				}
			}
			conosciuti[c]=1;
			nodo_attuale = c;
		}
		for(long long int i=0;i<dim;i++)
		{
			printf("conosciuti[%lld] =  %lld   cost[%lld]=  %lld  \n", i, conosciuti[i], i, cost[i]);
		}
		return;
}