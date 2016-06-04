#include "mflow.h"

void MaxFlow::exibirGrafo()
{
    for(map< string, map< string, int > >::iterator it = m_grafo.begin() ; it != m_grafo.end(); it++ )
    {
        cout <<  ">> Cliente : " << it->first << endl;
        for( map< string, int >::iterator it2 = it->second.begin() ; it2 != it->second.end(); it2++ )
        {
            cout <<  "\t>> Produto : " << it2->first << endl;
        }
    }
}

bool MaxFlow::carregarArquivo()
{
    cout << "Carregando arquivo (" << m_arqEntrada << ")" << endl;
    size_t pos1;
    ifstream arq;
    arq.open(m_arqEntrada.c_str(), ios::in);

    if(!arq.is_open())
    {
        cout << "[ERRO] Arquivo [" << m_arqEntrada << "] não encontrado" << endl;
        return false;
    }

    string line, produto, clientes;
    vector<string> vClientes;

    while(getline(arq, line))
    {
        if(line.empty()) continue;

        vClientes.clear();

        pos1 = line.find(';');
        if(pos1 == string::npos) continue;
        produto = line.substr(0, pos1);
        clientes = line.substr(pos1+1);

        split(clientes, ',', vClientes);

        m_grafo[produto][FIM] = vClientes.size();

        for(vector<string>::iterator it = vClientes.begin(); it != vClientes.end(); it++)
        {
            m_grafo[*it][produto] = 1;
            if(m_grafo[INICIO].find(*it) == m_grafo[INICIO].end()) m_grafo[INICIO][*it] = 1;
            else m_grafo[INICIO][*it] += 1;
        }
    }
    arq.close();

    // Aplica restricao no grafo
    for(map<string, int>::iterator it = m_grafo[INICIO].begin(); it != m_grafo[INICIO].end(); it++ )
    {
        it->second = it->second*m_porcentagemAvaliacoes;
        m_capacidadeMax += it->second;
    }

    return true;
}

bool MaxFlow::bfs(map<string,string> &parent)
{
    map<string,bool> visited;
    for(map<string, map<string, int> >::iterator it = m_grafo.begin(); it != m_grafo.end(); it++ )
    {
        visited[it->first] = false;
    }
    queue<string> vertex;
    vertex.push(INICIO);
    visited[INICIO] = true;
    parent[INICIO] = "";
    while(!vertex.empty())
    {
        string u = vertex.front();
        vertex.pop();
        for(map<string,int>::iterator it = m_grafo[u].begin(); it != m_grafo[u].end(); ++it)
        {
            if(visited[it->first] == false && it->second > 0)
            {
                    vertex.push(it->first);
                    parent[it->first] = u;
                    visited[it->first] = true;
            }
        }
    }
    return visited[FIM];
}

int MaxFlow::calcularFluxoMaximo()
{
    cout <<  "Calculando fluxo máximo" << endl;
    string u,v;

    map<string,string> parent;

    int max_flow = 0;

    while(bfs(parent))
    {
        int path_flow = INT_MAX;
        for(v = FIM; v!= INICIO ; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow,m_grafo[u][v]);
        }
        for(v = FIM; v!= INICIO ; v = parent[v])
        {
            u = parent[v];
            m_grafo[u][v] -= path_flow;
            if( m_grafo[v].find(u) == m_grafo[v].end() ) m_grafo[v][u] = 0;
            m_grafo[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

void MaxFlow::executar()
{
    if( carregarArquivo() )
    {
//        exibirGrafo();

        int fluxoMax = calcularFluxoMaximo();

        if (fluxoMax == m_capacidadeMax)
        {
            cout << "Fluxo máximo encontrado respeita a restrição!" << endl;
        }
        else {
            cout << "Fluxo máximo não respeita restrição!" << endl;
        }

        cout << "\tFluxo máximo encontrado (" << fluxoMax << ") - Capacidade mínimo de avalições (" << m_capacidadeMax << ")" << endl;
    }
}

int main(int argv, char *argc[])
{
    double start = getUnixTime();

    if(argv != 3)
    {
        cout << "Usar: " << argc[0] << " <path-entrada> <porcentagem-maxima-avaliacao>" << endl;
        exit(1);
    }

    string arquivoEntrada(argc[1]);

    float porcentagemAvaliacoes = atof(argc[2]);

    if( porcentagemAvaliacoes < 0.0 || porcentagemAvaliacoes > 40.0)
    {
        cout << "Valor da % máxima de avaliações inválido: " << porcentagemAvaliacoes << ". Deve ser de 0 a 40%." << endl;
        exit(1);
    }

    porcentagemAvaliacoes /= 100.0;

    MaxFlow maxFlow = MaxFlow( arquivoEntrada, porcentagemAvaliacoes );

    maxFlow.executar();

    cout << "Tempo total de processamento: (" << getUnixTime() - start << ")" << endl;

    return 0;
}
