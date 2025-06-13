
# 📚 Explicação dos Arquivos de Cabeçalho (`.h`)

Este documento descreve o propósito e a lógica de cada header (`.h`) usado no projeto Blackjack em C.

---

## 🔹 `baralho.h`
Responsável por gerenciar o **baralho de cartas** do jogo.

- `#define TAM_BARALHO 52`: Define que o baralho possui 52 cartas.
- `void inicializar_baralho()`: Inicializa o baralho padrão.
- `int comprar_carta()`: Retorna uma carta aleatória do baralho.
- `void embaralhar()`: Embaralha as cartas.

> Este módulo isola toda a lógica de gerenciamento do baralho.

---
## 🔹 `jogador.h`
Define a estrutura e funções para o jogador humano no jogo.

- `typedef struct JogadorInfo`: Estrutura que armazena as informações de cada jogador.
- `criarJogador()` Função para criar um jogador
- `rotina_jogador(void*)` :rotina da thread que controla as ações do jogador

--- 

## 🔹 `bots.h`
Controla os **jogadores bots**, que agem automaticamente.

- `#define NUM_BOTS 2`: Define que o jogo terá dois bots por padrão.
- `typedef struct BotsInfo`: Estrutura que armazena as informações de cada bot.
- `void distribuicao_cartas_iniciais_bots(...)`: Distribui cartas iniciais aos bots.
- `void inicializar_bots(...)`: Inicializa as estruturas dos bots.
- `void* rotina_bot(void*)`: Thread responsável por simular a jogada automática de cada bot.

> Usado para simular adversários fictícios com lógica automatizada via `pthread`.

---

## 🔹 `dealer.h`
Representa o **dealer (a casa)**.

- `typedef struct DealerInfo`: Estrutura que armazena as cartas e pontuação do dealer.
- `void* rotina_dealer(void*)`: Função em thread que executa a jogada do dealer automaticamente.

> O dealer segue regras fixas do Blackjack (ex: para ao atingir 17+).

---

## 🔹 `interface.h`
Responsável por exibir todas as **interfaces de texto** para o jogador.

- Contém funções como:
  - `tela_apresentacao()`, `tela_como_jogar()`, `tela_creditos()`
  - `tela_valor_aposta()`, `tela_cartas_iniciais_*`, `tela_pontuacao_final(...)`
- Usa as estruturas `JogadorInfo`, `DealerInfo` e `BotsInfo`.

> Isola a exibição visual do jogo e permite uma experiência mais amigável.

---

## 🔹 `jogo.h`
Contém a lógica principal de **uma partida individual (single player)**.

- `void game(...)`: Função principal que executa uma rodada do jogo.
- `double aposta(...)`: Lida com o valor da aposta do jogador.
- `void distribuicao_cartas_iniciais_*`: Distribui cartas para jogador e dealer.
- `void pontuacao_final(...)`: Avalia quem ganhou e ajusta o saldo.

> É o coração do jogo para um jogador humano contra dealer e bots.

---

## 🔹 `multiplayer.h`
Adiciona suporte a **modo multiplayer local**

- `#define MAX_JOGADORES 5`: Número máximo de jogadores.
- `void multiplayer()`: Controla a lógica geral do modo multiplayer.
- `void cadastrar_jogadores(...)`: Pede nome e inicializa os jogadores.
- `void apostas(...)`: Coleta as apostas individuais de cada jogador.
- `void tela_mesa(...)`: Exibe a mesa com todos os jogadores e dealer.
- `void resultados_rodada(...)`: Avalia os resultados e atualiza os saldos.
- `void resultado_partida(...)`: Resultado final da partida

> Essa camada amplia o jogo para mais jogadores reais e maior competição.

---

## 🔹 `utils.h`
Contém **funções utilitárias** e auxiliares usadas por vários módulos.

- `int calcular_pontuacao(...)`: Calcula a pontuação total de uma mão de cartas.
- `void imprimir_cartas(...)`: Mostra as cartas no terminal.
- `void imprimir_uma_carta(...)`: Mostra uma única carta no terminal.

> Ajuda a manter o código organizado, reutilizando funcionalidades comuns.

---

## 🔹 `main.c`
Arquivo principal que **inicia o jogo**.

- Executa a função `tela_apresentacao()` para receber dados iniciais do jogador.
- Exibe o menu principal com opções:

  - 1: Jogar no modo single player `game()`

  - 2: Jogar no modo multiplayer local `multiplayer()`

  - 3: Mostrar instruções `tela_como_jogar()`

  - 4: Exibir créditos `tela_creditos()`

  - 5: Sair do jogo

- Verifica se o jogador tem saldo suficiente para jogar antes de iniciar qualquer partida.

- Serve como ponto de entrada do programa, controlando o fluxo geral do jogo.

> Serve como ponto de entrada do programa, controlando o fluxo geral do jogo.
