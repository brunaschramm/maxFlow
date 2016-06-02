#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <math.h>
#include "utils.h"

using namespace std;

static const string INICIO = "S";
static const string FIM = "T";

class MaxFlow {
    private:
        string m_arqEntrada;
        int m_capacidadeMax;
        map<string, map<string, int> > m_grafo;
        map<string, int > m_clientesPorProduto;

        bool carregarArquivo();
    public:
        MaxFlow( string &entrada ): m_arqEntrada(entrada), m_capacidadeMax(0)
        {
            m_grafo.clear();
            m_clientesPorProduto.clear();
        }
        void executar();
        void criarRedeFluxo();
        void calcularFluxoMaximo();
        void exibirGrafo();
};