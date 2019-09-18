#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco {
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};

int compara(const void *e1, const void *e2) {
    return strncmp(((Endereco *)e1)->cep, ((Endereco *)e2)->cep, 8);
}

int main(){
    
    FILE *f, *saida;
    Endereco *e;
    char arquivo[100];

    long tamanho, qtd_linhas, particao ;
    f = fopen("cep.dat", "r");
    fseek(f,0,SEEK_END);
    tamanho = ftell(f);
    qtd_linhas = tamanho / sizeof(Endereco);
    particao = (qtd_linhas/8) + 1;
    int i = 0;
    fseek(f, 0, SEEK_SET);

    while(i < 8){
    	
        e = (Endereco*)malloc(sizeof(Endereco) * particao);
        
        if(!fread(e, sizeof(Endereco), particao, f) == particao){
            printf("Erro durante leitura da particao");
        }
        
        qsort(e, particao, sizeof(Endereco), compara);
        sprintf(arquivo, "cep_%d.dat", i);
        saida = fopen(arquivo, "w");
        fwrite(e, sizeof(Endereco), particao, saida);
        
        fclose(saida);
        free(e);
        i++;
    }

    fclose(f);

    FILE *a1, *b1;

    Endereco ea1, eb1;

    int x = 0;
    int y = 1;
    int j = 0;

   while(j<7){

        sprintf(arquivo, "cep_%d.dat", x);
        a1 = fopen(arquivo, "r");
        sprintf(arquivo, "cep_%d.dat", y);
        b1 = fopen(arquivo, "r");
        sprintf(arquivo, "cep_%d.dat", i);
        saida = fopen(arquivo, "w");
        fread(&ea1, sizeof(Endereco), 1, a1);
        fread(&eb1, sizeof(Endereco), 1, b1);

        while (!feof(a1) && !feof(b1)) {
            if (compara(&ea1, &eb1) < 0) {
                fwrite(&ea1, sizeof(Endereco), 1, saida);
                fread(&ea1, sizeof(Endereco), 1, a1);
            } 
			else {
                fwrite(&eb1, sizeof(Endereco), 1, saida);
                fread(&eb1, sizeof(Endereco), 1, b1);
            }
        }

        while (!feof(a1)) {
            fwrite(&ea1, sizeof(Endereco), 1, saida);
            fread(&ea1, sizeof(Endereco), 1, a1);
        }
        
        while (!feof(b1)) {
            fwrite(&eb1, sizeof(Endereco), 1, saida);
            fread(&eb1, sizeof(Endereco), 1, b1);
        }

        fclose(a1);
        fclose(b1);
        fclose(saida);
        x += 2;
        y += 2;
        i++;
        j++;
    }
}
