<h1 align="center">get_next_line</h1>

<p align="center">
  <img src="https://img.shields.io/badge/linguagem-C-blue.svg" alt="Linguagem">
  <img src="https://img.shields.io/badge/42-School-black.svg" alt="42 School">
  <img src="https://img.shields.io/badge/status-completo-brightgreen.svg" alt="Status">
</p>

<p align="center">
  Uma função que lê uma linha por vez de qualquer file descriptor — de forma eficiente, com estado persistente entre chamadas.
</p>

<p align="center">
  <a href="README.md">🇺🇸 Read in English</a>
</p>

---

## Por que este projeto importa

> "Este projeto me ensinou como o buffering de I/O funciona no nível do sistema operacional — por que ler de um arquivo ou socket não é instantâneo, como buffers evitam chamadas de sistema redundantes, e como variáveis estáticas podem manter estado entre chamadas de função em C. São conceitos presentes em toda aplicação backend ou de sistemas do mundo real."

Entender `read()`, file descriptors e gerenciamento de buffer é fundamental para quem trabalha com programação de rede, processamento de arquivos ou I/O de alta performance.

---

## O que foi construído

Uma única função `get_next_line(int fd)` que:

- Lê de **qualquer file descriptor** (arquivos, stdin, pipes, sockets)
- Retorna uma linha completa por chamada, incluindo o `\n`
- Retorna `NULL` quando o arquivo termina ou ocorre um erro
- Usa um buffer estático interno para evitar re-leitura de bytes já consumidos
- Funciona corretamente com **qualquer `BUFFER_SIZE`** — de 1 byte a milhares

### Bônus
A versão bônus suporta **múltiplos file descriptors simultaneamente**, mantendo estado independente por fd. Isso espelha como servidores reais lidam com conexões concorrentes.

---

## Um detalhe técnico que se destaca

O uso de um `static char stash[]` combinado com a função `move_remains()` para mover os bytes não consumidos para o início do buffer é uma abordagem elegante que evita alocação dinâmica do stash, ao mesmo tempo que trata corretamente linhas que se estendem por múltiplas chamadas `read()`. Esse padrão é comum em bibliotecas de I/O em produção.

---

## Como usar

```bash
git clone https://github.com/gustavofsousa/get_next_line_42.git
cd get_next_line_42
```

Inclua os arquivos no seu projeto:

```c
#include "get_next_line.h"
```

Compile com o `BUFFER_SIZE` desejado:

```bash
gcc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c seu_main.c
```

### Exemplo de uso

```c
int fd = open("arquivo.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## Estrutura do projeto

```
get_next_line_42/
├── get_next_line.c          # Lógica principal
├── get_next_line.h          # Header
├── get_next_line_utils.c    # Funções auxiliares
├── get_next_line_bonus.c    # Suporte a múltiplos fds
├── get_next_line_bonus.h
└── get_next_line_utils_bonus.c
```

---

## Habilidades demonstradas

- I/O e chamadas de sistema (`read`, `open`, `close`)
- Variáveis estáticas e estado persistente de função
- Gerenciamento de buffer e leituras parciais
- Gerenciamento de memória (sem vazamentos entre chamadas)
- Tratamento de casos extremos: linhas vazias, EOF sem newline, arquivos grandes

---

## Licença

Este projeto foi desenvolvido como parte do currículo da [42 School](https://42.fr).

---

<p align="center">Feito com ☕ na 42 Rio de Janeiro</p>
