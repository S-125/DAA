
#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of elements\n");
    scanf("%d",&n);
    int a[n],max,min,smax,smin;
     printf("Enter elements\n");
     for(int i=0;i<n;i++)
     {
         scanf("%d",&a[i]);
     }
     max=a[0],min=a[0];
     for(int i=0;i<n;i++)
     {
         if(a[i]>max)
         {
             max=a[i];
         }
         if(a[i]<min)
         {
             min=a[i];
         }
     }
      smax=min,smin=max;
     for(int i=0;i<n;i++)
     {
         if(a[i]!=max && a[i]>smax)
         {
             smax=a[i];
         }
         if(a[i]!=min && a[i]<smin)
         {
             smin=a[i];
         }
     }
     printf("\n Second Largest= %d ",smax);
     printf("\n Second Smallest= %d ",smin);
    

    return 0;
}
