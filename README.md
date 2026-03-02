# 🧱 Simulador de Tetris em C  
### Estruturas de Dados: Fila Circular (FIFO) e Pilha (LIFO)

Este projeto é uma simulação da lógica de gerenciamento de peças do jogo **Tetris**, desenvolvido em linguagem C com foco na aplicação prática de **estruturas de dados fundamentais**.

O objetivo principal é reforçar conceitos de:

- Fila Circular (FIFO)
- Pilha Linear (LIFO)
- Organização de memória com arrays estáticos
- Programação estruturada
- Separação de responsabilidades em funções

---

## 🎯 Objetivo do Projeto

Simular:

- 🔄 A fila de próximas peças do jogo (Fila Circular)
- 📦 O sistema de reserva de peças (Pilha)
- 🎮 A jogabilidade básica via terminal

O projeto foi desenvolvido como prática acadêmica para consolidar conhecimentos em Estruturas de Dados na disciplina de Algoritmos e Programação.

---

## 🧩 Estrutura do Sistema

### 🔹 1. Modelagem da Peça

```c
typedef struct {
    char tipo;   // 'I', 'O', 'T', 'L'
    int id;      
} Peca;
