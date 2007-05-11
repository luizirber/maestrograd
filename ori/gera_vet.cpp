#include <iostream>
using namespace std;
#include <ctime>
#include <time.h>

#define tamanho 1000000


void quickSort(int numbers[],unsigned long  int array_size);
void q_sort(int numbers[],unsigned long  int left,unsigned long  int right);
void heapSort(int numbers[],unsigned long  int array_size);
void siftDown(int numbers[],unsigned long  int root,unsigned long  int bottom);
int intersearch(int numbers[],unsigned long int tam,int key);
int binarySearch(int sortedArray[],unsigned long int first,unsigned long int last,int key);

int main(int argc){
  int vet[tamanho], vet2[tamanho];
 srand((unsigned)time(0));
 
 //Inicia Relogio
 clock_t ini = clock();
 for (unsigned int i=0;i<tamanho;i++){   //Enche vetor com int randomicos
      vet[i]=rand()%1000000;
      vet2[i]=vet[i];
 }
 //Finalina Relogio
 clock_t fim = clock();
 cout<<"Tempo de Execucao: "<<(double)(fim-ini)/CLOCKS_PER_SEC<<endl;

 //////////////////////////////////QUICK//////////////////////////////////
 //Inicia Relogio
 ini = clock();
  quickSort(vet, tamanho);
 //Finalina Relogio
 fim = clock();
 cout<<"Tempo de Execucao do QUICK SORT: "<<(double)(fim-ini)/CLOCKS_PER_SEC<<endl;

 //////////////////////////////////HEAP//////////////////////////////////
 
 ini = clock();
  heapSort(vet2, tamanho);
 fim = clock();
 cout<<"Tempo de Execucao do HEAP SORT: "<<(double)(fim-ini)/CLOCKS_PER_SEC<<endl;







 int procura=rand()%1000000; 
 //////////////////////////////////BINARIO//////////////////////////////////
 ini = clock();
  for (int i=0;i<1000000;i++)
  binarySearch(vet, 0, tamanho-1, procura);
 fim = clock();
 cout<<"Tempo de Execucao da pesquisa BINARIA: "<<(double)(fim-ini)/CLOCKS_PER_SEC<<endl;

 //////////////////////////////////INTERPOLACAO//////////////////////////////////
 ini = clock();
//  for (int i=0;i<1000000;i++)
  intersearch(vet, tamanho,procura);  
 fim = clock();
 cout<<"Tempo de Execucao da pesquisa por INTERPOLACAO: "<<(double)(fim-ini)/CLOCKS_PER_SEC<<endl;

 //FIM ROTINAS
 

 /*
 for (int i=0;i<tamanho;i++){
   cout<<"["<<vet[i]<<"] ";
 }
 cout<<endl;
 */
 
}

void quickSort(int numbers[],unsigned long  int array_size)
{
  q_sort(numbers, 0, array_size - 1);
}


void q_sort(int numbers[],unsigned long  int left,unsigned long  int right)
{
  int pivot, l_hold, r_hold;

  l_hold = left;
  r_hold = right;
  pivot = numbers[left];
  while (left < right)
  {
    while ((numbers[right] >= pivot) && (left < right))
      right--;
    if (left != right)
    {
      numbers[left] = numbers[right];
      left++;
    }
    while ((numbers[left] <= pivot) && (left < right))
      left++;
    if (left != right)
    {
      numbers[right] = numbers[left];
      right--;
    }
  }
  numbers[left] = pivot;
  pivot = left;
  left = l_hold;
  right = r_hold;
  if (left < pivot)
    q_sort(numbers, left, pivot-1);
  if (right > pivot)
    q_sort(numbers, pivot+1, right);
}


void heapSort(int numbers[],unsigned long int array_size)
{
  int i, temp;

  for (i = (array_size / 2)-1; i >= 0; i--)
    siftDown(numbers, i, array_size);

  for (i = array_size-1; i >= 1; i--)
  {
    temp = numbers[0];
    numbers[0] = numbers[i];
    numbers[i] = temp;
    siftDown(numbers, 0, i-1);
  }
}


void siftDown(int numbers[],unsigned long int root,unsigned long int bottom)
{
  int done, maxChild, temp;

  done = 0;
  while ((root*2 <= bottom) && (!done))
  {
    if (root*2 == bottom)
      maxChild = root * 2;
    else if (numbers[root * 2] > numbers[root * 2 + 1])
      maxChild = root * 2;
    else
      maxChild = root * 2 + 1;

    if (numbers[root] < numbers[maxChild])
    {
      temp = numbers[root];
      numbers[root] = numbers[maxChild];
      numbers[maxChild] = temp;
      root = maxChild;
    }
    else
      done = 1;
  }
}


int  intersearch(int numbers[],unsigned long int tam,int key)
{   
   int low=0;
   int high=tam-1;
   while ((numbers[high] >= key) and (key > numbers[low]))
   {
     int j= ((key - numbers[low]) / (numbers[high]-numbers[low]) * (high-low))+low;
     if (key > numbers[j]) low=j+1;
       else if (key < numbers[j]) high=j-1;
              else low=j;
   }
   if (numbers[low]==key) return low;
     else return -1;
}

int binarySearch(int sortedArray[],unsigned long int first,unsigned long int last,int key) { 
  while (first <= last) {
       int mid = (first + last) / 2;
       if (key > sortedArray[mid]) 
           first = mid + 1;
       else if (key < sortedArray[mid]) 
           last = mid - 1;
       else
           return mid;    
   }
   return -(first + 1);   

}








