# 🌲 Cullen & Quileute Co. - Forks Mutual Bank

<p align="center">
  <img src="capa.png" alt="Forks Bank Capa" width="750px"/>
</p>

<p align="center">
  <strong>Sistema de Manutenção de Contas Bancárias em C Puro</strong><br>
  Gerenciamento de registros de tamanho fixo utilizando manipulação direta de arquivos binários.
</p>

---

## 🎭 Sobre o Projeto
O sistema foi desenvolvido como uma solução em C puro para gerenciar as finanças e territórios de Forks, divididos entre o Clã Cullen e a Tribo Quileute. O programa utiliza persistência contígua em disco para garantir que os dados fiquem salvos mesmo após o encerramento do terminal.

---

## 🚀 Funcionalidades Implementadas 

O sistema cumpre com rigor técnico todas as operações obrigatórias utilizando a biblioteca padrão `stdio.h`:

* **1. Cadastrar cliente em posição específica:** Calcula o deslocamento exato via `fseek` e grava os dados na posição indicada pelo usuário. Se a posição estiver ocupada por uma conta ativa, o sistema impede a gravação para proteger os dados.
* **2. Consultar cliente pelo número da conta:** Realiza uma busca sequencial no arquivo binário através de `fread`, localizando o titular e exibindo seu saldo.
* **3. Atualizar o saldo de um cliente:** Modifica diretamente o campo `reserva_ouro` do registro no arquivo físico utilizando `fwrite`.
* **4. Encerra conta (remover cliente):** Aplica uma remoção lógica mudando a flag `status_imortal` para `0` (Mortal/Inativa), preservando a estrutura de posições fixas do arquivo.
* **5. Listar todos os clientes:** Exibe no terminal uma tabela com todas as posições mapeadas do arquivo (tanto os clientes ativos quanto os espaços livres).
* **6. Restaurar leitura do início com `rewind()`:** Executa o reset explícito do ponteiro de leitura do arquivo físico para a posição inicial (`0`) para auditoria dos dados.

---

## 🛠️ Estrutura de Dados (`config.h`)

Os registros são gravados de forma sequencial no arquivo `contas_forks.dat` baseando-se na seguinte estrutura:

```c
typedef struct {
    int codigo_conta;           // Número único da conta
    char nome_titular[50];      // Nome do membro ou clã
    float reserva_ouro;         // Saldo da conta
    int status_imortal;         // Flag de ativação (1 = Ativa, 0 = Inativa)
} RegistroConta;
