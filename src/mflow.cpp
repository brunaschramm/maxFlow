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
    set<string> vClientes;

    while(getline(arq, line))
    {
        if(line.empty()) continue;

        vClientes.clear();

        pos1 = line.find(';');
        if(pos1 == string::npos) continue;
        produto = line.substr(0, pos1);
        clientes = line.substr(pos1+1);

        split(clientes, ',', vClientes);

        m_clientesPorProduto[produto] = vClientes.size();

        for(set<string>::iterator it = vClientes.begin(); it != vClientes.end(); it++)
        {
            m_grafo[*it][produto] = 1;
        }
    }
    arq.close();

    return true;
}

void MaxFlow::criarRedeFluxo()
{
    cout << "Criando rede de fluxo" << endl;
    int capacidadeCliente;
    for(map< string, map< string, int > >::iterator it = m_grafo.begin() ; it != m_grafo.end(); it++ )
    {
        if(it->first != INICIO)
        {
    //        capacidadeCliente = ceil(it->second.size() * 0.4);
            capacidadeCliente = it->second.size();
            m_grafo[INICIO][it->first] = capacidadeCliente;
            m_capacidadeMax += capacidadeCliente;
//            cout <<  "[1]>> " << it->first << " - " << capacidadeCliente << endl;
        }
    }

    m_grafo[FIM][INICIO] = m_capacidadeMax;

    int aux = 0;

    for(map<string, int >::iterator it = m_clientesPorProduto.begin(); it != m_clientesPorProduto.end(); it++)
    {
        m_grafo[it->first][FIM] = it->second;
        aux += it->second;
//        cout <<  "[2]>> " << it->first << " - " << it->second << endl;
    }

//    cout << m_capacidadeMax << " - " << aux << endl;
}

//bool MaxFlow::bfs(map<string,map<string,int> > rGraph, map<string,string> &parent){
//    map<string,bool> visited;
//    for(int i = 0; i < keys.size(); i++ ){
//        visited[keys[i]] = false;
//    }
//    queue<string> vertex;
//    vertex.push("SOURCE");
//    visited["SOURCE"] = true;
//    parent["SOURCE"] = "";
//    while(!vertex.empty()){
//        string u = vertex.front();
//        vertex.pop();
//        for(map<string,int>::iterator it = rGraph[u].begin(); it!=rGraph[u].end(); ++it){
//            if(visited[it->first] == false && it->second>0){
//                    vertex.push(it->first);
//                    parent[it->first] = u;
//                    visited[it->first] = true;
//            }
//        }
//    }
//    return (visited["SINK"] == true);
//}

void MaxFlow::calcularFluxoMaximo()
{

}

void MaxFlow::executar()
{
    if( carregarArquivo() )
    {
//        exibirGrafo();

        criarRedeFluxo();

        calcularFluxoMaximo();

        return;
    }
}

int main(int argv, char *argc[])
{
    double start = getUnixTime();

    if(argv != 2)
    {
        cout << "Usar: " << argc[0] << " <path-entrada>" << endl;
        exit(1);
    }

    string arquivoEntrada(argc[1]);
//    cout << "- Arquivo de entrada = [" << arquivoEntrada << "]" << endl;

    MaxFlow maxFlow = MaxFlow( arquivoEntrada );

    maxFlow.executar();

    cout << "Tempo total de processamento: (" << getUnixTime() - start << ")" << endl;

    return 0;
}
