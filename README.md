# 🃏 Blackjack em C

Este é um projeto em linguagem C que simula o jogo de cartas **Blackjack (21)**. O jogo inclui um jogador humano, bots fictícios controlados por threads e um dealer (a casa). O objetivo é chegar o mais próximo possível de 21 pontos sem ultrapassá-los.

## 📋 Funcionalidades

- Dois bots (threads) que jogam em ordem após o jogador
- Dealer que segue as regras clássicas do Blackjack
- Sistema de apostas com saldo
- Embaralhamento e distribuição de cartas
- Interface de texto amigável
- Uso de `pthread` para simular concorrência com bots, jogador e dealer

## 🎮 Como Jogar

- Você começa com um saldo inicial de R$100.
- Aposta mínima: R$5 (múltiplos de 5).
- Você escolhe se quer comprar mais cartas ou parar.
- Após você, os bots jogam automaticamente.
- Em seguida, o dealer joga com base nas regras da casa.
- O resultado é exibido e você decide se quer continuar jogando.

## 🧵 Threads

Este projeto utiliza `pthread` para:

- Executar a jogada do jogador real
- Rodar cada bot em sequência, utilizando semaforização.
- Gerenciar a jogada automática do dealer


## 📁 Estrutura do Projeto

```
BlackJack/
├── include/            # Arquivos de cabeçalho (.h)
│   ├── baralho.h
│   ├── bots.h
│   ├── dealer.h
│   ├── interfaces.h
│   ├── jogador.h
│   ├── jogo.h
│   └── utils.h
├── src/                # Código-fonte (.c)
│   ├── baralho.c
│   ├── bots.c
│   ├── dealer.c
│   ├── interfaces.c
│   ├── jogador.c
│   ├── jogo.c
│   └── main.c
└── README.md
```
<br>
<br>

# 🚀 Como Compilar e Executar
### 📌 Requisitos

- Compilador C com suporte a C11 ou superior
- Biblioteca `pthread` (Linux ou compatível)

### Linux / WSL (Windows Subsystem for Linux)

Certifique-se de ter o compilador GCC:

```bash
sudo apt update
sudo apt install build-essential
```

Acesse a pasta onde o projeto está (coloque o seu caminho):
```bash
cd "/mnt/c/Users/.../BlackJack"
```

**Compilação:**

```bash
gcc -o blackjack src/*.c -Iinclude -pthread
```

**Executar:**
```bash
./blackjack
```
> ⚠️aviso: O jogo deve ser compilado e rodado dentro do Ubuntu (WSL) — e não em um terminal Windows nativo com MinGW, pois esse não suporta pthread.
--- 
<br>
<br>

# 💻​ Instalação WSL + Ubuntu (para rodar no Windows):

## 1. Abra o terminal PowerShell

## 2. Instalar o WSL

```bash
wsl --install
```
> 💡 Esse comando instala o WSL e, normalmente, também o Ubuntu automaticamente.


### ⚠️ Caso o Ubuntu NÃO seja instalado automaticamente:
- Instale manualmente com:
```bash
wsl --install -d Ubuntu
```
> Ou abra a Microsoft Store, pesquise por "Ubuntu" e instale a versão padrão.
--- 
## 3. Reinicie o computador quando solicitado

## 4. Após a reinicialização, abra o terminal do Ubuntu:
- Escolha um nome de usuário
- Defina uma senha

### ​✅​ Agora o Ubuntu está funcionando via WSL!
<br>

## 5. 🔧 Instalar GCC e ferramentas de compilação:

No terminal do Ubuntu:
```bash
sudo apt update
sudo apt install build-essential -y
```
### ​✅​ Tudo Certo! Agora compile e execute o projeto.

--- 
<br>
<br>

# 🛠️ Abrindo o Projeto no VS Code
programar e editar o projeto diretamente no Visual Studio Code:

## 1. Instale as Extensões Necessárias no VS Code
- Remote - WSL

- C/C++

## 2. Abra o Projeto via WSL no VS Code

Abra o Ubuntu e vá até a pasta do seu projeto:
```bash
cd /mnt/c/Users/SEU_USUARIO/Documentos/BlackJack
```
Agora digite:
```bash
code .
```
## 2.1 Direto pelo VS Code

- 1 Abra o VS Code normalmente

- 2 Pressione **"Ctrl + Shift + P"** para abrir a paleta de comandos

- 3 Digite:

```bash
Remote-WSL: Open Folder in WSL
```

- 4 Navegue até a pasta do seu projeto:

```bash
/mnt/c/Users/SEU_USUARIO/Documentos/BlackJack
```

<!-- 
## 3. Adicione o seguinte arquivo `.vscode/c_cpp_properties.json`:


```json
{
  "configurations": [
    {
      "name": "WSL",
      "includePath": [
        "${workspaceFolder}/include",
        "/usr/include",
        "/usr/local/include"
      ],
      "defines": [],
      "compilerPath": "/usr/bin/gcc",
      "cStandard": "c11",
      "intelliSenseMode": "linux-gcc-x64"
    }
  ],
  "version": 4
}
> ⚠️ Isso informa ao VS Code que os arquivos .h estão na pasta /include

 -->

<br>
<br>

# 📄 Licença

Projeto final da matéria de **Sistemas Operacionais**

Engenharia de Software | Universidade Católica de Brasília

Este projeto é de livre uso acadêmico.

> Desenvolvido por:
- João Ricardo Jales Cirino 
- Felipe Lima Duarte
- Henrique Vinha Rocha
- Gustavo Domingues de Sousa
---