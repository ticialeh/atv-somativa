#ifndef CONFIG_H
#define CONFIG_H

#define ARQUIVO_BANCO "contas_forks.dat"
#define TAM_NOME 50
#define ID_LIVRE -1

// Estrutura de tamanho fixo exigida pelo enunciado
typedef struct {
    int codigo_conta;
    char nome_titular[TAM_NOME];
    float reserva_ouro;
    int status_imortal; // 1 = Ativa, 0 = Encerrada
} RegistroConta;

#endif