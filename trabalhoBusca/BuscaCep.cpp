#include<stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int c;
	long meio;
	bool achei = false;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	
	f = fopen("cep_ordenado.dat","r");
	long inicio = 0;
	fseek(f,0,SEEK_END);
	long tamarq = ftell(f); //tamarq em bytes
	long fim = tamarq/sizeof(Endereco); //fim em linhas
	
	
	int i = 0;
	while(inicio<=fim && achei==false){
		i++;
		meio = (inicio+fim)/2;
		fseek(f,meio*300,SEEK_SET);
		fread(&e,sizeof(Endereco),1,f);
		c = strncmp(argv[1],e.cep,8);
		if(c==0)
			achei = true;
		else if(c<0)
			fim = meio - 1;
		else
			inicio = meio + 1;			
	}
	
	if(achei == true){
		printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
	}
	else
		printf("Nao encontrado\n");
	
	printf("Total lido: %d", i);
	fclose(f);
	return 0;
}
	
	
	

	
	
	
	
	
	
