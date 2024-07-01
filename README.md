# EXPLICAÇÃO DO PROBLEMA
O código acima consiste em um labirinto onde um personagem nomeado Hércules deve percorrer o menor caminho possível até um certo ponto do labirinto, que consiste de N vértices e a aresta de cada vértice tem peso X.

# MODELAGEM DO PROBLEMA
Para solucionar o problema descrito, foi utilizado um grafo não orientado que é criado durante a execução do programa a partir de um dado arquivo em formato “.txt”. Para criar o grafo foi utilizado uma lista de adjacência dinamicamente alocada de forma que os grafos criados tanto pelo usuário, quanto pelo programa não possuam limitações técnicas. A lista de adjacência utilizada foi estruturada a partir de um Lista de dados nomeada adjacente que possui 2 inteiros: peso e destino, peso representa o valor X que existe entre um vértice e outro enquanto destino representa os vértices que o vértice em questão tem uma aresta em comum, e uma variável nomeada proximo que faz referência ao próximo dado da lista. Esta Lista de dados está inserida em Struct nomeada Vertice, esta sim é a estrutura alocada dinamicamente e possui 2 inteiros: peso e visitado, peso é utilizado para calcular o peso relativo de um vértice de origem até o dado vértice e visitado é utilizado para verificar o vértice em questão já foi analisado pelo algoritmo utilizado no programa, e a lista de adjacência do vértice, que foi nomeada de listaAdj.
Estruturas exemplificadas:
      
    typedef struct Adjacente {
        int destino;
        int peso;
        struct Adjacente* proximo;
    } Adjacente;
    
    typedef struct Vertice {
        Adjacente* listaAdj;
        int peso;
        int visitado;
    } Vertice;

# ALGORITMO UTILIZADO
Após a criação do grafo foi utilizado o algoritmo Djikstra para calcular o caminho mínimo entre um vértice origem e um vértice destino, ambos especificados pelo usuário ou aleatorizados pelo programa. O algoritmo, juntamente da função de inserção de vértices, inicializa o peso dos vértices na variável Vertice com o maior valor possível de um inteiro, porém o vértice de origem tem seu peso inicial com valor 0. O algoritmo funciona em loop de forma que a cada iteração o mesmo procure o vértice com o menor peso, então percorre sua lista de adjacência de forma a atualizar seus pesos se:

  #### O vértice destino na lista de adjacência não tenha sido visitado,
  #### O peso do vértice selecionado seja diferente do valor máximo atribuído
  #### O peso do vértice selecionado somado com o peso do vértice destino na lista de adjacência seja menor que o peso do vértice destino.
	
Caso as condições sejam obedecidas, o peso do vértice é atualizado com o valor obtido pela soma do peso do vértice selecionado e o peso do vértice destino que foi analisado na lista de adjacência do vértice selecionado. 
Tal procedimento é realizado até que todos os destinos do vértice sejam comparados e possivelmente atualizados de acordo com as condições citadas acima.

Durante a atualização do peso dos vértices descritos pela variável Vertice, um vetor nomeado anterior também é atualizado de forma que, baseado nas  3 condições, o caminho mais rápido seja criado, seguindo a ideia de que o vértice anterior ao um vértice X seja o vértice Y, dessa maneira, ao final da execução do algoritmo, é criado um vetor de tamanho N em que cada posição possui um valor numérico que representa o vértice que deve ser percorrido para que o caminho mais rápido seja encontrado. Portanto, ao ordenar esse vetor é possível visualizar o caminho mais rápido calculado pelo programa. 
  
# DIFICULDADES ENCONTRADAS E SOLUÇÕES ABORDADAS
Durante a resolução do trabalho, os problemas encontrados foram a dificuldade de ordenar o vetor que continha o caminho mais rápido, a variável anterior, e a criação e impressão de um grafo de teste para que o usuário pudesse interagir com o programa de forma a jogar o jogo criado. Para resolver o primeiro problema foi criado um segundo vetor de tamanho N nomeado anteriorOrdenado, que tem o vértice destino atribuído a posição 0 e suas demais posições com o valor encontrado em anterior no índice posicao, que tinha seu valor atualizado para o valor que foi atribuído para anteriorOrdenado, dessa maneira era possível colocar em ordem inversa o caminho mais rápido.
Código exemplificado:

    int posicao = destino;
    anteriorOrdenado[0] = destino;
    for (int i = 1; i < tamanho; i++) {
        anteriorOrdenado[i] = anterior[posicao];
        posicao = anterior[posicao]; 

        if (posicao == 0) {
            break;
        }
    }

Para a impressão do caminho mais rápido é preciso percorrer e imprimir o vetor de trás para frente, já que o destino se encontra na posição 0.
O segundo problema não era lógico e sim um problema massante e foi solucionado com escrita manual de todos as 113 arestas do grafo e a escrita manual de um “printf” com 113 parâmetros.

# CONCLUSÃO
O projeto final conta com 3 opções em seu menu, a primeira para calcular o caminho mais rápido do grafo inserido pelo usuário, a segunda, a opção de jogar um jogo em que é preciso encontrar o caminho mais rápido do ponto 0 até um ponto aleatório, sendo que as arestas possuem valores aleatórios entre 1 e 99 e o labirinto possui 65 vértices (um jogo realmente desafiante), por fim a terceira opção que demonstra de forma sucinta o funcionamento do algoritmo utilizado. 

