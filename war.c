#include <stdio.h>
#include <string.h>

// Define o número fixo de territórios para o cadastro, conforme o requisito.
#define NUM_TERRITORIOS 5

/**
 * @brief Definição da estrutura Territorio.
 *
 * Esta struct agrupa informações relacionadas a um território:
 * nome (para identificação), cor do exército e número de tropas.
 */
typedef struct {
    char nome[30];  // Nome do território (máx. 29 caracteres + '\0')
    char cor[10];   // Cor do exército (máx. 9 caracteres + '\0')
    int tropas;     // Quantidade de tropas no território
} Territorio;

/**
 * @brief Função principal do programa.
 *
 * Responsável por gerenciar o cadastro e a exibição dos dados dos territórios.
 */
int main() {
    // Declaração de um vetor de structs Territorio.
    // O vetor 'cadastro_territorios' pode armazenar NUM_TERRITORIOS estruturas.
    Territorio cadastro_territorios[NUM_TERRITORIOS];
    int i; // Variável de controle para os laços

    printf("===========================================\n");
    printf("   🛡️ SISTEMA DE CADASTRO DE TERRITÓRIOS 🛡️\n");
    printf("===========================================\n");
    printf("  Por favor, insira os dados de %d territórios.\n\n", NUM_TERRITORIOS);

    // --- ENTRADA DE DADOS ---
    // Utilização de um laço 'for' para preencher os dados dos 5 territórios.
    // O laço itera de 0 a NUM_TERRITORIOS - 1 (ou seja, 5 vezes).
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Cadastro do Território #%d ---\n", i + 1);

        // USABILIDADE: Mensagens claras para orientar o usuário.
        // NOME DO TERRITÓRIO
        printf("Nome (máx. 29 caracteres): ");
        // Uso de scanf para ler o nome, limitando o número de caracteres para evitar buffer overflow
        // e limpando o buffer de entrada.
        if (scanf("%29s", cadastro_territorios[i].nome) != 1) {
             // Tratamento de erro básico
             printf("Erro na leitura do nome. Encerrando.\n");
             return 1;
        }


        // COR DO EXÉRCITO
        printf("Cor do Exército (máx. 9 caracteres): ");
        if (scanf("%9s", cadastro_territorios[i].cor) != 1) {
             printf("Erro na leitura da cor. Encerrando.\n");
             return 1;
        }

        // QUANTIDADE DE TROPAS
        printf("Quantidade de Tropas (número inteiro): ");
        // Uso de scanf para ler o número inteiro de tropas.
        if (scanf("%d", &cadastro_territorios[i].tropas) != 1) {
             printf("Erro na leitura das tropas. Encerrando.\n");
             return 1;
        }

        printf("\n");
    }

    // --- EXIBIÇÃO DE DADOS ---
    // O sistema exibe os dados logo após o preenchimento (requisito de desempenho).
    printf("===========================================\n");
    printf("     ✅ DADOS DOS TERRITÓRIOS CADASTRADOS ✅\n");
    printf("===========================================\n");

    // Utilização de um segundo laço 'for' para percorrer o vetor e exibir os dados.
    for (i = 0; i < NUM_TERRITORIOS; i++) {
        // Formatação clara para a exibição dos dados (requisito de Usabilidade).
        printf("🗺️ TERRITÓRIO #%d:\n", i + 1);
        printf("  - Nome: %s\n", cadastro_territorios[i].nome);
        printf("  - Cor do Exército: %s\n", cadastro_territorios[i].cor);
        printf("  - Tropas: %d\n", cadastro_territorios[i].tropas);
        printf("---\n");
    }

    printf("Fim do cadastro e exibição.\n");
    return 0;
}