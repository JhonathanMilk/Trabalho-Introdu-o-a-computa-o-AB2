#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void UsoDeCpu (int pid, int i) 		/*Função utilizada pelo processo pai para monitorar consumo de memória do processo filho*/
{
	char ucp_cmd[256];
	sprintf(ucp_cmd, "ps axo pid,pcpu | grep %d | awk '{print $2}'", pid); 		/*Armazenando na variável os comandos shell e filtrando através de pipes para salvar somente os valores da cpu na string*/
	/*	ou utilizar esse comando: sprintf(ucp_cmd, "ps u%d | awk '{print $3}' | grep -v CPU", pid);*/
		char buffer[1000];
		FILE *pipe; 			/*Ponteiro para variável do tipo arquivo*/
		int len;
		pipe = popen(ucp_cmd, "r"); 			/*Arquivo pipe recebe valores lidos na variável*/

		if (NULL == pipe) {
			perror("pipe");				/*Se o popen não conseguir ler nenhum valor, sai da função com mensagem de erro: Pipe*/
			exit(1);
		}

		char* cpu_usage = fgets(buffer, sizeof(buffer), pipe); 		/*obtendo todos valores do arquivo, limitado num máximo do tamanho do valor do buffer(1000), e armazenando na variável buffer*/
		len = strlen(ucp_cmd);  			/*Função strlen conta números de caracteres da string*/
		ucp_cmd[len-1] = '\0'; 				/*Último caractere da string recebe o operador nulo*/
		FILE *file = fopen("Main.txt", "a"); 		/*Criando arquivo para obter os dados. Finalidade: plotar um gráfico*/
		fprintf(file, "%d ", i); 				/*Salvando o contador no arquivo Main.txt*/
		fprintf(file, "%s", cpu_usage);				 /*Salvando o uso da ucp no arquivo Main.txt*/
		pclose(pipe); 			/*fechando fluxo aberto por popen*/
		printf("cpu_usage == %s", cpu_usage); 			/*Printando resultados na tela*/
}

void UsoDeMem(int pid, int i)			/*Função utilizada pelo processo pai para monitorar consumo de ucp e memória do processo filho*/
{
	char mem_cmd[256];
	sprintf(mem_cmd, "ps u%d | awk '{print $5}' | grep -v VSZ", pid);
		char buffer[1000];
		FILE *pipe;
		int len;
		pipe = popen(mem_cmd, "r");

		if (NULL == pipe) {
			perror("pipe");
			exit(1);
		}

		char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
		len = strlen(mem_cmd);
		mem_cmd[len-1] = '\0';
		FILE *file = fopen("Main2.txt", "a"); 		/*Criando arquivo para obter os dados. Finalidade: plotar um gráfico*/
		fprintf(file, "%d ", i);  	/*Salvando o contador no arquivo Main2.txt*/
		fprintf(file, "%s", mem_usage); 		/*Salvando o uso de memória no arquivo Main2.txt*/
		pclose(pipe);

		printf("mem_usage == %s\n", mem_usage);
}

void MatarProcesso (int pid)
	{
		char kill_process[256];		 /*Declaração de variavél para armazenar uma string*/
		sprintf(kill_process, "kill -9 %d", pid); 	/*Concatenando comando shell a ser utilizado para matar processo + pid do processo, e armazenando a string na variável kill_process*/
    system (kill_process);  	/*Comando system executa a string que está na variável*/
  }

int main (int argc, char *argv[], char *envp[]) {

int pid ; 	 /* identificador de processo */
int i=1; 		/*Declaração da condição de parada*/

system ("rm -rvf Main.txt >/dev/null");  /*Apagando arquivo Main.txt, caso já houver na pasta que o progama está sendo executado + ocultando saída no terminal*/
system ("rm -rvf Main2.txt >/dev/null");  /*Apagando arquivo Main2.txt, caso já houver na pasta que o progama está sendo executado + ocultando saída no terminal*/

pid = fork () ; 	/* replicação do processo */

if ( pid < 0 ) { 	/* se o fork não funcionou */
	perror ("Erro: ") ;
	exit (-1); 	/* encerra o processo com código de erro -1 */
}
else if( pid > 0 ) /* se sou o processo pai*/
{
	if (!strcmp (argv[1], "ucp"))		/*Se argumento de execução do progama for cpu-mem*/
  {
		while (i<=10)
		{
			UsoDeCpu(pid, i);  /*Chamada da função para monitorar uso de ucp*/
			sleep(1);    /*Aguarda 1 segundo para cada novo ciclo de monitoramento*/
			i++;        /*Condição de parada incrementando +1 a cada ciclo*/
		}
	}
	if (!strcmp (argv[1], "ucp-mem"))   /*Se argumento de execução do progama for cpu-mem*/
	{
		while (i<=10)
		{
			UsoDeCpu(pid, i);  /*Chamada da função para monitorar uso de ucp*/
			UsoDeMem (pid, i);  /*Chamada da função para monitorar uso de memória*/
			sleep(1);  /*Aguarda 1 segundo para cada novo ciclo de monitoramento*/
			i++;     /*Condição de parada incrementando +1 a cada ciclo*/
		}
  }

MatarProcesso (pid);

}
else 		/* senão, sou o processo filho (pid == 0) */
{
	if (!strcmp (argv[1], "ucp"))
  {
		for (;;) {}  	/*Loop infinito*/
	}
	if (!strcmp (argv[1], "ucp-mem"))
	{
		for (;;) 	/*Loop infinito*/
		{
			usleep(1); 	 /*Aguarda 1 milessegundo para cada repetição*/
			malloc(100000); 	/*Alocação de memória*/
  	}
	}
}

exit(0); 	/* encerra o processo com sucesso (código 0) */

}
