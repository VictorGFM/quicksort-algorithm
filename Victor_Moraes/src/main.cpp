#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include "Pilha.h"

void executaQuicksort(std::string &variacao, std::string &tipoVetor, long tamanhoVetor, long numeroExecucoes,
                      double *vetorResultados, std::string *vetoresUtilizados);
void inicializaVetor(long *vetor, std::string &tipoVetor, long tamanhoVetor, std::string *vetoresUtilizados);
double* selecionaQuicksort(const std::string &variacao, long tamanhoVetor, long *vetor);


double* quicksortClassico(long vetor[], long tamanho);
void ordenaQuicksortClassico(int esquerda, int direita, long vetor[], double *comparacaoChave,
                             double *movimentacaoRegistro);
void particaoQuicksortClassico(int esquerda, int direita, int *i, int *j, long *vetor, double *movimentacaoRegistro,
                               double *comparacaoChave);

double* quicksortMedianaTres(long *vetor, long tamanho);
void ordenaQuicksortMedianaTres(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                double *movimentacaoRegistro);
long particaoQuicksortMedianaTres(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                  double *movimentacaoRegistro);

double* quicksortPrimeiroElemento(long *vetor, long tamanho);
void ordenaQuicksortPrimeiroElemento(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                     double *movimentacaoRegistro);
long particaoQuicksortPrimeiroElemento(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                       double *movimentacaoRegistro);


double* quicksortInsercao(long *vetor, long tamanho, double porcentagem);
void ordenaQuicksortInsercao(long *vetor, int esquerda, int direita, double *comparacaoChave,
                             double *movimentacaoRegistro, double porcentagem);
long particaoQuicksortInsercao(long *vetor, int esquerda, int direita, double *comparacaoChave,
                               double *movimentacaoRegistro);

void ordenaInsercao(long *vetor, long tamanho, double *comparacaoChave, double *movimentacaoRegistro);

double* quicksortNaoRecursivo(long *vetor, long tamanho);
long particaoQuicksortNaoRecursivo(int esquerda, int direita, long *vetor, double *comparacaoChave,
                                   double *movimentacaoRegistro);

void trocaElementos(long *a, long *b);
void imprimeResultado(std::string &variacao, std::string &tipoVetor, long tamanhoVetor, double *vetorResultados,
                      std::string &vetoresUtilizados, bool exibirVetor);

int main(int argc, char* argv[])  {
    //Obtem parâmetros de entrada;
    std::string variacao = argv[1];
    std::string tipoVetor = argv[2];
    long tamanhoVetor = std::stol(std::string(argv[3]));
    bool exibirVetor = argv[4] != nullptr;

    //Define quantidade de execuções do algoritmo e variaveis de saída;
    long numeroExecucoes = 20;
    double vetorResultados[3] = {}; // Vetor dos resultados [0]:media de movimentacao de registro [1]:media de 					       comparacao de chave [2]:mediana do tempo de execucao;
    std::string vetoresUtilizados;

    //Executa método Quicksort de acordo com os parâmetros definidos;
    executaQuicksort(variacao, tipoVetor, tamanhoVetor, numeroExecucoes, vetorResultados, &vetoresUtilizados);

    //Imprime o resultado obtido após terminar todas as execuções;
    imprimeResultado(variacao, tipoVetor, tamanhoVetor, vetorResultados, vetoresUtilizados, exibirVetor);

    return 0;
}

void executaQuicksort(std::string &variacao, std::string &tipoVetor, long tamanhoVetor, long numeroExecucoes,
                      double *vetorResultados, std::string* vetoresUtilizados) {
    //Define indice de mediana, para o cálculo da mediana de tempo de execução;
    bool isParNumeroExecucoes = numeroExecucoes%2 == 0;
    int indiceMediana = (numeroExecucoes/2)-1;
    auto* vetorTempoExecucao = new double[numeroExecucoes];

    for (int i = 0; i < numeroExecucoes; i++) {
        //Inicializa vetor com base no parâmetro de entrada (OrdC, OrdD ou Ale);
        long* vetor = new long[tamanhoVetor];
        inicializaVetor(vetor, tipoVetor, tamanhoVetor, vetoresUtilizados);

        //Obtem resultado da execução do Quicksort;
        double* resultado = selecionaQuicksort(variacao, tamanhoVetor, vetor);

        for (int j = 0; j < 2; j++) {
            vetorResultados[j] += resultado[j];
        }

        vetorTempoExecucao[i] = resultado[2];
    }

    //Obtem media da movimentação de registro e comparacao de chave;
    for (int i = 0; i < 2; i++) {
        vetorResultados[i] /= numeroExecucoes;
    }
    //Obtem mediana do tempo de execução;
    if(isParNumeroExecucoes) {
        vetorResultados[2] = (vetorTempoExecucao[indiceMediana] + vetorTempoExecucao[indiceMediana+1])/2.0;
    } else {
        vetorResultados[2] = vetorTempoExecucao[indiceMediana];
    }
}
double* selecionaQuicksort(const std::string &variacao, long tamanhoVetor, long *vetor) {
    //Seleciona o tipo de Quicksort conforme parametro de entrada;
    auto* resultado = new double[3];
    if (variacao == "QC") {
        resultado = quicksortClassico(vetor, tamanhoVetor);
    } else if (variacao == "QM3") {
        resultado = quicksortMedianaTres(vetor, tamanhoVetor);
    } else if (variacao == "QPE") {
        resultado = quicksortPrimeiroElemento(vetor, tamanhoVetor);
    } else if (variacao == "QI1") {
        double umPorcento = (tamanhoVetor*(1.0/100));
        resultado = quicksortInsercao(vetor, tamanhoVetor, umPorcento);
    } else if (variacao == "QI5") {
        double cincoPorcento = (tamanhoVetor*(5.0/100));
        resultado = quicksortInsercao(vetor, tamanhoVetor, cincoPorcento);
    } else if (variacao == "QI10") {
        double dezPorcento = (tamanhoVetor*(10.0/100));
        resultado = quicksortInsercao(vetor, tamanhoVetor, dezPorcento);
    } else if (variacao == "QNR") {
        resultado = quicksortNaoRecursivo(vetor, tamanhoVetor);
    }
    return resultado;
}
void inicializaVetor(long *vetor, std::string &tipoVetor, long tamanhoVetor, std::string *vetoresUtilizados) {
    if(tipoVetor == "Ale") { //Inicializa vetor com valores aleatorios;
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<long> distribution(0,tamanhoVetor-1);
        for(long i=0; i<tamanhoVetor; i++) {
            vetor[i] = distribution(generator);
            *vetoresUtilizados += std::to_string(vetor[i]) + " "; // Salva vetores utilizados na variavel de saída
        }
    } else if(tipoVetor == "OrdC") { //Inicializa vetor ordenado de forma crescente;
        for(long i=0; i<tamanhoVetor; i++) {
            vetor[i] = i;
            *vetoresUtilizados += std::to_string(vetor[i]) + " "; // Salva vetores utilizados na variavel de saída
        }
    } else if(tipoVetor == "OrdD") { //Inicializa vetor ordenado de forma decrescente;
        for(long j=tamanhoVetor-1, i=0; j>=0; j--, i++) {
            vetor[i] = j;
            *vetoresUtilizados += std::to_string(vetor[i]) + " "; // Salva vetores utilizados na variavel de saída
        }
    }
    *vetoresUtilizados += "\n";
}

double* quicksortClassico(long *vetor, long tamanho) {
    //Define variaveis de retorno;
    static double resultado[3];
    auto* comparacaoChave = new double;
    auto* movimentacaoRegistro = new double;
    *comparacaoChave = 0;
    *movimentacaoRegistro = 0;

    //Executa algoritmo Quicksort;
    std::chrono::high_resolution_clock::time_point t1 =  std::chrono::high_resolution_clock::now();
    ordenaQuicksortClassico(0, tamanho-1, vetor, comparacaoChave, movimentacaoRegistro);
    std::chrono::high_resolution_clock::time_point t2 =  std::chrono::high_resolution_clock::now();

    //Calcula tempo de execução do algoritmo;
    std::chrono::duration<double, std::micro> tempoExecucao = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    //Inicializa variáveis de retorno de acordo com resultado obtido;
    resultado[0] = *comparacaoChave;
    resultado[1] = *movimentacaoRegistro;
    resultado[2] = tempoExecucao.count();

    return resultado;
}
void ordenaQuicksortClassico(int esquerda, int direita, long *vetor, double *comparacaoChave,
                             double *movimentacaoRegistro) {
    int i = 0, j = 0;
    //Define partições do vetor;
    particaoQuicksortClassico(esquerda, direita, &i, &j, vetor, movimentacaoRegistro, comparacaoChave);
    //Ordena partição da esquerda;
    if(esquerda < j) ordenaQuicksortClassico(esquerda, j, vetor, comparacaoChave, movimentacaoRegistro);
    //Ordena partição da direita;
    if(i < direita) ordenaQuicksortClassico(i, direita, vetor, comparacaoChave, movimentacaoRegistro);
}
void particaoQuicksortClassico(int esquerda, int direita, int *i, int *j, long *vetor, double *movimentacaoRegistro,
                               double *comparacaoChave) {
    //Define apontadores inicias;
    *i = esquerda;
    *j = direita;
    //Define pivô central
    long pivo = vetor[(*i+*j)/2];

    do {
        //Percorre até achar um elemento à esquerda que seja maior ou igual ao pivô
        while(pivo > vetor[*i]) {
            (*i)++;
            (*comparacaoChave)++;
        }
        (*comparacaoChave)++;
        //Percorre até achar um elemento à direita que seja menor ou igual ao pivô
        while(pivo < vetor[*j]) {
            (*j)--;
            (*comparacaoChave)++;
        }
        (*comparacaoChave)++;
        //Troca os elementos da posição i e j;
        if(*i <= *j) {
            trocaElementos(&vetor[*i], &vetor[*j]);
            (*movimentacaoRegistro)++;
            (*i)++;
            (*j)--;
        }
    } while(*i <= *j); //Repete o processo até que os apontadores i e j se cruzem;
}

double * quicksortMedianaTres(long *vetor, long tamanho) {
    //Define variaveis de retorno;
    static double resultado[3];
    auto* comparacaoChave = new double;
    auto* movimentacaoRegistro = new double;
    *comparacaoChave = 0;
    *movimentacaoRegistro = 0;

    //Executa algoritmo Quicksort;
    std::chrono::high_resolution_clock::time_point t1 =  std::chrono::high_resolution_clock::now();
    ordenaQuicksortMedianaTres(vetor, 0, tamanho-1, comparacaoChave, movimentacaoRegistro);
    std::chrono::high_resolution_clock::time_point t2 =  std::chrono::high_resolution_clock::now();

    //Calcula tempo de execução do algoritmo;
    std::chrono::duration<double, std::micro> tempoExecucao = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    //Inicializa variáveis de retorno de acordo com resultado obtido;
    resultado[0] = *comparacaoChave;
    resultado[1] = *movimentacaoRegistro;
    resultado[2] = tempoExecucao.count();

    return resultado;
}
void ordenaQuicksortMedianaTres(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                double *movimentacaoRegistro) {
    //Executa para partições(Subvetores) de tamanho maior que 1;
    if(esquerda < direita) {
        //Define pivô que define a separação das partições;
        long pivo = particaoQuicksortMedianaTres(vetor, esquerda, direita, comparacaoChave, movimentacaoRegistro);
        //Ordena partição da esquerda;
        ordenaQuicksortMedianaTres(vetor, esquerda, pivo-1, comparacaoChave, movimentacaoRegistro);
        //Ordena partição da direita;
        ordenaQuicksortMedianaTres(vetor, pivo+1, direita, comparacaoChave, movimentacaoRegistro);
    }
}
long particaoQuicksortMedianaTres(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                  double *movimentacaoRegistro) {
    //Define elementos de inicio, meio e fim do vetor;
    int indiceCentral = (esquerda+direita)/2;
    long inicio = vetor[esquerda];
    long meio = vetor[indiceCentral];
    long fim = vetor[direita];
    int indiceMediana;

    //Define indice da mediana, com base nos parametros de inicio, meio e fim;
    (*comparacaoChave)++;
    if(inicio < meio) {
        (*comparacaoChave)++;
        if(meio < fim) {
            indiceMediana = indiceCentral;
        }  else {
            (*comparacaoChave)++;
            if (inicio < fim) {
                indiceMediana = direita;
            } else {
                indiceMediana = esquerda;
            }
        }
    } else {
        (*comparacaoChave)++;
        if (fim < meio) {
            indiceMediana = indiceCentral;
        } else {
            (*comparacaoChave)++;
            if (fim < inicio) {
                indiceMediana = direita;
            } else {
                indiceMediana = esquerda;
            }
        }
    }

    //Troca o elemento da mediana para a ultima posição do vetor;
    trocaElementos(&vetor[indiceMediana], &vetor[direita]);
    (*movimentacaoRegistro)++;

    //Define pivô como o ultimo elemento do vetor (Mediana);
    long pivo = vetor[direita];
    int i = esquerda - 1;
    int j = 0;

    //Percorre até que o apontador j chegue ao final do vetor;
    for(j=esquerda; j<direita; j++) {
        (*comparacaoChave)++;
        //Troca elemento da posição i com o da posição j caso o elemento de j seja menor ou igual ao pivô
        if(vetor[j] <= pivo) {
            i++;
            trocaElementos(&vetor[i], &vetor[j]);
            (*movimentacaoRegistro)++;
        }
    }
    //Troca a posição do pivô e coloca ele na posição correta;
    trocaElementos(&vetor[i+1], &vetor[direita]);
    (*movimentacaoRegistro)++;
    //Retorna a posição do pivô;
    return i+1;
}

double * quicksortPrimeiroElemento(long *vetor, long tamanho) {
    //Define variaveis de retorno;
    static double resultado[3];
    auto* comparacaoChave = new double;
    auto* movimentacaoRegistro = new double;
    *comparacaoChave = 0;
    *movimentacaoRegistro = 0;

    //Executa algoritmo Quicksort;
    std::chrono::high_resolution_clock::time_point t1 =  std::chrono::high_resolution_clock::now();
    ordenaQuicksortPrimeiroElemento(vetor, 0, tamanho-1, comparacaoChave, movimentacaoRegistro);
    std::chrono::high_resolution_clock::time_point t2 =  std::chrono::high_resolution_clock::now();

    //Calcula tempo de execução do algoritmo;
    std::chrono::duration<double, std::micro> tempoExecucao = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    //Inicializa variáveis de retorno de acordo com resultado obtido;
    resultado[0] = *comparacaoChave;
    resultado[1] = *movimentacaoRegistro;
    resultado[2] = tempoExecucao.count();

    return resultado;
}
void ordenaQuicksortPrimeiroElemento(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                     double *movimentacaoRegistro) {
    //Executa para partições(Subvetores) de tamanho maior que 1;
    if(esquerda < direita) {
        //Define pivô que define a separação das partições;
        long pivo = particaoQuicksortPrimeiroElemento(vetor, esquerda, direita, comparacaoChave, movimentacaoRegistro);
        //Ordena partição da esquerda;
        ordenaQuicksortPrimeiroElemento(vetor, esquerda, pivo-1, comparacaoChave, movimentacaoRegistro);
        //Ordena partição da direita;
        ordenaQuicksortPrimeiroElemento(vetor, pivo+1, direita, comparacaoChave, movimentacaoRegistro);
    }
}
long particaoQuicksortPrimeiroElemento(long *vetor, int esquerda, int direita, double *comparacaoChave,
                                       double *movimentacaoRegistro) {
    //Define pivô como primeiro elemento do vetor;
    long pivo = vetor[esquerda];
    //Define apontadores iniciais;
    int i = esquerda;
    int j = direita;

    //Executa até que i seja igual j;
    while(i<j) {

        //Percorre até achar um elemento à esquerda que seja maior que o pivô;
        (*comparacaoChave)++;
        while ((vetor[i] <= pivo) && (i<direita)) {
            i++;
            (*comparacaoChave)++;
        }
        //Percorre até achar um elemento à direita que seja menor ou igual que o pivô;
        (*comparacaoChave)++;
        while (vetor[j] > pivo) {
            j--;
            (*comparacaoChave)++;
        }
        //Troca os elementos, caso i seja menor que j;
        if (i<j) {
            trocaElementos(&vetor[i], &vetor[j]);
            (*movimentacaoRegistro)++;
        }
    }
    //Troca a posição do pivô e coloca ele na posição correta;
    trocaElementos(&vetor[esquerda], &vetor[j]);
    (*movimentacaoRegistro)++;
    //Retorna a posição do pivô;
    return j;
}

double * quicksortInsercao(long *vetor, long tamanho, double porcentagem) {
    //Define variaveis de retorno;
    static double resultado[3];
    auto* comparacaoChave = new double;
    auto* movimentacaoRegistro = new double;
    *comparacaoChave = 0;
    *movimentacaoRegistro = 0;

    //Executa algoritmo Quicksort;
    std::chrono::high_resolution_clock::time_point t1 =  std::chrono::high_resolution_clock::now();
    ordenaQuicksortInsercao(vetor, 0, tamanho - 1, comparacaoChave, movimentacaoRegistro, porcentagem);
    std::chrono::high_resolution_clock::time_point t2 =  std::chrono::high_resolution_clock::now();

    //Calcula tempo de execução do algoritmo;
    std::chrono::duration<double, std::micro> tempoExecucao = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    //Inicializa variáveis de retorno de acordo com resultado obtido;
    resultado[0] = *comparacaoChave;
    resultado[1] = *movimentacaoRegistro;
    resultado[2] = tempoExecucao.count();

    return resultado;
}
void ordenaQuicksortInsercao(long *vetor, int esquerda, int direita, double *comparacaoChave,
                             double *movimentacaoRegistro, double porcentagem) {
    //Executa para partições(Subvetores) de tamanho maior que 1;
    if(esquerda < direita) {
        long tamanhoSubVetor = direita-esquerda+1;
        //Se a partição(Subvetor) for menor que a porcentagem estabelecida (conforme o parametro passado), ordena pelo método de inserção;
        if(tamanhoSubVetor<porcentagem){
            long* subVetor = &vetor[esquerda];
            ordenaInsercao(subVetor, tamanhoSubVetor, comparacaoChave, movimentacaoRegistro);
        } else {
            //Define pivô que define a separação das partições;
            long pivo = particaoQuicksortInsercao(vetor, esquerda, direita, comparacaoChave, movimentacaoRegistro);
            //Ordena partição da esquerda;
            ordenaQuicksortInsercao(vetor, esquerda, pivo - 1, comparacaoChave, movimentacaoRegistro, porcentagem);
            //Ordena partição da direita;
            ordenaQuicksortInsercao(vetor, pivo + 1, direita, comparacaoChave, movimentacaoRegistro, porcentagem);
        }
    }
}
long particaoQuicksortInsercao(long *vetor, int esquerda, int direita, double *comparacaoChave,
                               double *movimentacaoRegistro) {
    //Define elementos de inicio, meio e fim do vetor;
    int indiceCentral = (esquerda+direita)/2;
    long inicio = vetor[esquerda];
    long meio = vetor[indiceCentral];
    long fim = vetor[direita];
    int indiceMediana;

    //Define indice da mediana, com base nos parametros de inicio, meio e fim;
    (*comparacaoChave)++;
    if(inicio < meio) {
        (*comparacaoChave)++;
        if(meio < fim) {
            indiceMediana = indiceCentral;
        }  else {
            (*comparacaoChave)++;
            if (inicio < fim) {
                indiceMediana = direita;
            } else {
                indiceMediana = esquerda;
            }
        }
    } else {
        (*comparacaoChave)++;
        if (fim < meio) {
            indiceMediana = indiceCentral;
        } else {
            (*comparacaoChave)++;
            if (fim < inicio) {
                indiceMediana = direita;
            } else {
                indiceMediana = esquerda;
            }
        }
    }

    //Troca o elemento da mediana para a ultima posição do vetor;
    trocaElementos(&vetor[indiceMediana], &vetor[direita]);
    (*movimentacaoRegistro)++;

    //Define pivô como o ultimo elemento do vetor (Mediana);
    long pivo = vetor[direita];
    int i = esquerda - 1;
    int j = 0;

    //Percorre até que o apontador j chegue ao final do vetor;
    for(j=esquerda; j<direita; j++) {
        (*comparacaoChave)++;
        //Troca elemento da posição i com o da posição j caso o elemento de j seja menor ou igual ao pivô
        if(vetor[j] <= pivo) {
            i++;
            trocaElementos(&vetor[i], &vetor[j]);
            (*movimentacaoRegistro)++;
        }
    }

    //Troca a posição do pivô e coloca ele na posição correta;
    trocaElementos(&vetor[i+1], &vetor[direita]);
    (*movimentacaoRegistro)++;
    //Retorna a posição do pivô;
    return i+1;
}
void ordenaInsercao(long *vetor, long tamanho, double *comparacaoChave, double *movimentacaoRegistro) {
    int i, j;
    long elemento;
    //Percorre segundo elemento até o ultimo elemento do vetor;
    for(i = 1; i<tamanho; i++) {
        elemento = vetor[i];
        j = i-1;
        //Percorre do fim até o inicio do vetor, comparando se o elemento anterior é maior que o proximo elemento;
        (*comparacaoChave)++;
        while(j>=0 && vetor[j]>elemento) {
            vetor[j+1] = vetor[j]; // Coloca elemento anterior na posição do proximo;
            j--;
            (*comparacaoChave)++;
            (*movimentacaoRegistro)++;
        }
        //Insere o elemento em sua posição correta;
        vetor[j+1] = elemento;
        (*movimentacaoRegistro)++;
    }
}

double * quicksortNaoRecursivo(long *vetor, long tamanho) {
    //Define variaveis de retorno;
    static double resultado[3];
    auto* comparacaoChave = new double;
    auto* movimentacaoRegistro = new double;
    *comparacaoChave = 0;
    *movimentacaoRegistro = 0;

    std::chrono::high_resolution_clock::time_point t1 =  std::chrono::high_resolution_clock::now();

    //Cria pilha de partições;
    auto* pilha = new Pilha();
    //Define apontadores iniciais;
    long esquerda = 0;
    long direita = tamanho - 1;

    //Empilha intervalo da partição inicial;
    pilha->push(esquerda);
    pilha->push(direita);

    //Percorre até esvaziar a pilha de partições;
    while (pilha->getTopo() >= 0) {
        //Desempilha intervalo de partição
        direita = pilha->pop();
        esquerda = pilha->pop();

        //Define pivô que define a separação das partições;
        int pivo = particaoQuicksortNaoRecursivo(esquerda, direita, vetor, comparacaoChave, movimentacaoRegistro);

        //Caso exista elemento à esquerda, empilha o intervalo na pilha;
        if (pivo - 1 > esquerda) {
            pilha->push(esquerda);
            pilha->push(pivo - 1);
        }
        //Caso exista elemento à direita, empilha o intervalo na pilha;
        if (pivo + 1 < direita) {
            pilha->push(pivo + 1);
            pilha->push(direita);
        }
    }

    std::chrono::high_resolution_clock::time_point t2 =  std::chrono::high_resolution_clock::now();

    //Calcula tempo de execução do algoritmo;
    std::chrono::duration<double, std::micro> tempoExecucao = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    //Inicializa variáveis de retorno de acordo com resultado obtido;
    resultado[0] = *comparacaoChave;
    resultado[1] = *movimentacaoRegistro;
    resultado[2] = tempoExecucao.count();

    return resultado;
}
long particaoQuicksortNaoRecursivo(int esquerda, int direita, long *vetor, double *comparacaoChave,
                                   double *movimentacaoRegistro)  {
    int pivo = vetor[direita];
    int i = (esquerda - 1);
    //Percorre do inicio até o fim da partição(Subvetor);
    for (int j=esquerda; j<direita; j++) {
        //Compara se elemento na posição j é menor ou igual ao pivo;
        (*comparacaoChave)++;
        if (vetor[j] <= pivo) {
            (*comparacaoChave)++;
            i++;
            //Realiza troca de elemento da posição i com o elemento da posição j;
            trocaElementos(&vetor[i], &vetor[j]);
            (*movimentacaoRegistro)++;
        }
    }
    //Troca a posição do pivô e coloca ele na posição correta;
    trocaElementos(&vetor[i + 1], &vetor[direita]);
    (*movimentacaoRegistro)++;
    //Retorna a posição do vetor;
    return (i + 1);
}

void trocaElementos(long *a, long *b) {
    //Troca valor de a com valor de b, por meio de uma variável auxiliar;
    long auxiliarTroca = *a;
    *a = *b;
    *b = auxiliarTroca;
}
void imprimeResultado(std::string &variacao, std::string &tipoVetor, long tamanhoVetor, double *vetorResultados,
                      std::string &vetoresUtilizados, bool exibirVetor) {
    //Imprime resultado de saída conforme formato da documentação;
    std::cout << std::fixed << std::setprecision(0) << variacao << " " << tipoVetor << " " << tamanhoVetor << " " << round(vetorResultados[0])
              << " " << round(vetorResultados[1]) << " " << std::setprecision(0) <<vetorResultados[2];
    if(exibirVetor) {
	std::cout << std::endl << vetoresUtilizados;
    }
}
