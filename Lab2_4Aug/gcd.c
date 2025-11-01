#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findGCD(int a,int b){
       if( a==b )
              return a;
      else if(b==0)
              return a;
      else if(a>b)
              findGCD(b,a%b);
      else
               findGCD(b,a);

}



int main(int argc, char* argv[])
{
      
	char* src= argv[1];
	char* dest= argv[2];
	
	int n=10;
	int num[n];
	
	FILE* sptr;
	FILE* dptr;
	
	int len=0;
	sptr= fopen(src,"r");
	
	if(sptr==NULL)
	{
	      printf("Error in opening file");
	      return 1;
	}
	int i=0;
	while( fscanf(sptr,"%d", &num[i]) == 1)
	{
	      i++;
	      len++;
	   if(i>=n)
	     {
	     	break;
	     }
	}
	fclose(sptr);
	int gcd[len/2];
	int k=0;
	for(int j=0;j<n;j+=2)
	{
	     gcd[k++]=findGCD(num[j],num[j+1]);
	}
	
	dptr= fopen(dest,"w");
	
	if(dptr==NULL)
	{
	      printf("Error in opening file");
	      return 1;
	}
	
	for(int j=0;j<len/2;j++)
	{
	      fprintf( dptr, "%d\n", gcd[j]);
	}
	
	fclose(dptr);
	
	return 0;
}
