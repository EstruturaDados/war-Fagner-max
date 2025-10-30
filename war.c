// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>  // Para funções de entrada/saída (printf, scanf)
#include <string.h> // Para manipulação de strings (embora não estritamente necessário para este caso, é uma boa prática incluir)

// --- Definição da Struct Territorio ---
/*
 * Define a estrutura de dados composta chamada 'Territorio'.
 * Esta struct agrupa informações relacionadas a um único território.
 * * Campos:
 * - nome: Armazena o nome do território (máx. 29 caracteres + '\0').
 * - cor: Armazena a cor do exército que ocupa o território (máx. 9 caracteres + '\0').
 * - tropas: Armazena a quantidade de tropas no território.
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Função Principal ---
int main() {
    // Declaração de um vetor de structs Territorio.
    // O vetor 'territorios' armazena 5 estruturas, conforme o requisito.
    // O tamanho 5 é uma constante simbólica implícita para o número de cadastros.
    struct Territorio territorios[5];
    const int MAX_TERRITORIOS = 5;
    int i; // Variável de controle para os laços 'for'

    printf("==========================================\n");
    printf("     Sistema de Cadastro de Territórios     \n");
    printf("==========================================\n");
    printf("Você irá cadastrar informações para 5 territórios.\n\n");

    // --- Lógica de Entrada de Dados (Cadastro) ---
    /*
     * Laço for para percorrer o vetor 'territorios' e preencher cada uma das 5 posições.
     * A usabilidade é garantida por mensagens claras que orientam o usuário.
     */
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("--- Cadastro do Território #%d ---\n", i + 1);

        // Entrada do NOME do Território
        printf("Digite o NOME do território (máx. 29 caracteres): ");
        // Usamos scanf com [^\n] para ler a linha inteira (incluindo espaços) até o ENTER.
        // O limite de tamanho garante que não haja estouro de buffer (30-1).
        scanf(" %29[^\n]", territorios[i].nome);

        // Entrada da COR do Exército
        printf("Digite a COR do exército (máx. 9 caracteres, e.g., Azul, Vermelho): ");
        // Usamos %s, que lê uma palavra (até um espaço).
        // %9s garante que não haverá estouro de buffer.
        scanf("%9s", territorios[i].cor);

        // Entrada da QUANTIDADE de Tropas
        printf("Digite a QUANTIDADE de tropas: ");
        scanf("%d", &territorios[i].tropas);
        
        printf("\n"); // Espaço em branco para melhor visualização entre os cadastros
    }

    // --- Lógica de Saída de Dados (Exibição) ---
    /*
     * Laço for para percorrer o vetor 'territorios' após o cadastro
     * e exibir os dados de cada struct com formatação clara.
     * Isto atende ao requisito de desempenho (exibição logo após o cadastro).
     */
    printf("==========================================\n");
    printf("       Informações dos Territórios Registrados       \n");
    printf("==========================================\n");

    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("Território #%d\n", i + 1);
        // Exibição clara e formatada dos campos da struct
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exército: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("------------------------------------------\n");
    }

    printf("Fim do Cadastro e Exibição. Obrigado!\n");

    return 0; // Indica que o programa terminou com sucesso
}