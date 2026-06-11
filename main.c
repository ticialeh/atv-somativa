#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

// Função para calcular o total de registros no arquivo binário
int obter_total_registros(FILE* f) {
    fseek(f, 0, SEEK_END);
    return (int)(ftell(f) / sizeof(RegistroConta));
}

// SUA ARTE ASCII INTEGRADA: Tela de abertura do banco
void mostrar_intro_edward(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("EDWARD CULLEN\n");
    printf("                        @@@@@@@@@@@@@@@@@@@@@@@@                    \n");
    printf("              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@                    \n");
    printf("           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 \n");
    printf("         @@@@@@@%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
    printf("       @@@@@@@@@%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n");
    printf("    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%@@@%%@@@@@%%@@@         \n");
    printf("   @@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@%%@@@@@@@@@@@@@          \n");
    printf("  @@@@@@@@@@@@@@@@@@@@@@@@%%@@@@@@@@@%%%%%@@@@@@@@@%%@@@#@         \n");
    printf("  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+          \n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%#@         \n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%@%%        \n");
    printf(" %%%%@@@@@@@@@@@@@@@@@@@@@@@%%%%%%%%%%@@@@@@%%@@@@@@@@@@@@@@@%%@       \n");
    printf("  %%@@@@@@@@@@@@@@@@%%%%#*+=======+*##*+++*#%%@@@@@@@@@@@@#%%@       \n");
    printf("  %%%%@@@@@@@@@@@#*+==--------:-----==--=+*#%%@@@@@@@@@%%#@       \n");
    printf("   ##%%%%@@@@@@@%%*+===---:::::::::--------==+*#%%@@@@@@@%%%%        \n");
    printf("   %%%%@%%%%@@@@@%%*+====----::::::::--------====+#@@@@@%%%%#        \n");
    printf("   @%%%%%%%@@@@@#+======----:::::::-------====-=+%%@@@@%%%%         \n");
    printf("    %%#%%##@@@%%#+====-------::::::-------=======#@%%%%%         \n");
    printf("    %%%%@@%%#@@@%%*+=====---:::::::::--------===-==+%%@@@%%          \n");
    printf("    @@%%@@%%@@%%#+======-----:::::::---------=----=#@@@            \n");
    printf("    -=+#@@@%%*+========-------:----------=====-:-*@%%            \n");
    printf("    *##+*@@#====+*%%%%%%%##**=--=------==+*####*=-*%%* \n");
    printf("    -+**##%%*==+*###%%%%@@@@@%%*+===++#%%@@@@@@@@%%=#%%* \n");
    printf("    =-++#%%*-=+***%%@#%%%%%*%%##*+--=*#%%%%%%@%%#%%#*-##             \n");
    printf("     +-=*#%%=-=====+*#*****+====-:-+=++++****++=-##            \n");
    printf("      -++#=-==============-===-:-=====+**+===--+               \n");
    printf("       -=*=-====-----------==----============--#               \n");
    printf("       -=+===+====--------===----==+==-========                \n");
    printf("        #+=+++++====-----=+==---:--==--===++++* \n");
    printf("         :-+++++++===-----+==--::--:=-===++**+                 \n");
    printf("          -=+++++++===-----+##+=++**===++++*++                 \n");
    printf("          ===+++++====--------+###+=====++*++                  \n");
    printf("          ++++++++======---------========+++%%                  \n");
    printf("        @@%%++++++====*#*##%%######**#*++++@@@@                 \n");
    printf("      %%%%@@@@**++++++====+********#*+++++++%%@@@@@               \n");
    printf("     @%%@@@@@+*#*+++======++*######*+++++*%%@@@@@@%%               \n");
    printf("    **%%@@@@@++#%%#*+++=======--====+++++*+%%@@@@@@%%#              \n");
    printf("   ***%%@@@@#*+**#%%#*++==---------====+#*+%%@@@@@@@#*@#            \n");
    printf("  ***#%%@@%%###****##%%#*+====----====+*%%#*#@@@@@@@@%%*##%%%%         \n");
    printf(" @#%%##**#%%@@%%*********#%%%%#*++++++***#%%####%%@@@@@@@%%#*#%%####%%      \n");
    printf("-------------------------------------------------------------------------\n");
    printf("            BEM-VINDO AO CULLEN & QUILEUTE CO. MUTUAL BANK               \n");
    printf("-------------------------------------------------------------------------\n");
    printf("Pressione ENTER para acessar o sistema de contas...");
    getchar();
}

// Opção 5: Função de listagem limpa (usada também pelo rewind)
void listar_registros_impressao(FILE* f) {
    int total = obter_total_registros(f);
    if (total == 0) {
        printf("\n[AVISO] O arquivo de contas esta vazio.\n");
        return;
    }

    printf("\n%-5s %-8s %-25s %-12s %-10s\n", "Pos", "Conta", "Titular", "Saldo", "Status");
    printf("-----------------------------------------------------------------\n");

    RegistroConta c;
    for (int i = 0; i < total; i++) {
        fseek(f, i * sizeof(RegistroConta), SEEK_SET);
        fread(&c, sizeof(RegistroConta), 1, f);

        if (c.codigo_conta == ID_LIVRE) {
            printf("%-5d %-8s %-25s %-12s %-10s\n", i, "---", "(Espaco Livre)", "---", "Livre");
        } else {
            printf("%-5d %-8d %-25s %-12.2f %-10s\n", 
                   i, c.codigo_conta, c.nome_titular, c.reserva_ouro, 
                   c.status_imortal ? "Ativa" : "Encerrada");
        }
    }
    printf("-----------------------------------------------------------------\n");
}

// Opção 1: Cadastrar cliente em posição específica
void cadastrar_membro(void) {
    FILE* f = fopen(ARQUIVO_BANCO, "r+b");
    if (!f) f = fopen(ARQUIVO_BANCO, "w+b");
    if (!f) return;

    int pos;
    RegistroConta nova;

    printf("\n--- 1. CADASTRAR CLIENTE (POSICAO ESPECIFICA) ---\n");
    printf("Digite a posicao desejada no arquivo (0 = primeira): ");
    scanf("%d%*c", &pos);

    int total = obter_total_registros(f);

    if (pos < total) {
        fseek(f, pos * sizeof(RegistroConta), SEEK_SET);
        fread(&nova, sizeof(RegistroConta), 1, f);
        if (nova.status_imortal == 1) {
            printf("❌ ERRO: A posicao %d ja esta ocupada por %s\n", pos, nova.nome_titular);
            fclose(f);
            return;
        }
    }

    printf("Numero da Conta: ");
    scanf("%d%*c", &nova.codigo_conta);
    printf("Nome do Titular: ");
    fgets(nova.nome_titular, TAM_NOME, stdin);
    nova.nome_titular[strcspn(nova.nome_titular, "\n")] = '\0';
    printf("Saldo Inicial: ");
    scanf("%f%*c", &nova.reserva_ouro);
    nova.status_imortal = 1;

    if (pos > total) {
        RegistroConta vazio = {ID_LIVRE, "", 0.0f, 0};
        for (int i = total; i < pos; i++) {
            fseek(f, i * sizeof(RegistroConta), SEEK_SET);
            fwrite(&vazio, sizeof(RegistroConta), 1, f);
        }
    }

    fseek(f, pos * sizeof(RegistroConta), SEEK_SET);
    fwrite(&nova, sizeof(RegistroConta), 1, f);
    printf("✔️ Cliente gravado com sucesso na posicao %d!\n", pos);

    fclose(f);
}

// Opção 2: Consultar cliente pelo número da conta
void consultar_membro(void) {
    FILE* f = fopen(ARQUIVO_BANCO, "rb");
    if (!f) { printf("\n[ERRO] Nenhum arquivo de dados encontrado.\n"); return; }

    int busca_id, achou = 0;
    printf("\n--- 2. CONSULTAR CLIENTE POR CONTA ---\n");
    printf("Digite o numero da conta para buscar: ");
    scanf("%d%*c", &busca_id);

    int total = obter_total_registros(f);
    RegistroConta c;

    for (int i = 0; i < total; i++) {
        fseek(f, i * sizeof(RegistroConta), SEEK_SET);
        fread(&c, sizeof(RegistroConta), 1, f);

        if (c.codigo_conta == busca_id && c.status_imortal == 1) {
            printf("\n✔️ Cliente Encontrado:\n");
            printf(" -> Posicao no Arquivo: %d\n", i);
            printf(" -> Nome do Titular   : %s\n", c.nome_titular);
            printf(" -> Saldo Atual       : R$ %.2f\n", c.reserva_ouro);
            achou = 1;
            break;
        }
    }

    if (!achou) printf("❌ Conta #%d nao encontrada ou esta desativada.\n", busca_id);
    fclose(f);
}

// Opção 3: Atualizar o saldo de um cliente
void atualizar_reserva(void) {
    FILE* f = fopen(ARQUIVO_BANCO, "r+b");
    if (!f) return;

    int busca_id, achou = 0;
    printf("\n--- 3. ATUALIZAR SALDO DE CLIENTE ---\n");
    printf("Digite o numero da conta: ");
    scanf("%d%*c", &busca_id);

    int total = obter_total_registros(f);
    RegistroConta c;

    for (int i = 0; i < total; i++) {
        fseek(f, i * sizeof(RegistroConta), SEEK_SET);
        fread(&c, sizeof(RegistroConta), 1, f);

        if (c.codigo_conta == busca_id && c.status_imortal == 1) {
            printf("Titular: %s | Saldo Atual: R$ %.2f\n", c.nome_titular, c.reserva_ouro);
            printf("Digite o novo valor do saldo: ");
            scanf("%f%*c", &c.reserva_ouro);

            fseek(f, i * sizeof(RegistroConta), SEEK_SET);
            fwrite(&c, sizeof(RegistroConta), 1, f);
            printf("✔️ Saldo atualizado com sucesso!\n");
            achou = 1;
            break;
        }
    }

    if (!achou) printf("❌ Conta nao encontrada.\n");
    fclose(f);
}

// Opção 4: Encerra conta (remover cliente)
void encerrar_membro(void) {
    FILE* f = fopen(ARQUIVO_BANCO, "r+b");
    if (!f) return;

    int busca_id, achou = 0;
    printf("\n--- 4. ENCERRAR CONTA (REMOVER CLIENTE) ---\n");
    printf("Digite o numero da conta para encerrar: ");
    scanf("%d%*c", &busca_id);

    int total = obter_total_registros(f);
    RegistroConta c;

    for (int i = 0; i < total; i++) {
        fseek(f, i * sizeof(RegistroConta), SEEK_SET);
        fread(&c, sizeof(RegistroConta), 1, f);

        if (c.codigo_conta == busca_id && c.status_imortal == 1) {
            c.status_imortal = 0; 
            fseek(f, i * sizeof(RegistroConta), SEEK_SET);
            fwrite(&c, sizeof(RegistroConta), 1, f);
            printf("✔️ Conta de %s encerrada com sucesso.\n", c.nome_titular);
            achou = 1;
            break;
        }
    }

    if (!achou) printf("❌ Conta nao encontrada.\n");
    fclose(f);
}

// Opção 5: Listar todos os clientes
void listar_todos(void) {
    FILE* f = fopen(ARQUIVO_BANCO, "rb");
    if (!f) { printf("\n[AVISO] Arquivo nao inicializado ainda.\n"); return; }
    printf("\n--- 5. LISTAGEM DE CLIENTES ---");
    listar_registros_impressao(f);
    fclose(f);
}

// Opção 6: Restaurar a leitura do arquivo do início com rewind()
void executar_rewind(void) {
    FILE* f = fopen(ARQUIVO_BANCO, "rb");
    if (!f) { printf("\n[AVISO] Arquivo nao inicializado ainda.\n"); return; }

    printf("\n--- 6. RESTAURANDO LEITURA DO INICIO VIA REWIND() ---\n");
    
    rewind(f); 
    
    printf("Ponteiro resetado. Repetindo listagem a partir do comeco:\n");
    listar_registros_impressao(f);
    
    fclose(f);
}

// --- MAIN (MENU DO SISTEMA VIA TERMINAL) ---
int main(void) {
    int opcao;

    // Dispara a introdução com a sua arte ASCII assim que o programa abre
    mostrar_intro_edward();

    do {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("====================================================\n");
        printf("         FORKS BANK - MANUTENCAO DE CONTAS          \n");
        printf("====================================================\n");
        printf("  1. Cadastrar cliente em posicao especifica\n");
        printf("  2. Consultar cliente pelo numero da conta\n");
        printf("  3. Atualizar o saldo de um cliente\n");
        printf("  4. Encerra conta (remover cliente)\n");
        printf("  5. Listar todos os clientes\n");
        printf("  6. Restaurar leitura do inicio com rewind()\n");
        printf("  7. Encerrar\n");
        printf("====================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d%*c", &opcao);

        switch(opcao) {
            case 1: cadastrar_membro(); break;
            case 2: consultar_membro(); break;
            case 3: atualizar_reserva(); break;
            case 4: encerrar_membro(); break;
            case 5: listar_todos(); break;
            case 6: executar_rewind(); break;
            case 7: printf("\nEncerrando o sistema de Forks. Ate logo!\n"); break;
            default: printf("\n⚠️ Opcao invalida! Tente novamente.\n"); break;
        }

        if (opcao != 7) {
            printf("\nPressione ENTER para voltar ao menu...");
            getchar();
        }

    } while(opcao != 7);

    return 0;
}