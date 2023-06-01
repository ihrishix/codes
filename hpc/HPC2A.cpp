#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);


void bubble(int *a, int n)
{
    for(  int i = 0;  i < n;  i++ )
     {  	 
   	 int first = i % 2; 	 

   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  )
   	   {  	 
   		 if(  a[ j ]  >  a[ j+1 ]  )
   		  {  	 
     			 swap(  a[ j ],  a[ j+1 ]  );
   		  }  	 
   		   }  	 
     }
}


void swap(int &a, int &b)
{

    int test;
    test=a;
    a=b;
    b=test;

}

int main()
{

    double start,end;
    int no_of_threads = 1;      //Set threads = 1 for sequential | 1< For parallel

	omp_set_num_threads(no_of_threads);

    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];

    for(int i=0;i<n;i++)
    {
   	 a[i]=rand()%n;
    }

    start=omp_get_wtime();  
    bubble(a,n);
    end=omp_get_wtime();
    
    printf("\n-------------------------\n Time Parallel= %f for %i threads \n\n",(end-start), no_of_threads);

return 0;
}

