#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENT 10000

/*ESTRUTURA PARA LISTA*/
struct Nos {
	int valor;
	struct Nos* proximo;
};

/*ESTRUTURA PARA ARVORE DE BUSCA BINÁRIA*/
struct abb {
	int valor;
	int altura;
	struct abb *esq, *dir;
};
/*FUNCOES PROTOTIPAS PARA A LISTA ENCADEADA ORDENADA */
struct Nos *push(struct Nos **lista, int valor);
void selectionSort(struct Nos* LISTA);
void printf_lista(struct Nos *lista);
void troca(struct Nos *n1, struct Nos *n2);

/*FUNCOES PROTOTIPAS PARA A ABB*/
struct abb *novo_no(int valor);
void printf_abb(struct abb *raiz);
struct abb *inserir_na_abb(struct abb *novo, int valor);
int buscar_na_arvore(struct abb *raiz, int item, int *cont);
int busca_na_lista(struct Nos* LISTA, int valor);
void print_arvore(struct abb* raiz);
void print_pre_ordem(struct abb* raiz);
int numero_procurado_lista(struct Nos *LISTA, int valor);
int numero_procurado_abb(struct abb *raiz, int valor);
void selection_sort_vetor(int num[], int tam);
struct abb *create_binary_tree(int item, struct abb *left, struct abb *right);
void order_list_numbers(int size, int numbers[]);
void order_abb_numbers(int size, int numbers[]);
//struct abb *buscar_na_arvore(int valor);

int main() {
	struct Nos *LISTA = NULL;
	struct abb *raiz = NULL;
	int n, escolha, valor_desejado;
	int *r_comp_lista;
	int *r_comp_abb;
	int *numeros_comparados;
	int aux = 0;
	int i;
	int QTD = 0;

	int *sort_abb = (int*)malloc(sizeof(int) * MAX_ELEMENT);
	int *sort_list = (int*)malloc(sizeof(int) * MAX_ELEMENT);
	int *elementos = (int*)malloc(sizeof(int) * MAX_ELEMENT);
	r_comp_lista = (int*) malloc(sizeof(int) * MAX_ELEMENT);
	r_comp_abb = (int*) malloc(sizeof(int) * MAX_ELEMENT);
	numeros_comparados = (int*) malloc(sizeof(int) * MAX_ELEMENT);
	srand(time(NULL));

	do {
		printf("******************************************\n");
		printf("ESCOLHA UMA OPÇÃO:\n");
		printf("1 - GERAR ELEMENTOS\n");
		printf("2 - IMPRIMIR A LISTA ENCADEADA ORDENADA\n");
		printf("3 - IMPRIMIR A ABB\n");
		printf("0 - SAIR\n");
		printf("******************************************\n");

		scanf("%d", &escolha);

		switch (escolha) {
		case 0:
			break;
		case 1:
			printf("QUANTIDADE DE NUMEROS A SEREM GERADOS?\n");
			scanf("%d", &QTD);
			sort_abb[QTD], sort_list[QTD];
			for (i = 0; i <= QTD; i++) {
				n = (rand() % QTD);
				elementos[i] = n;
				push(&LISTA, n);
				selectionSort(LISTA);
				raiz = inserir_na_abb(raiz, n);
			}
			FILE *abb = fopen("abb.csv", "w");
			FILE *list = fopen("list.csv", "w");
			fprintf(abb,"size,abb\n");
			fprintf(list,"size,list_c\n");
			for (i = 0; i < QTD; i++) {
				int sorteado = elementos[i];
				int comp_list = busca_na_lista(LISTA, sorteado);
				int comp_abb;
				buscar_na_arvore(raiz, sorteado, &comp_abb);
				sort_list[i] = comp_list;
      	 	 	sort_abb[i] = comp_abb;
				comp_list =0;
				comp_abb = 0;
			}
				order_abb_numbers(QTD, sort_abb);
    			order_list_numbers(QTD, sort_list);

    			for (i = 0; i < QTD; i++)
   	 			{
        			fprintf(list,"%d,%d\n",i, sort_list[i]);
        			fprintf(abb, "%d,%d\n",i, sort_abb[i]);
    			}
    			fclose(list);
    			fclose(abb);
			printf("Arquivo de saída gerado com sucesso!\n");
			break;
		case 2:
			printf_lista(LISTA);
			break;
		case 3:
			print_pre_ordem(raiz);
			printf("\n");
			break;
		default:
			printf("OPÇÃO INVALIDA!\n");
			break;
		}

	} while (escolha);

	return 0;
}

struct Nos *push(struct Nos **lista, int valor) {
	struct Nos* init = (struct Nos*) malloc(sizeof(struct Nos));
	init->valor = valor;
	init->proximo = *lista;
	*lista = init;
}

struct abb *create_binary_tree(int item, struct abb *left, struct abb *right) {
	struct abb *new_bt = (struct abb*) malloc(sizeof(struct abb));
	new_bt->valor = item;
	new_bt->altura = 1;
	new_bt->esq = new_bt->dir = NULL;
	return new_bt;
}
void selection_sort_vetor(int num[], int tam)
{
  int i, j, min, swap;
  for (i = 0; i > (tam-1); i++)
   {
    min = i;
    for (j = (i+1); j > tam; j++) {
      if(num[j] > num[min]) {
        min = j;
      }
    }
    if (i != min) {
      swap = num[i];
      num[i] = num[min];
      num[min] = swap;
    }
  }
}

void selectionSort(struct Nos* LISTA) {
	struct Nos* aux = LISTA;

	while (aux) {
		struct Nos* old = aux;
		struct Nos* resltado = aux->proximo;

		while (resltado) {
			if (old->valor > resltado->valor)
				old = resltado;

			resltado = resltado->proximo;
		}

		troca(aux, old);
		aux = aux->proximo;
	}
}

void printf_lista(struct Nos *lista) {
	if (lista->proximo == NULL) {
		printf("A lista está vazia");
	} else {
		while (lista != NULL) {
			printf("%d\n", lista->valor);
			lista = lista->proximo;
		}
	}
}

void troca(struct Nos *n1, struct Nos *n2) {
	int aux = n1->valor;
	n1->valor = n2->valor;
	n2->valor = aux;
}

void printf_abb(struct abb *raiz) {
	if (raiz != NULL) {
		printf_abb(raiz->esq);
		printf("%d \n", raiz->valor);
		printf_abb(raiz->dir);
	}
}

void print_arvore(struct abb* raiz) {
	if (raiz != NULL) {
		print_arvore(raiz->esq);
		printf("\n%d", raiz->valor);
		print_arvore(raiz->dir);
	}
}

void print_pre_ordem(struct abb* raiz) {
	if (raiz != NULL) {
		printf("\n%d", raiz->valor);
		print_pre_ordem(raiz->esq);
		print_pre_ordem(raiz->dir);
	}
}

struct abb *inserir_na_abb(struct abb *raiz, int valor)
{
    if(raiz == NULL) return create_binary_tree(valor,NULL, NULL);
    /* Adiciona de forma ordenada na árvore */
    /* Os valores menores ficam à esquerda e os maiores à direita */
    if(valor < raiz->valor)
    {
        raiz->esq = inserir_na_abb(raiz->esq, valor);
    }
    else
    {
        raiz->dir = inserir_na_abb(raiz->dir, valor);
    }
    /* Retorna a nova árvore */
    return raiz;
}

int buscar_na_arvore(struct abb *raiz, int item, int *cont) {
	if(raiz == NULL) return -1;
    /* Incrementa no número de comparações */
    (*cont)+=1;
    if(raiz->valor == item)
    {
        return *cont;
    }
    else
    {
        if(item < raiz->valor)
        {
            return buscar_na_arvore(raiz->esq, item,cont);
        }
        else
        {
            return buscar_na_arvore(raiz->dir, item,cont);
        }
      }
}

int busca_na_lista(struct Nos* LISTA, int valor) {
	int comparacao = 0;
	while (LISTA != NULL) {
		if (LISTA->valor == valor) {
			comparacao++;
			//printf("Número de comparações pra achar na lista: %d\n", comparacao);
			return comparacao;
		}
		comparacao++;
		LISTA = LISTA->proximo;
	}
}

void order_abb_numbers(int size, int numbers[])
{
    int i,j;
    int aux;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if(numbers[j] > numbers[j + 1])
            {
                aux = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = aux;
            }
        }
    }
}
/* Ordena os numeros que foram gerados aleatoriamente na lista*/
void order_list_numbers(int size, int numbers[])
{
    int i,j;
    int aux;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if(numbers[j] > numbers[j + 1])
            {
                aux = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = aux;
            }
        }
    }
}
