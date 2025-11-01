#include<stdio.h>
#include <stdlib.h>
#include <string.h>


int decToBin(int n)
{
      if (n == 0) return 0;
    if (n == 1) return 1;
    return decToBin(n / 2) * 10 + (n % 2);
} 


int main(int argc ,char* argv[])
{
    int n=atoi(argv[1]);
    char* src=argv[2];
    char* dest=argv[3];
    
    int dec[n];
    int bin[n];
    int j;
    FILE* fptr;
    
    fptr=fopen(src,"r");
    
    if( fptr== NULL)
    {
        printf("Error locating file");
        return 1;
    }
    j=0;
    while( fscanf( fptr, "%d" , &dec[j] ) ==1)
    {
         j++;
         if( j >= n)
         {
         	 break;
          }
     }
     
     fclose(fptr);
     
     for(int i=0;i<n;i++){
           bin[i]= decToBin(dec[i]);
     }
     
     FILE *dptr;
     
     dptr=fopen( dest,"w");
     if( dptr == NULL)
     {
     	printf("Error locating file");
        return 1;
    }
    
    for(int i=0;i<n;i++)
    {
    	fprintf( dptr , "%d\n" , bin[i]);
    }
    fclose(dptr);
    
    return 0;
}

