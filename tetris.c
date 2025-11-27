#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

// Struct da peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Struct da Fila circular
typedef struct {
    Peca itens[MAX];
    int inicio, fim, total;
} Fila;

int contadorID = 0;

// Inicializar fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verificar se está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Verificar se está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Gerar peça aleatória
Peca gerarPeca() {
    char formas[] = {'I','O','T','L'};
    Peca p;
    p.tipo = formas[rand() % 4];
    p.id = contadorID++;
    return p;
}

// Inserir peça na fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("A fila está cheia!\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Remover peça da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca vazio = {'-', -1};
    if (filaVazia(f)) {
        printf("A fila está vazia!\n");
        return vazio;
    }
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return p;
}

// Mostrar fila
void mostrarFila(Fila *f) {
    printf("\nFila de peças futuras:\n");
    int i = f->inicio;
    for (int c = 0; c < f->total; c++) {
        printf("[%c %d] ", f->itens[i].tipo, f->itens[i].id);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {

    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    // Preencher fila inicial
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opc;

    do {
        mostrarFila(&fila);

        printf("\n1 - Jogar peça\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        if (opc == 1) {
            Peca jogada = dequeue(&fila);
            if (jogada.id != -1) {
                printf("Peça jogada: [%c %d]\n", jogada.tipo, jogada.id);
                enqueue(&fila, gerarPeca());
            }
        }

    } while (opc != 0);

    return 0;
}