# Free Fire – Mini Game em C (Desafio Tema 2)

Mini game em **linguagem C** que simula um modo de sobrevivência inspirado em Free Fire, focado em **estruturas de dados** (vetor e lista encadeada), **operações de inserção/remoção/percorrimento**, **buscas linear e binária (iterativa e recursiva)** e **métodos de ordenação** (Bubble e Selection) com **contagem de comparações**.

> Estrutura e organização no mesmo estilo do desafio 1 (War): pastas claras, `README` completo, `Makefile`, `.gitignore` e código pronto para compilar.

---

 Objetivos do projeto
- Implementar **lista linear (vetor)** e **lista encadeada**;
- Executar **inserção, remoção, percorrimento e busca sequencial**;
- Comparar **vetor vs. lista encadeada** (comparações e tempo);
- Implementar **Bubble Sort** (por nome) e **Selection Sort** (por prioridade desc);
- Implementar **Busca Binária** (iterativa e recursiva) por nome (em dados ordenados);
- Simular uma checagem de **condição de escape** (requisitos mínimos no inventário).

---

 Estrutura de pastas
```
freefire-desafio-c/
├── src/
│   └── main.c          # código completo do mini game
├── .gitignore          # ignora artefatos de build
├── Makefile            # build simples (gcc)
└── README.md
```

---

 Como compilar e executar
 Via Makefile (recomendado)
```bash
make
./freefire
```
Limpar artefatos:
```bash
make clean
```

### Via gcc direto
```bash
gcc -O2 -Wall -Wextra -o freefire src/main.c
./freefire
```

> Requer GCC/Clang e um terminal. Testado com `gcc`.

---

 Menu do jogo
```
1) Listar inventario (vetor)
2) Pegar item (insere no vetor)
3) Dropar item (remove por indice do vetor)
4) Ordenar por NOME (Bubble) e mostrar comparacoes
5) Ordenar por PRIORIDADE desc (Selection) e mostrar comparacoes
6) Buscar por NOME (Linear no vetor)
7) Buscar por NOME (Binaria ITERATIVA)
8) Buscar por NOME (Binaria RECURSIVA)
9) Mostrar lista encadeada
10) Inserir na lista encadeada (push front)
11) Remover da lista encadeada por nome
12) Benchmark: comparar busca vetor vs lista
13) Tentar FUGA da ilha
0) Sair
```

- **Ordenar por nome** (opção 4) **antes** de usar as buscas binárias (7 e 8).
- A **fuga** exige pelo menos 1 item de cada tipo (ALIMENTO, ARMA, FERRAMENTA) e soma de prioridades ≥ **120**.

---

 Busca e Ordenação
- **Busca sequencial** no vetor: `seq_busca_sequencial_nome`
- **Busca binária** (iterativa e recursiva): `bsearch_nome_iter` e `bsearch_nome_rec`  
  *Pré-condição:* vetor **ordenado por nome** (`bubble_sort_nome`).
- **Bubble Sort por nome**: usa a relação `vetor[j] > vetor[j+1]` (com contagem de comparações).
- **Selection Sort por prioridade (desc)**: ordena da maior para a menor prioridade.

---

 Comparação Vetor × Lista Encadeada
A função `benchmark_busca` faz a busca **linear** em ambos e exibe:
- posição encontrada,
- **número de comparações**,
- **tempo** da operação (usando `clock()`).
Isso ilustra, de forma simples, as diferenças de percurso e acesso (contíguo vs. encadeado).

---

##  Observações didáticas
- Vetor tem **acesso indexado O(1)** e bom cache; inserções/remoções no meio custam deslocamento.
- Lista encadeada tem inserções/remoções locais baratas, mas **acesso sequencial O(n)** e pior localidade de cache.
- **Busca binária** só é válida em **dados ordenados** e com **acesso aleatório O(1)** (por isso aplicada no vetor).

---

##  Licença
MIT — livre para estudar, modificar e reutilizar com créditos.

---

##  Créditos
Projeto educacional do desafio *Free Fire — Tema 2*. Feito em C, com foco em estruturas de dados e análise de algoritmos.
