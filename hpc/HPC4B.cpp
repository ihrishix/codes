!pip install git+https://github.com/andreinechaev/nvcc4jupyter.git

//set the runtime to gpu


%load_ext nvcc_plugin



%%cu
#include<stdio.h>
#define TILE_WIDTH 10

__global__ void MatrixMul( int *Md , int *Nd , int *Pd , const int WIDTH )
{

           unsigned int col = TILE_WIDTH*blockIdx.x + threadIdx.x ;

           unsigned int row = TILE_WIDTH*blockIdx.y + threadIdx.y ;

           Pd[row*WIDTH + col]=0;

         for (int k = 0 ; k<WIDTH ; k++ )
         {
                  Pd[row*WIDTH + col]+= Md[row * WIDTH + k ] * Nd[ k * WIDTH + col] ;
          }

}

int main ()
{
   const int WIDTH = 10;
   int array1_h[WIDTH][WIDTH] ,array2_h[WIDTH][WIDTH],result_array_h[WIDTH][WIDTH];
  int *array1_d , *array2_d ,*result_array_d ; 
  int i , j ;
 
  for ( i = 0 ; i < WIDTH ; i++ )
  {
     for (j = 0 ; j < WIDTH ; j++ )
     {
       
    	 array1_h[i][j]=2;
    	 array2_h[i][j]=2;
     }
  }

  cudaMalloc((void **) &array1_d , WIDTH*WIDTH*sizeof (int) ) ;

  cudaMalloc((void **) &array2_d , WIDTH*WIDTH*sizeof (int) ) ;

  cudaMemcpy ( array1_d , array1_h , WIDTH*WIDTH*sizeof (int) , cudaMemcpyHostToDevice ) ;

  cudaMemcpy ( array2_d , array2_h , WIDTH*WIDTH*sizeof (int) , cudaMemcpyHostToDevice ) ;

  cudaMalloc((void **) &result_array_d , WIDTH*WIDTH*sizeof (int) ) ;

  dim3 dimGrid ( WIDTH/TILE_WIDTH , WIDTH/TILE_WIDTH ,1 ) ;

  dim3 dimBlock( TILE_WIDTH, TILE_WIDTH, 1 ) ;
  MatrixMul <<<dimGrid,dimBlock>>> ( array1_d , array2_d ,result_array_d , WIDTH) ;

  cudaMemcpy(result_array_h , result_array_d , WIDTH*WIDTH*sizeof(int) ,cudaMemcpyDeviceToHost) ;

  printf("matrix result\n");
  for ( i = 0 ; i < WIDTH ; i++ )
  {
      for ( j = 0 ; j < WIDTH ; j++ )
     {
        printf ("%d   ",result_array_h[i][j] ) ;
     }
 printf ("\n") ;
}
 system("pause") ;
}