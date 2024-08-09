#include <stdio.h>

// x => chave | v[] => vetor ordenado | e => limite inferior (esquerda) | d => limite superior (direita)
int PesquisaBinaria (int x, int v[], int e, int d)
{
 int meio = (e + d)/2;
 if (v[meio] == x)
    return meio;
 if (e >= d)
    return -1; // não encontrado
 else
     if (v[meio] < x)
        return PesquisaBinaria(x, v, meio+1, d);
     else
        return PesquisaBinaria(x, v, e, meio-1);
}


int main(){

    
    int vetor[10]= {1,6,7,8,10,20,80,98,99,128};

    int x = PesquisaBinaria(20, vetor, 0, 10);

    if( x != -1){
        printf("Achou");
    }else
    {
        printf("Não achou");
    }
    
}