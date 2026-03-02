#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3


// Estrutura da Peça
typedef struct {
    char tipo;   // 'I', 'O', 'T', 'L'
    int id;      
} Peca;

// Fila Circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Pilha Linear
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

// Variável global para gerar IDs únicos
int contadorID = 1;

// Geração automática de peça
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// FUNÇÕES DA FILA
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void enqueue(Fila *f, Peca p) {
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->total++;
}

Peca dequeue(Fila *f) {
    Peca removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->total--;
    return removida;
}

// FUNÇÕES DA PILHA
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca nova) {
    p->topo++;
    p->itens[p->topo] = nova;
}

Peca pop(Pilha *p) {
    Peca removida = p->itens[p->topo];
    p->topo--;
    return removida;
}

// EXIBIÇÃO
void mostrarEstado(Fila *f, Pilha *p) {
    printf("\n========== ESTADO ATUAL ==========\n");

    // Mostrar fila
    printf("Fila de peças futuras:\n");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % TAM_FILA) {
        printf("[ %c-%d ] ", f->itens[idx].tipo, f->itens[idx].id);
    }

    // Mostrar pilha
    printf("\n\nPilha de reserva (topo -> base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[ %c-%d ]\n", p->itens[i].tipo, p->itens[i].id);
    }

    if (pilhaVazia(p)) {
        printf("(vazia)\n");
    }

    printf("==================================\n");
}

// PROGRAMA PRINCIPAL
int main() {

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inicializa fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        mostrarEstado(&fila, &pilha);

        printf("\n1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1: { // Jogar peça
                Peca jogada = dequeue(&fila);
                printf("\nPeça jogada: %c-%d\n", jogada.tipo, jogada.id);
                enqueue(&fila, gerarPeca());
                break;
            }

            case 2: { // Reservar peça
                if (pilhaCheia(&pilha)) {
                    printf("\nPilha cheia! Não pode reservar.\n");
                } else {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    printf("\nPeça reservada: %c-%d\n", reservada.tipo, reservada.id);
                    enqueue(&fila, gerarPeca());
                }
                break;
            }

            case 3: { // Usar peça reservada
                if (pilhaVazia(&pilha)) {
                    printf("\nPilha vazia! Nenhuma peça reservada.\n");
                } else {
                    Peca usada = pop(&pilha);
                    printf("\nPeça usada da reserva: %c-%d\n", usada.tipo, usada.id);
                }
                break;
            }

            case 0:
                printf("\nEncerrando jogo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}
