#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <math.h>
#include <limits.h>
#include "utils.h"

using namespace std;

static const string INICIO = "S";
static const string FIM = "T";

class MaxFlow {
    private:
        string m_arqEntrada;
        int m_capacidadeMax;
        float m_porcentagemAvaliacoes;
        map<string, map<string, int> > m_grafo;

        bool carregarArquivo();
        int calcularFluxoMaximo();
        void exibirGrafo();
        bool bfs(map<string,string> &parent);
        bool bfsOpt(map<string,string> &parent);
    public:
        MaxFlow( string &entrada, float &porcentagemAvaliacoes ): m_arqEntrada(entrada), m_capacidadeMax(0), m_porcentagemAvaliacoes(porcentagemAvaliacoes)
        {
            m_grafo.clear();
        }

        void executar();
};
