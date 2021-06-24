#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct No{
  int valor;
  struct No *proximo;
};

struct Lista{
  struct No *primeiro;
  struct No *ultimo;
  int tamanho;
};

struct Lista* criarLista(){
  struct Lista *lista;
  lista = malloc(sizeof(struct Lista));
  if(!lista) { perror(NULL); exit(1); }
  return lista;
};

void inserirInicio(struct Lista* lista, int valor){
  struct No *novoNo = malloc(sizeof(struct No));
  if(!novoNo) { perror(NULL); exit(EXIT_FAILURE); }
  novoNo->valor = valor;
  if(lista->primeiro == NULL){
    lista->primeiro = novoNo;
    lista->ultimo = novoNo;
  }
  else{
    novoNo->proximo = lista->primeiro;
    lista->primeiro = novoNo;
  }
  lista->tamanho++;
}
bool removerInicio(struct Lista* lista){
  if(lista->tamanho == 0){
    return false;
  }
  if(lista->tamanho == 1){
    free(lista->primeiro);
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    return true;
  }
  struct No *noRemover = lista->primeiro;
  lista->primeiro = lista->primeiro->proximo;
  free(noRemover);
  lista->tamanho--;
  return true;
}
void inserirFinal(struct Lista *lista, int A) {
  struct No *novo = malloc(sizeof(struct No));
  if(!novo) { 
    perror(NULL); exit(EXIT_FAILURE); 
  }
  novo->valor = A;
  novo->proximo = NULL;
  lista->ultimo->proximo = novo;
  lista->ultimo = novo;
  lista->tamanho += 1;
}
void removerFinal(struct Lista* lista){
  if(lista->tamanho == 0){
    printf("lista vazia");
  }
  if(lista->tamanho == 1){
    free(lista->primeiro);
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
  }
  struct No *noRemover = lista->ultimo;
  struct No *noContador = lista->primeiro;
  for (int i=0;i<lista->tamanho;i++){
    if(noContador->proximo->valor == lista->ultimo->valor){
      lista->ultimo = noContador;
      free(noRemover);
      lista->tamanho--;
      break;
    }
    noContador= noContador->proximo;
  }
}
void inserirPosicao(struct Lista *lista, int pos, int valor){
  struct No *antecessorNo = lista->primeiro;
  struct No *novoNo = malloc(sizeof(struct No));
  novoNo->valor = valor;
  int i = 0;
  if(pos<=lista->tamanho){
    if(pos==0){
      inserirInicio(lista, valor);
    }
    else{
      for(int i=0;i < lista->tamanho;i++) {
        if(i==(pos-1)){
          novoNo->proximo = antecessorNo->proximo;
          antecessorNo->proximo = novoNo;
          lista->tamanho += 1;
          if(antecessorNo->valor == lista->ultimo->valor){
            lista->ultimo = novoNo;
          }
        }
        antecessorNo = antecessorNo->proximo;
      }
    }
  }
  else{
    printf("\nValor excede tamanho da lista\n");
  }
}
void removerPosicao(struct Lista *lista, int pos){
  if(lista->tamanho == 0){
    printf("Lista vazia");
  }
  if(lista->tamanho == 1){
    free(lista->primeiro);
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
  }
  if(lista->tamanho>1){
    struct No *noRemover = lista->primeiro;
    struct No *noAnterior = malloc(sizeof(struct No));
    struct No *noPosterior = malloc(sizeof(struct No));
    if(pos==0){
      removerInicio(lista);
    }
    else{
      for(int i=0; i < lista->tamanho;i++){
        if(i==(pos-1)){
          noAnterior = noRemover;
          noRemover = noRemover->proximo;
          noPosterior = noRemover->proximo;
          noAnterior->proximo = noPosterior;
          if(noRemover->valor == lista->ultimo->valor){
            lista->ultimo = noAnterior;
          }
          free(noRemover);
          lista->tamanho--;
          break;
        }
        noRemover = noRemover->proximo;
      }
    }
  }
}
void imprimirLista(struct Lista *lista){
  struct No* primeiroNo = lista->primeiro;
  for (int i=0;i<lista->tamanho;i++){
    printf("%d ", primeiroNo->valor);
    primeiroNo = primeiroNo->proximo;
  }
}
int main(void) {
  struct Lista* novaLista =  criarLista();
  printf("Duas inserções no inicio e duas no fim: \n");
  inserirInicio(novaLista, 2);
  inserirInicio(novaLista, 3);
  inserirFinal(novaLista, 5);
  inserirFinal(novaLista, 6);
  imprimirLista(novaLista);
  printf("\nInserindo valor 4 na posição 3: \n");
  inserirPosicao(novaLista,2, 4);
  imprimirLista(novaLista);
  printf("\nRemovendo o valor 4 na posição 3: \n");
  removerPosicao(novaLista, 2);
  imprimirLista(novaLista);
  printf("\nRemovendo o final: \n");
  removerFinal(novaLista);
  imprimirLista(novaLista);
  printf("\nRemovendo o inicio: \n");
  removerInicio(novaLista);
  imprimirLista(novaLista);
  printf("\nInserindo o último através do inserir em qualquer posição: \n");
  inserirPosicao(novaLista,3, 8);
  printf("\nÚltimo valor: %d\n", novaLista->ultimo->valor);
  imprimirLista(novaLista);
  return 0;
}