
#include <stdio.h>

int main()
{
    int n;
    printf("Enter number of elements\n");
    scanf("%d",&n);
    int a[n];
    int prefixSum[n];
    printf("Enter elements\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);

    }
    //prefixSum[0]=a[0];
    for(int i=1;i<n;i++)
    {
        a[i]=a[i-1]+a[i];
    }
    printf("\n Prefix Sum \n");
    for(int i=0;i<n;i++)
    {
        printf("%d\t",a[i]);
    }
    return 0;
}
