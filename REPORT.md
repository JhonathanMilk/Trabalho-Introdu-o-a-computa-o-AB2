﻿# Identificação
Página do repositório do trabalho ([github](https://github.com/JhonathanMilk/Trabalho-Introdu-o-a-computa-o-AB2.git))


 + Discente 1 <br>
    - Nome: Jonatan Leite Alves <br>
    - Matrícula: 18211780 <br>
    - Distribuição da nota(%): 10 <br>
 + Discente 2 <br>
    - Nome: José Luanderson Gonçalves de Souza <br>
    - Matrícula: 18211781 <br>
    - Distribuição da nota(%): 10 <br>
 + Discente 3 <br>
    - Nome: Cleverton José da Silva Santos <br>
    - Matrícula: 18211741 <br>
    - Distribuição da nota(%): 10 <br>


# Resultados
## Teste UCP


![Monitorando ucp](https://uploaddeimagens.com.br/images/001/911/853/full/UCP.png?)


## Teste UCP e memória


![enter image description here](https://uploaddeimagens.com.br/images/001/912/817/full/UCP-MEM1.png?)


![enter image description here](https://uploaddeimagens.com.br/images/001/912/827/full/chart_%287%29.png?)
# Discussão <br>


## Utilização intensa da UCP
A reta mostrada no gráfico manteve-se constante girando em torno da porcentagem de 100 à 102, extrapolando os 100%, pois a ucp na qual foi realizado os testes possui 4 núcleos de processamento, logo, o tanto que foi exigido durante a execução do programa foi o esperado, já que a alocação de tarefas, com um ciclo infinito que é acionado dependendo do argumento usado na execução no terminal(``` if(strcmp ( argv[1], “ucp”)) {for (;;) {}} ```), jogadas na ucp foram de níveis razoáveis para a máquina em questão. Contanto fica implícito que em máquinas de um núcleo o computador irá conseguir executar, porém ficará lento durante a execução(caso não seja adicionado uma condição de parada dos testes na ucp( ``` i>10 ```, sendo “i” o contador e 10 o tempo em segundos), dificultando desde o arrastar do mouse até a execução de programas em segundo plano, pois a prioridade ficará destinada ao ciclo infinito (``` for(;;) ```). <br><br>


## Utilização intensa da UCP e memória
A curva de execução no gráfico somente da ucp(testando ucp-mem) tem seu início em 0 e oscila entre a porcentagem 16.4 à 18.1. Esses dados foram monitorados pelo processo pai ```(pid>o)``` em um intervalo de 1 segundo a cada novo ciclo (implementado ao código na função ``` sleep ```). Quando ocorreu a alocação excessiva de memória a ucp ficou em espera durante partes do ciclo, pois, ou executava o teste da ucp ou o teste da memória, isso explica a queda drástica nos resultados se comparado o segundo gráfico(ucp-mem), tendo pequenas oscilações 16 à 18 por cento, com o primeiro gráfico(testando somente ucp) que partiu de variações na porcentagem de 100 à 102. Vale ressaltar que esses dados obtidos no teste (ucp-mem) podem variar de forma inesperada. Dependendo da máquina que esteja executando o programa, a porcentagem de consumo da ucp pode aumentar consideravelmente.


O gráfico de consumo da memória, quando testado o programa com argumento(``` ucp-mem ```) se assemelha a função de crescimento linear, por conta de um crescimento constante dos valores que são alocados na memória virtual. A alocação em excesso de memória virtual foi executada por meio do comando ``` malloc(quantidade que será alocada de memória virtual, em bytes)```, sendo nos testes do grupo utilizado um valor de 100000 bytes a cada ciclo de repetição. Se não for adicionado um limite para a alocação de memória, consequentemente irá ocorrer um travamento na máquina, resultado de uma extrapolação dos recursos de hardware oferecidos pela mesma. O limite de execução no código é determinado pelo processo pai, que vai esperar 10 segundos para matar o processo filho, porém, durante este período, irá monitorar a cada um segundo e salvar os dados obtidos.


Os resultados obtidos eram esperados, uma vez que a memória que a máquina em que os testes representados nos gráficos dispunha 8 gb de ram, o que a fez suportar o tempo de execução do programa sem demais problemas, e mesmo realizando os testes em um computador com 2gb de ram, foi possível completar o tempo de execução do programa sem apresentar problemas. <br><br>


## Considerações finais
Foi notado que quanto mais robusto e eficiente o hardware da máquina, para execução dos processos, maior será a capacidade da mesma em aguentar os ciclos, sem causar uma extrapolação de recursos(claro que entre o tempo estipulado de 10 segundos de execução). Contudo, o grupo notou que até em um celeron(processador da linha de entrada), testando o comando ``` malloc ``` alocando 10000 bytes, juntamente com o laço infinito  (``` for (;;) ```), o consumo da ucp foi entre 80 e 90 por cento da capacidade da ucp. Isso leva a conclusão que a boa execução do programa vai depender dos recursos finitos oferecidos pela máquina do usuário. <br><br>
