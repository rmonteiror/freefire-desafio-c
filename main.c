#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 200
#define NOME_MAX 32

typedef enum { ALIMENTO=0, ARMA=1, FERRAMENTA=2 } ItemTipo;

typedef struct {
    char nome[NOME_MAX];
    ItemTipo tipo;
    int prioridade; // 1..100
} Item;

/* ---------------- Lista Sequencial (Vetor) ---------------- */
typedef struct {
    Item data[MAX];
    int size;
} SeqList;

void seq_init(SeqList* L){ L->size = 0; }

int seq_inserir_fim(SeqList* L, Item x){
    if(L->size >= MAX) return 0;
    L->data[L->size++] = x;
    return 1;
}

int seq_remover_indice(SeqList* L, int idx){
    if(idx < 0 || idx >= L->size) return 0;
    for(int i=idx;i<L->size-1;i++) L->data[i]=L->data[i+1];
    L->size--;
    return 1;
}

int seq_busca_sequencial_nome(SeqList* L, const char* nome, long* comps){
    for(int i=0;i<L->size;i++){
        (*comps)++;
        if(strcmp(L->data[i].nome, nome)==0) return i;
    }
    return -1;
}

/* --------- Utilidades de impressão ---------- */
const char* tipo_str(ItemTipo t){
    switch(t){
        case ALIMENTO: return "ALIMENTO";
        case ARMA: return "ARMA";
        case FERRAMENTA: return "FERRAMENTA";
        default: return "?";
    }
}

void print_item(const Item* x){
    printf(" - %-12s | %-10s | prioridade=%d\n", x->nome, tipo_str(x->tipo), x->prioridade);
}

void seq_listar(const SeqList* L){
    printf("Inventario (seq): size=%d\n", L->size);
    for(int i=0;i<L->size;i++){
        printf("[%3d]", i); print_item(&L->data[i]);
    }
}

/* ------------- Comparadores ------------- */
int cmp_nome(const Item* a, const Item* b){ return strcmp(a->nome,b->nome); }
int cmp_prioridade_desc(const Item* a, const Item* b){ return b->prioridade - a->prioridade; }

/* ------------- Bubble Sort (por nome) ------------- */
long bubble_sort_nome(SeqList* L){
    long comps=0;
    for(int i=0;i<L->size-1;i++){
        for(int j=0;j<L->size-1-i;j++){
            comps++;
            if(cmp_nome(&L->data[j], &L->data[j+1]) > 0){ // vetor[j] > vetor[j+1]
                Item tmp = L->data[j];
                L->data[j] = L->data[j+1];
                L->data[j+1] = tmp;
            }
        }
    }
    return comps;
}

/* -------- Selection Sort (por prioridade desc) ------- */
long selection_sort_prioridade_desc(SeqList* L){
    long comps=0;
    for(int i=0;i<L->size-1;i++){
        int best=i;
        for(int j=i+1;j<L->size;j++){
            comps++;
            if(cmp_prioridade_desc(&L->data[j], &L->data[best]) > 0) best=j;
        }
        if(best!=i){
            Item tmp = L->data[i];
            L->data[i]=L->data[best];
            L->data[best]=tmp;
        }
    }
    return comps;
}

/* --------- Busca Binária por nome (iterativa) --------- */
/* Pré-condição: lista ordenada por nome (bubble_sort_nome antes) */
int bsearch_nome_iter(const SeqList* L, const char* nome, long* comps){
    int lo=0, hi=L->size-1;
    while(lo<=hi){
        int mid = lo + (hi-lo)/2;
        (*comps)++;
        int c = strcmp(L->data[mid].nome, nome);
        if(c==0) return mid;
        if(c<0) lo=mid+1; else hi=mid-1;
    }
    return -1;
}

/* --------- Busca Binária por nome (recursiva) --------- */
int bsearch_nome_rec_(const SeqList* L, const char* nome, int lo, int hi, long* comps){
    if(lo>hi) return -1;
    int mid = lo + (hi-lo)/2;
    (*comps)++;
    int c = strcmp(L->data[mid].nome, nome);
    if(c==0) return mid;
    if(c<0) return bsearch_nome_rec_(L,nome,mid+1,hi,comps);
    return bsearch_nome_rec_(L,nome,lo,mid-1,comps);
}
int bsearch_nome_rec(const SeqList* L, const char* nome, long* comps){
    return bsearch_nome_rec_(L, nome, 0, L->size-1, comps);
}

/* ---------------- Lista Encadeada ---------------- */
typedef struct Node {
    Item item;
    struct Node* next;
} Node;

Node* ll_push_front(Node* head, Item x){
    Node* n = (Node*)malloc(sizeof(Node));
    n->item = x;
    n->next = head;
    return n;
}

Node* ll_remover_por_nome(Node* head, const char* nome, int* ok){
    *ok = 0;
    Node *prev=NULL, *cur=head;
    while(cur){
        if(strcmp(cur->item.nome,nome)==0){
            *ok=1;
            if(prev) prev->next = cur->next;
            else head = cur->next;
            free(cur);
            return head;
        }
        prev=cur; cur=cur->next;
    }
    return head;
}

int ll_busca_sequencial(Node* head, const char* nome, long* comps){
    int pos=0;
    for(Node* p=head; p; p=p->next){
        (*comps)++;
        if(strcmp(p->item.nome,nome)==0) return pos;
        pos++;
    }
    return -1;
}

void ll_listar(Node* head){
    int i=0; printf("Inventario (lista encadeada):\n");
    for(Node* p=head; p; p=p->next){
        printf("[%3d]", i++); print_item(&p->item);
    }
}

/* -------------- Utilidades -------------- */
Item novo_item(const char* nome, ItemTipo t, int prioridade){
    Item x; strncpy(x.nome, nome, NOME_MAX-1);
    x.nome[NOME_MAX-1]='\0';
    x.tipo = t; x.prioridade = prioridade;
    return x;
}

int tem_para_fuga(const SeqList* L){
    int temAl=0, temAr=0, temFe=0, somaP=0;
    for(int i=0;i<L->size;i++){
        Item it = L->data[i];
        if(it.tipo==ALIMENTO) temAl=1;
        if(it.tipo==ARMA) temAr=1;
        if(it.tipo==FERRAMENTA) temFe=1;
        somaP += it.prioridade;
    }
    // Exemplo de condição de vitória:
    return temAl && temAr && temFe && (somaP >= 120);
}

/* -------------- Bench simples: vetor vs lista -------------- */
void benchmark_busca(SeqList* L, Node* head, const char* alvo){
    long comps_seq=0, comps_ll=0;
    clock_t a,b;

    // Busca seq no vetor (sem binária, para comparação justa com a encadeada)
    a=clock();
    int posV = seq_busca_sequencial_nome(L, alvo, &comps_seq);
    b=clock();
    double tV = (double)(b-a)/CLOCKS_PER_SEC;

    // Busca seq na encadeada
    a=clock();
    int posL = ll_busca_sequencial(head, alvo, &comps_ll);
    b=clock();
    double tL = (double)(b-a)/CLOCKS_PER_SEC;

    printf("== Benchmark de busca pelo nome \"%s\"\\n", alvo);
    printf("Vetor: pos=%d, comps=%ld, tempo=%.6fs\\n", posV, comps_seq, tV);
    printf("Lista: pos=%d, comps=%ld, tempo=%.6fs\\n", posL, comps_ll, tL);
}

/* -------------- Menu / Jogo -------------- */
int ler_int(const char* msg){
    int x; printf("%s", msg); scanf("%d", &x); return x;
}
void ler_str(const char* msg, char* buf, int n){
    printf("%s", msg); scanf(" %31[^\\n]", buf);
}

int main(void){
    SeqList inv; seq_init(&inv);
    Node* enc = NULL;

    // Alguns itens iniciais
    seq_inserir_fim(&inv, novo_item("KitMedico", ALIMENTO, 30));
    seq_inserir_fim(&inv, novo_item("Faca", ARMA, 25));
    seq_inserir_fim(&inv, novo_item("Martelo", FERRAMENTA, 40));
    enc = ll_push_front(enc, novo_item("Barrinha", ALIMENTO, 15));
    enc = ll_push_front(enc, novo_item("Pistola", ARMA, 45));

    int opc;
    do{
        printf("\\n===== FREE FIRE – Sobrevivencia (C) =====\\n");
        printf("1) Listar inventario (vetor)\\n");
        printf("2) Pegar item (insere no vetor)\\n");
        printf("3) Dropar item (remove por indice do vetor)\\n");
        printf("4) Ordenar por NOME (Bubble) e mostrar comparacoes\\n");
        printf("5) Ordenar por PRIORIDADE desc (Selection) e mostrar comparacoes\\n");
        printf("6) Buscar por NOME (Linear no vetor)\\n");
        printf("7) Buscar por NOME (Binaria ITERATIVA)\\n");
        printf("8) Buscar por NOME (Binaria RECURSIVA)\\n");
        printf("9) Mostrar lista encadeada\\n");
        printf("10) Inserir na lista encadeada (push front)\\n");
        printf("11) Remover da lista encadeada por nome\\n");
        printf("12) Benchmark: comparar busca vetor vs lista\\n");
        printf("13) Tentar FUGA da ilha\\n");
        printf("0) Sair\\n");
        opc = ler_int("Escolha: ");

        if(opc==1){
            seq_listar(&inv);
        } else if(opc==2){
            char nome[32]; int t,p;
            ler_str("Nome do item: ", nome, 32);
            printf("Tipo (0=ALIMENTO,1=ARMA,2=FERRAMENTA): ");
            scanf("%d",&t);
            p = ler_int("Prioridade (1..100): ");
            if(seq_inserir_fim(&inv, novo_item(nome,(ItemTipo)t,p)))
                printf("OK: item inserido no vetor.\\n");
            else printf("Falha: inventario cheio.\\n");
        } else if(opc==3){
            int idx = ler_int("Indice para remover: ");
            if(seq_remover_indice(&inv, idx)) printf("OK: removido.\\n");
            else printf("Indice invalido.\\n");
        } else if(opc==4){
            long c = bubble_sort_nome(&inv);
            printf("Ordenado por NOME (Bubble). Comparacoes: %ld\\n", c);
        } else if(opc==5){
            long c = selection_sort_prioridade_desc(&inv);
            printf("Ordenado por PRIORIDADE desc (Selection). Comparacoes: %ld\\n", c);
        } else if(opc==6){
            char nome[32]; ler_str("Nome a procurar (linear): ", nome, 32);
            long comps=0;
            int pos = seq_busca_sequencial_nome(&inv, nome, &comps);
            printf("Linear: pos=%d, comps=%ld\\n", pos, comps);
        } else if(opc==7){
            char nome[32]; ler_str("Nome a procurar (binaria ITER): ", nome, 32);
            long comps=0;
            int pos = bsearch_nome_iter(&inv, nome, &comps);
            printf("Binaria(ITER): pos=%d, comps=%ld (lembre: precisa estar ordenado por NOME!)\\n", pos, comps);
        } else if(opc==8){
            char nome[32]; ler_str("Nome a procurar (binaria REC): ", nome, 32);
            long comps=0;
            int pos = bsearch_nome_rec(&inv, nome, &comps);
            printf("Binaria(REC): pos=%d, comps=%ld (lembre: precisa estar ordenado por NOME!)\\n", pos, comps);
        } else if(opc==9){
            ll_listar(enc);
        } else if(opc==10){
            char nome[32]; int t,p;
            ler_str("Nome do item: ", nome, 32);
            printf("Tipo (0=ALIMENTO,1=ARMA,2=FERRAMENTA): ");
            scanf("%d",&t);
            p = ler_int("Prioridade (1..100): ");
            enc = ll_push_front(enc, novo_item(nome,(ItemTipo)t,p));
            printf("OK: inserido na lista encadeada (frente).\\n");
        } else if(opc==11){
            char nome[32]; ler_str("Nome para remover (lista): ", nome, 32);
            int ok=0; enc = ll_remover_por_nome(enc, nome, &ok);
            printf(ok? "Removido.\\n":"Nao encontrado.\\n");
        } else if(opc==12){
            char nome[32]; ler_str("Nome-alvo para benchmark: ", nome, 32);
            benchmark_busca(&inv, enc, nome);
        } else if(opc==13){
            if(tem_para_fuga(&inv)) printf("SUCESSO! Voce construiu a torre e escapou da ilha!\\n");
            else printf("Ainda falta recurso (precisa 1 de cada tipo e prioridade total >= 120).\\n");
        }
    }while(opc!=0);

    // liberar lista encadeada
    while(enc){ Node* t = enc; enc=enc->next; free(t); }
    return 0;
}
