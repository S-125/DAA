#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char name[50];
    int age;
    int height;
    int weight;
};

struct person *arr = NULL;
int n = 0;


void swap(struct person *a, struct person *b) {
    struct person t = *a; *a = *b; *b = t;
}


void minHeapify(int i) {
    int l = 2*i+1, r = 2*i+2, small = i;
    if (l<n && arr[l].age < arr[small].age) small = l;
    if (r<n && arr[r].age < arr[small].age) small = r;
    if (small != i) { swap(&arr[i], &arr[small]); minHeapify(small); }
}

void buildMinHeap() {
    for (int i=n/2-1;i>=0;i--) minHeapify(i);
}


void maxHeapify(int i) {
    int l = 2*i+1, r = 2*i+2, big = i;
    if (l<n && arr[l].weight > arr[big].weight) big = l;
    if (r<n && arr[r].weight > arr[big].weight) big = r;
    if (big != i) { swap(&arr[i], &arr[big]); maxHeapify(big); }
}

void buildMaxHeap() {
    for (int i=n/2-1;i>=0;i--) maxHeapify(i);
}


void display() {
    printf("Id Name Age Height Weight\n");
    for (int i=0;i<n;i++)
        printf("%d %s %d %d %d\n", arr[i].id, arr[i].name, arr[i].age, arr[i].height, arr[i].weight);
}


void readFile() {
    FILE *fp=fopen("students.txt","r");
    if (!fp) { printf("File not found\n"); return; }
    fscanf(fp,"%d",&n);
    arr = malloc(n*sizeof(struct person));
    for (int i=0;i<n;i++)
        fscanf(fp,"%d %s %d %d %d", &arr[i].id, arr[i].name, &arr[i].age, &arr[i].height, &arr[i].weight);
    fclose(fp);
    display();
}


void youngestWeight() {
    buildMinHeap();
    printf("Weight of youngest student: %d kg\n", arr[0].weight);
}


void insert() {
    struct person p;
    printf("Enter Id Name Age Height Weight: ");
    scanf("%d %s %d %d %d",&p.id,p.name,&p.age,&p.height,&p.weight);
    n++;
    arr = realloc(arr,n*sizeof(struct person));
    arr[n-1]=p;
    buildMinHeap();
}


void deleteOldest() {
    if (n==0) { printf("No data\n"); return; }
    int idx=0;
    for (int i=1;i<n;i++) if (arr[i].age>arr[idx].age) idx=i;
    printf("Deleted oldest: %s (Age %d)\n",arr[idx].name,arr[idx].age);
    arr[idx]=arr[n-1];
    n--;
    arr = realloc(arr,n*sizeof(struct person));
    buildMinHeap();
}

int main() {
    int ch;
    while (1) {
        printf("\n1.Read Data\n2.Min-heap(age)\n3.Max-heap(weight)\n4.Youngest weight\n5.Insert\n6.Delete oldest\n7.Exit\nChoice: ");
        scanf("%d",&ch);
        if (ch==1) readFile();
        else if (ch==2) { buildMinHeap(); display(); }
        else if (ch==3) { buildMaxHeap(); display(); }
        else if (ch==4) youngestWeight();
        else if (ch==5) insert();
        else if (ch==6) deleteOldest();
        else if (ch==7) break;
    }
}

