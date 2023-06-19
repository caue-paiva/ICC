#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codigo;
    int estoque;
    float preco;
    char nome[100];

} produto;

float Consulta_saldo(float *Saldo);
void Consulta_estoque(produto *pVetor, int prodADD);
void Realizar_venda(int Codigos[], int QntdVendida, produto *pVetor, int tamanho_estoque, float *Saldo, int TamanhoVetor);
void Mudar_preco(int Codigo, float Novo_preco, produto *pVetor, int tamanho_estoque);
void Aumentar_Estoque(int Codigo, int ADD_Estoque, produto *pVetor, int tamanho_estoque);
void Adicionar_Item(int *pCodigo, produto *pVetor, char nome[], int Quanti, float preco, int *pProdutos_ADD);

int main()
{

    int Espaco_DISP;

    int Produtos_ADD = 0;
    int *pProdutos_ADD = &Produtos_ADD;

    char ope[3];

    float saldo = 100.0;
    float *pSaldo = &saldo;

    int codigo = 0;
    int *pCodigo = &codigo;

    produto *pVetor_produtos;

    printf("Qual Tamanho deverá ter o estoque?");

    scanf("%d", &Espaco_DISP);

    pVetor_produtos = (produto *)malloc(Espaco_DISP * sizeof(produto));
    printf("digite um comando "); // lembrar de deletar esses outputs de teste
    scanf("  %2s", ope);

    while (strcmp(ope, "FE") != 0)
    {

        if (strcmp(ope, "IP") == 0)
        {
            char nomeADD[100];
            int estoqueESCO;
            float precoESCO;
            scanf("%s %d %f", nomeADD, &estoqueESCO, &precoESCO);
            Adicionar_Item(pCodigo, pVetor_produtos, nomeADD, estoqueESCO, precoESCO, pProdutos_ADD);
        }
        else if (strcmp(ope, "AE") == 0)
        {
            int codigoESCO;
            int estoqueADD;
            scanf("%d %d", &codigoESCO, &estoqueADD);
            Aumentar_Estoque(codigoESCO, estoqueADD, pVetor_produtos, Espaco_DISP);
        }
        else if (strcmp(ope, "RV") == 0)
        {
            int vetorVendas[20];
            int numeroID;
            int numeroVendas;
            int i = 0;
            while (scanf("%d", &numeroID) == 1 && numeroID >= 0)
            {
                vetorVendas[i] = numeroID;

                i++;
            }
            numeroVendas = numeroID; // numero vendas = numero negativo que quebra o loop e representa quantos itens serão vendidos;
            Realizar_venda(vetorVendas, numeroVendas, pVetor_produtos, Espaco_DISP, pSaldo, i);
        }
        else if (strcmp(ope, "MP") == 0)
        {
            int codigoMP;
            float PrecoMP;
            scanf("%d %f", &codigoMP, &PrecoMP);
            Mudar_preco(codigoMP, PrecoMP, pVetor_produtos, Espaco_DISP);
        }
        else if (strcmp(ope, "CE") == 0)
        {
            Consulta_estoque(pVetor_produtos, Produtos_ADD);
            printf("%d", Produtos_ADD);
        }
        else if (strcmp(ope, "CS") == 0)
        {
            float saldoDisplay = Consulta_saldo(pSaldo);
            printf("%f", saldoDisplay);
        }
        printf("digite um comando ");
        scanf(" %2s", ope);
    }

    printf("loop acabou");

    free(pVetor_produtos);
}

void Adicionar_Item(int *pCodigo, produto *pVetor, char nome[], int Quanti, float preco, int *pProdutos_ADD)
{

    int codigoAtual = *pCodigo;

    produto NovoProduto = {
        NovoProduto.codigo = codigoAtual,
        NovoProduto.estoque = Quanti,
        NovoProduto.preco = preco,
    };

    strcpy(NovoProduto.nome, nome);

    (*pCodigo)++;
    (*pProdutos_ADD)++;

    pVetor[codigoAtual] = NovoProduto;

    printf("produto adicionado com sucesso \n");
}

void Aumentar_Estoque(int Codigo, int ADD_Estoque, produto *pVetor, int tamanho_estoque)
{
    for (int i = 0; i < tamanho_estoque; i++)
    {
        if (pVetor[i].codigo == Codigo)
        {
            pVetor[i].estoque += ADD_Estoque;
            break;
        }
    }
    printf("estoque aumentado com sucesso \n");
}

void Mudar_preco(int Codigo, float Novo_preco, produto *pVetor, int tamanho_estoque)
{
    for (int i = 0; i < tamanho_estoque; i++)
    {
        if (pVetor[i].codigo == Codigo)
        {
            pVetor[i].preco = Novo_preco;
            break;
        }
    }
    printf("preco alterado com sucesso \n");
}

void Realizar_venda(int Codigos[], int QntdVendida, produto *pVetor, int tamanho_estoque, float *Saldo, int TamanhoVetor)
{
    float total = 0.0;
    int Qntd_vendidaPosi = QntdVendida * -1;
    for (int i = 0; i < TamanhoVetor; i++)
    {

        for (int j = 0; j < tamanho_estoque; j++)
        {
            if (pVetor[j].codigo == Codigos[i])
            {
                printf("%s %f \n", pVetor[j].nome, pVetor[j].preco);
                pVetor[j].estoque -= Qntd_vendidaPosi;
                total += (pVetor[j].preco * Qntd_vendidaPosi);
                break;
            }
        }
    }
    *Saldo += total;
    printf("Total: %f", total);

    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
    printf(" venda realizada com sucesso \n");
}

void Consulta_estoque(produto *pVetor, int prodADD)
{
    for (int i = 0; i < prodADD; i++)
    {
        printf("%d %s %d \n", pVetor[i].codigo, pVetor[i].nome, pVetor[i].estoque);
    }

    for (int i = 0; i < 50; i++)
    {
        printf("-");
    }
    printf(" consulta realizada com sucesso \n");
}

float Consulta_saldo(float *Saldo)
{
    float saldo = *Saldo;

    printf("saldo consultado com sucesso \n");
    return saldo;
}