/*
  Para compilar é semelhante ao código busca
  ./gerador 1 | ./seleciona 1 -s //selecao1
  ./gerador 1 | ./seleciona 1 -b //selecao2
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*---------------troca-----------------*/
#define FALSE 0
#define TRUE 1

typedef short Bool;

void troca(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void print_array(int* array, int size) {
  int i;
  for(i = 0; i < size; i++)
    printf("%i ", array[i]);
  printf("\n");
}
/*-------------------------------------*/

/* ------------ quickSort -------------- */

int partition(int* array, int size) {
  int pivot = array[size-1];
  int i = -1;
  int j;

  for(j = 0; j < size-1; j++)
    if(array[j] <= pivot)
      troca(&array[++i], &array[j]);
  troca(&array[i+1], &array[j]);

  return i + 1;
}

void quicksort(int* array, int size) {
  int q;
  if (size > 0) {
    q = partition(array, size);

    quicksort(array, q);
    quicksort(&array[q+1], size - (q + 1));
  }
}
/*-----------------------------------------------------*/
// devolve a posição de n no arranjo ou -1 se não encontrar
int selecao1(int* array, int n, int size){
    quicksort(array, size);
    return array[n];
}

// devolve a posição de n no arranjo ou -1 se não encontrar
int selecao2(int* array, int n, int size){
    int q;
    q = partition(array, size);
    if(size == 1) return array[0];
    if(n > 0){
        if(n < array[q]) selecao2(array, n, q);       
        else if(n > array[q]) selecao2(&array[q+1], n, size - (q + 1));
        else return array[q];
    } 
    else return -1;
}

void print_help() {
  puts("-s selecao1");
  puts("-b selecao2");
  puts("-h ajuda");
}


int main(int argc, char const *argv[]) {
  int size, i, nfound, n;
  clock_t start, end;
  double elapsed;
  int* array;
  int p, tipo = 0;

  int (*busca[])(int*, int, int) = {selecao1, selecao2};

  nfound = 0;

  if(argc < 2) {
    puts("Uso: busca <repetições> <opções>");
    return 1;
  }

  if(argc == 3) {
    if(argv[2][0] == '-') {
      if(argv[2][1] == 's') tipo = 0;
      if(argv[2][1] == 'b') tipo = 1;
      if(argv[2][1] == 'h') {
        print_help();
        return 0;
      }
    }
    else {
      print_help();
      return 0;
    }
  }

  n = atoi(argv[1]);

  scanf("%i", &size);
  array = (int*) malloc(sizeof(int)*size);

  for(i = 0; i < size; i++)
    scanf("%i", &array[i]);

  start = clock();
  for(int i = 0; i < n; i++) {
    if((*busca[tipo])(array, -1, size) != -1)
      nfound++;
  }
  end = clock();

  elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Encontrados %i de %i elementos em %.2lf segundos.\n", nfound, n, elapsed);
  return 0;
}