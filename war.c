#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Necessário para srand(time(NULL))

// Estrutura para representar um Território
typedef struct {
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército (Dono)
    int tropas;    // Número de tropas no território
} Territorio;

// Protótipos das funções
void cadastrarTerritorio(Territorio* t, int indice);
void atacar(Territorio* atacante, Territorio* defensor);
void exibirTerritorio(const Territorio* t);
void exibirMapa(const Territorio* mapa, int numTerritorios);
void liberarMemoria(Territorio* mapa);

// --- Funções de Utilitário e Gerenciamento de Memória ---

/**
 * @brief Cadastra os dados de um único território.
 * @param t Ponteiro para o Territorio a ser cadastrado.
 * @param indice Índice do território no array (para exibição).
 */
void cadastrarTerritorio(Territorio* t, int indice) {
    printf("\n--- Cadastro do Território %d ---\n", indice + 1);
    printf("Nome: ");
    scanf(" %29s", t->nome);
    printf("Cor do Exército (Ex: Azul, Vermelho): ");
    scanf(" %9s", t->cor);
    printf("Número de Tropas: ");
    // Validação simples para garantir que o número de tropas seja no mínimo 1
    if (scanf("%d", &t->tropas) != 1 || t->tropas < 1) {
        t->tropas = 1; // Garante pelo menos 1 tropa
        printf("[!] Tropas inválidas. Definindo 1 tropa.\n");
        // Limpar buffer de entrada se a leitura falhou (boas práticas)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

/**
 * @brief Exibe os dados de um único território.
 * @param t Ponteiro constante para o Territorio a ser exibido.
 */
void exibirTerritorio(const Territorio* t) {
    printf("  -> Nome: %s | Cor: %s | Tropas: %d\n", t->nome, t->cor, t->tropas);
}

/**
 * @brief Exibe todos os territórios do mapa.
 * @param mapa Ponteiro constante para o primeiro elemento do array de Territorios.
 * @param numTerritorios Quantidade total de territórios.
 */
void exibirMapa(const Territorio* mapa, int numTerritorios) {
    printf("\n--- Mapa Atual ---\n");
    for (int i = 0; i < numTerritorios; i++) {
        printf("[%d] ", i);
        exibirTerritorio(&mapa[i]); // Aritmética de ponteiros
    }
    printf("------------------\n");
}

/**
 * @brief Libera a memória alocada dinamicamente.
 * @param mapa Ponteiro para o array que foi alocado com malloc/calloc.
 */
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\n[!] Memória alocada liberada com sucesso.\n");
    }
}

// --- Funções de Simulação de Batalha ---

/**
 * @brief Simula um ataque entre dois territórios usando rolagem de dados.
 * @param atacante Ponteiro para o território atacante.
 * @param defensor Ponteiro para o território defensor.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    // Rand() gera um número entre 0 e RAND_MAX. Usamos % 6 + 1 para obter [1, 6].
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- Simulação de Batalha ---\n");
    printf("Atacante (%s) rola %d.\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rola %d.\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("\n*** VITÓRIA do Atacante! (%s) ***\n", atacante->cor);
        
        // 1. Defensor muda de dono (cor do exército)
        // Uso de strcpy para copiar a string da cor
        strcpy(defensor->cor, atacante->cor); 
        
        // 2. Tropas do defensor são atualizadas
        int tropasTransferidas = atacante->tropas / 2; // Metade das tropas do atacante
        
        // As tropas transferidas se tornam as novas tropas do território defensor.
        defensor->tropas = tropasTransferidas;
        
        // O atacante perde as tropas transferidas
        atacante->tropas -= tropasTransferidas; 
        
        printf("[!] %d tropas do %s foram transferidas para %s.\n", 
               tropasTransferidas, atacante->nome, defensor->nome);

    } else {
        // Defensor vence ou empate (empate favorece o defensor no War)
        printf("\n*** VITÓRIA do Defensor! (%s) ***\n", defensor->cor);
        
        // Atacante perde uma tropa, mas deve ter no mínimo 1.
        if (atacante->tropas > 1) {
            atacante->tropas--;
            printf("[!] O atacante (%s) perdeu 1 tropa.\n", atacante->nome);
        } else {
            printf("[!] O atacante (%s) manteve 1 tropa (mínimo).\n", atacante->nome);
        }
    }
    printf("---------------------------\n");
}

// --- Função Principal (Main) ---

int main() {
    // Inicializa a semente do gerador de números aleatórios
    // Garante que a sequência de rand() seja diferente a cada execução
    srand(time(NULL));

    int numTerritorios;
    Territorio* mapa = NULL; // Ponteiro para o array de territórios

    printf("🎲 Bem-vindo ao Simulador de Ataque War em C! 🎲\n");

    // Alocação de Memória
    printf("Quantos territórios serão cadastrados? ");
    if (scanf("%d", &numTerritorios) != 1 || numTerritorios < 2) {
        printf("[!] Número de territórios inválido. O mínimo é 2.\n");
        return 1; // Encerra o programa com erro
    }

    // Alocação dinâmica de memória para o array de estruturas Territorio
    // Uso de calloc: aloca (numTerritorios * sizeof(Territorio)) bytes e inicializa em zero.
    mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("[!] Erro na alocação de memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < numTerritorios; i++) {
        // Passa o endereço do i-ésimo elemento do array
        cadastrarTerritorio(&mapa[i], i); 
    }

    // Loop principal de ataque
    int indiceAtacante, indiceDefensor;
    char continuar;

    do {
        // Exibição pós-ataque / Exibição Inicial
        exibirMapa(mapa, numTerritorios);

        printf("\n--- Escolha para o Ataque ---\n");
        printf("Selecione o índice do território ATACANTE (0 a %d): ", numTerritorios - 1);
        scanf("%d", &indiceAtacante);

        // Validação básica de índice
        if (indiceAtacante < 0 || indiceAtacante >= numTerritorios) {
            printf("[!] Índice do atacante inválido.\n");
            continue;
        }

        printf("Selecione o índice do território DEFENSOR (0 a %d): ", numTerritorios - 1);
        scanf("%d", &indiceDefensor);
        
        // Validação básica de índice
        if (indiceDefensor < 0 || indiceDefensor >= numTerritorios || indiceAtacante == indiceDefensor) {
            printf("[!] Índice do defensor inválido ou é o mesmo do atacante.\n");
            continue;
        }

        // --- Validação de Regras do Jogo ---
        
        // Não pode atacar a própria cor
        // Uso de strcmp para comparar as strings de cor
        if (strcmp(mapa[indiceAtacante].cor, mapa[indiceDefensor].cor) == 0) {
            printf("[!] ERRO: Você não pode atacar um território da sua própria cor (%s).\n", 
                   mapa[indiceAtacante].cor);
            continue;
        }
        
        // O atacante deve ter no mínimo 2 tropas para atacar
        if (mapa[indiceAtacante].tropas < 2) {
             printf("[!] ERRO: O território atacante (%s) deve ter no mínimo 2 tropas para atacar.\n", 
                   mapa[indiceAtacante].nome);
            continue;
        }

        // --- Execução do Ataque ---
        
        // Passa os endereços dos territórios (ponteiros) para a função atacar
        // O acesso e manipulação dos dados internos ocorrerá via ponteiro dentro da função
        atacar(&mapa[indiceAtacante], &mapa[indiceDefensor]);
        
        // Exibição dos dados atualizados pós-ataque
        printf("\n[Dados Pós-Ataque]\n");
        printf("Atacante [%d]: ", indiceAtacante);
        exibirTerritorio(&mapa[indiceAtacante]);
        printf("Defensor [%d]: ", indiceDefensor);
        exibirTerritorio(&mapa[indiceDefensor]);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar); // Espaço antes de %c para ignorar espaços/quebras de linha

    } while (continuar == 's' || continuar == 'S');

    // Liberação de Memória
    liberarMemoria(mapa);

    printf("\nPrograma finalizado. Até a próxima simulação!\n");
    return 0;
}