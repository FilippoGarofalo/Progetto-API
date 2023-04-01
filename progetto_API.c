#include <stdio.h>
#include <stdlib.h>
#define INT_32_MAX 2147483500

typedef struct topk_t{
  int index;
  int sum_path;
}topk_t;

int * parser (int d);
int dijkstra(int * curr_adj , int d);
void min_heapify (topk_t * p, int i , int k);
void swap(topk_t *a, topk_t* b);

int main(){
    char n;
    int index=0 , d=0 , k=0 , i;
    int tot;
    topk_t * testa = NULL;
    int * adj=NULL;
    n = getchar_unlocked();
    while(n!=' '){
        d = (d*10) + n - '0';
        n = getchar_unlocked();
    }
    n = getchar();
    while(n!='\n'){
        k = (k*10) + n - '0';
        n = getchar_unlocked();
    }
    testa = malloc(sizeof(topk_t) * k);
    for(i=0 ; i<k ; i++){
        (testa+i)->sum_path = INT_32_MAX;
        (testa+i)->index = -1;
    }
    n = getchar_unlocked();
    while(n!=EOF){
        if(n == 'A'){
            n = getchar_unlocked();
            while(n!='\n'){
                n = getchar_unlocked();
            }
            adj = parser(d);
            tot  = dijkstra(adj , d);
            free(adj);
            if(index-1<k){
              testa->sum_path = tot;
                  testa->index = index;
                  min_heapify(testa,0, k);
            }else{
                if(tot < testa->sum_path){
                  testa->sum_path = tot;
                  testa->index = index;
                  min_heapify(testa,0, k);
                }
              }
            index++;
            n = getchar_unlocked();
        }
        if(n == 'T'){
            n = getchar_unlocked();
            while(n!='\n'){
                n = getchar_unlocked();
            }
            if(index-1 < k){
              for(i=0;i<k;i++){
                if( (testa+i)->index !=-1 ){
                  if(i==0){
                    if((testa+i)->index != -1){
                      printf("%d", (testa+i)->index);
                    }
                  }else{
                      if((testa+i)->index != -1){
                        printf(" %d", (testa+i)->index);
                      }
                  }
                }
              }
            }else{
              for(i=0;i<k;i++){
                  if(i==0){
                    printf("%d", (testa+i)->index);
                  }else{
                      printf(" %d", (testa+i)->index);
                  }
              }
            }
            printf("\n");
            n = getchar_unlocked();
        }
    }
    return 0;
}

int* parser(int d){
    int i , j;
    char n;
    int * curr_adj = NULL;
    curr_adj = malloc( (sizeof(int)) * d * d);
    for(i=0 ; i<d ; i++){
      for(j=0 ; j<d-1 ; j++){
          *(curr_adj+(i*d)+j) = 0;
            n = getchar_unlocked();
            while(n!=','){
                *(curr_adj+(i*d)+j) = (*(curr_adj+(i*d)+j) *10) + n - '0';
                n = getchar_unlocked();
            }
        }
        *(curr_adj+(i*d)+j) = 0;
        n = getchar_unlocked();
        while(n!='\n'){
            *(curr_adj+(i*d)+j) = (*(curr_adj+(i*d)+j) *10) + n - '0';
            n = getchar_unlocked();
        }
    }
    return curr_adj;
}

int dijkstra (int* adj , int d){
  int i , passo  , curr_min , next=5;
  int tot;
  int * visited=NULL;
  int * dist = NULL;
  int* prec = NULL;

  dist = malloc(sizeof(int) * d);
  visited = malloc(sizeof(int) * d);
  prec = malloc(sizeof(int) * d);
  for(i=1,passo=0 ; i<d ; i++){
    if(*(adj+i)!=0){
      passo=1;
    }
  }
  if(passo==0){
    return 0;
  }
  for(i=0 ; i<d ; i++){
    *(dist+i) = *(adj+i);
    *(prec+i) = 0;
    *(visited+i) = 0;
  }
  *(dist) = 0;
  *(visited) = 1;
  passo=1;
  while(passo < d-1){
    curr_min = INT_32_MAX;
    for(i=0 ; i<d; i++){
      if(*(dist+i)!=0 && *(dist+i) <= curr_min && *(visited+i)==0){
        curr_min = *(dist+i);
        next = i;
      }
    }
    *(visited+next) = 1;
    for(i=0; i<d ; i++){
      if(*(visited+i)==0 && *(adj+(next*d)+i)>0){
        if(*(dist+i)==0){
          *(dist+i) = curr_min + *(adj+(next*d)+i);
          *(prec+i) = next;
        }else{
          if(curr_min + *(adj+(next*d)+i) <= *(dist+i)){
            *(dist+i) = curr_min + *(adj+(next*d)+i);
            *(prec+i) = next;
          }
        }
      }
    }
    passo++;
  }
  tot=0;
  for(i=1 ; i<d ; i++){
    if(*(dist+i)>0){
      tot = tot + *(dist+i);
    }
  }
  free(dist);
  free(visited);
  free(prec);
  return tot;
}

void min_heapify (topk_t * p, int i , int k){
    int l,r, posmin;
    l = (2*i) +1;
    r = (2*i) + 2;
    if(l <= k && (p+l)->sum_path > (p+i)->sum_path){
        posmin = l;
    }else{
        posmin = i;
    }
    if(r <= k && (p+r)->sum_path > (p+posmin)->sum_path){
        posmin = r;
    }
    if(posmin != i){
        swap(p + i, p + posmin);
        min_heapify (p, posmin , k);
    }
    return;
}

void swap(topk_t *a, topk_t* b){
    int tmp_sum_path;
    int tmp_index;
    tmp_sum_path = a->sum_path ;
    tmp_index = a->index;
    a->sum_path = b->sum_path;
    a->index = b->index;
    b->sum_path = tmp_sum_path;
    b->index = tmp_index;
    return;
}

