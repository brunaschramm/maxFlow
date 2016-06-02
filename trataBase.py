import re

def main():
    base = open("amazon-meta.txt","r")
    #base = open("teste.txt","r")
    baseTratada = open("base.txt","w")

    clientePattern = re.compile('cutomer:\s+([0-9A-z]+)\s+')

    saida = ''
    ID_PROD = None
    CLIENTES = []
    for linha in base:
        linha = linha.strip()
        if linha.find("ASIN:") != -1:
            if ID_PROD != None:
                if len(CLIENTES) > 0:
                    saida = ID_PROD + ';' + ','.join(CLIENTES)
                    baseTratada.write(saida+"\n")

            ID_PROD = linha.split(" ")[1]
            CLIENTES = []
        if linha.find("cutomer:") != -1: #achou um id de cliente
            m = clientePattern.search(linha)
            if m:
                cliente = m.group(1)
                CLIENTES.append(cliente)
            else:
                print 'ops.. ', linha

    if ID_PROD != None:
        if len(CLIENTES) > 0:
            saida = ID_PROD + ';' + ','.join(CLIENTES)
            baseTratada.write(saida+"\n")

if __name__ == "__main__":
    main()