import re

limiarAvaliacoes = 1000

def main():
    base = open("amazon-meta.txt","r")
    #base = open("teste.txt","r")
    baseTratada = open("base.txt","w")

    clientePattern = re.compile('cutomer:\s+([0-9A-z]+)\s+')

    grafo = {} # produto -> lista clientes
    produtosPorCliente = {} # guardo total de avaliacoes feitas por cada cliente

    saida = ''
    ID_PROD = None

    for linha in base:
        linha = linha.strip()
        if linha.find("ASIN:") != -1:
            #if ID_PROD != None and len(CLIENTES) > 0:
            #    if ID_PROD not in grafo:
            #        grafo = CLIENTES
            #    else:
            #       grafo[ID_PROD] += CLIENTES
                #saida = ID_PROD + ';' + ','.join(CLIENTES)
                #for c in CLIENTES: print ID_PROD, c
                #         baseTratada.write(saida+"\n")
            ID_PROD = linha.split(" ")[1]
            if ID_PROD not in grafo: grafo[ID_PROD] = []
        elif linha.find("cutomer:") != -1: #achou um id de cliente
            m = clientePattern.search(linha)
            if m:
                cliente = m.group(1)
                grafo[ID_PROD].append(cliente)
            else:
                print 'ops.. ', linha

    blackListClientes = set() # guarda os outliers
    for prod in grafo:
        for cliente in grafo[prod]:
            if cliente not in produtosPorCliente:
                produtosPorCliente[cliente] = 1
            else:
                produtosPorCliente[cliente] += 1

    for cliente in produtosPorCliente:
        if produtosPorCliente[cliente] > limiarAvaliacoes:
            blackListClientes.add(cliente)

    print 'Clientes removidos - possuem mais avaliacoes que o limiar ({0})'.format(limiarAvaliacoes)
    print blackListClientes

    for prod in grafo:
        listaFinal = []
        for cliente in grafo[prod]:
            if cliente not in blackListClientes:
                listaFinal.append(cliente)
        if len(listaFinal) > 0:
            baseTratada.write(prod + ';' + ','.join(listaFinal)+"\n")

if __name__ == "__main__":
    main()