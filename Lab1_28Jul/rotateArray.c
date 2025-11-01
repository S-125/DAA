
#include <stdio.h>
int exchange(int* a,int p)
{
    int temp=a[p-1];
    for(int i=p-2;i>=0;i--)
    {
        a[i+1]=a[i];
    }
    a[0]=temp;
    
    return 0;
}
int main()
{
    int n;
    printf("Enter number of elements\n");
    scanf("%d",&n);
    int a[n],p;
    printf("Enter elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("Enter number of elements to rotate\n");
    scanf("%d",&p);
    exchange(a,p);
    printf("Rotated array\n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t",a[i]);
    }
    return 0;
}
