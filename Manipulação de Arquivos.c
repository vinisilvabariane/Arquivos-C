#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct aluno {
    char idade[200];
    char nome[200];
    char matricula[200];
    char curso[200];
    char turno[20];
} aluno;

void vizualiza() {
    FILE *arq;
    arq = fopen("Alunos.txt", "r");
    aluno a;
    rewind(arq);
    while (fscanf(arq, "%s %s %s %s %s", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
        printf("O nome �: %s\n", a.nome);
        printf("A idade �: %s\n", a.idade);
        printf("A matricula �: %s\n", a.matricula);
        printf("O curso �: %s\n", a.curso);
        printf("O turno �: %s\n", a.turno);
        printf("\n------------------------------------------\n");
    }
    fclose(arq);
}

void adiciona() {
    FILE *arq;
    arq = fopen("Alunos.txt", "a");
    aluno a;
    printf("Digite o nome do aluno:\n:>");
    gets(a.nome);
    printf("Digite a idade do aluno:\n:>");
    gets(a.idade);
    printf("Digite o matricula do aluno:\n:>");
    gets(a.matricula);
    printf("Digite o curso do aluno:\n:>");
    gets(a.curso);
    printf("Digite o turno do aluno:\n:>");
    gets(a.turno);
    fprintf(arq, "%s %s %s %s %s\n", a.nome, a.idade, a.matricula, a.curso, a.turno);
    fclose(arq);
}
void modifica() {
    aluno a;
    aluno b;
    FILE *arq;
    FILE *arqtemp;
    arq = fopen("Alunos.txt", "r+");
    arqtemp = fopen("ArqTemp.txt", "w");
    rewind(arq);
    char novoNome[200];
    char nomeBusca[200];
    int encontrado = 0;
    int modificado = 0;  // Vari�vel para verificar se houve modifica��o
    do {
        printf("Digite o nome buscado ou digite \"sair\":\n:>");
        gets(nomeBusca);
        if (strcmp(nomeBusca, "sair") == 0) {
            break;
        }
        encontrado = 0;
        while (fscanf(arq, "%s %s %s %s %s ", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
            if (strcmp(a.nome, nomeBusca) == 0) {
                printf("Digite o novo nome:\n:>");
                gets(b.nome);
                printf("Digite a idade:\n:>");
                gets(b.idade);
                printf("Digite a matricula:\n:>");
                gets(b.matricula);
                printf("Digite o novo curso:\n:>");
                gets(b.curso);
                printf("Digite o novo turno:\n:>");
                gets(b.turno);
                fprintf(arqtemp, "%s %s %s %s %s\n", b.nome, b.idade, b.matricula, b.curso, b.turno);
                encontrado = 1;
                modificado = 1;  // Indica que houve modifica��o nos dados
            } else {
                fprintf(arqtemp, "%s %s %s %s %s\n", a.nome, a.idade, a.matricula, a.curso, a.turno);
            }
        }
        rewind(arq);
        if (!encontrado) {
            printf("Aluno n�o encontrado.\n");
        }
    } while (!encontrado);
    fclose(arq);
    fclose(arqtemp);
    
    if (modificado) {
        remove("Alunos.txt");
        rename("ArqTemp.txt", "Alunos.txt");
        printf("Aluno modificado com sucesso.\n");
    } else {
        remove("ArqTemp.txt");
        printf("Nenhum aluno foi modificado.\n");
    }
}
void exclui() {
    aluno a;
    FILE *arq;
    FILE *arqtemp;
    arq = fopen("Alunos.txt", "r+");
    arqtemp = fopen("ArqTemp.txt", "w");
    rewind(arq);
    char nomeBusca[200];
    int encontrado = 0;
    do {
        printf("Digite o nome buscado ou digite \"sair\":\n:>");
        gets(nomeBusca);
        if (strcmp(nomeBusca, "sair") == 0) {
            break;
        }
        encontrado = 0;
        while (fscanf(arq, "%s %s %s %s %s ", a.nome, a.idade, a.matricula, a.curso, a.turno) != EOF) {
            if (strcmp(a.nome, nomeBusca) != 0) {
                fprintf(arqtemp, "%s %s %s %s %s\n", a.nome, a.idade, a.matricula, a.curso, a.turno);
            } else {
                encontrado = 1;
            }
        }
        rewind(arq);
        if (!encontrado) {
            printf("Aluno n�o encontrado.\n");
        }
    } while (!encontrado);
    fclose(arq);
    fclose(arqtemp);
    if (encontrado) {
        printf("Deseja realmente excluir o aluno? (s/n): ");
        char confirmacao[2];
        gets(confirmacao);
        if (strcmp(confirmacao, "s") == 0) {
            remove("Alunos.txt");
            rename("ArqTemp.txt", "Alunos.txt");
            printf("Aluno exclu�do com sucesso.\n");
        } else {
            remove("ArqTemp.txt");
            printf("Exclus�o cancelada.\n");
        }
    } else {
        remove("ArqTemp.txt");
    }
}
int main(){
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    do {
        printf("O que voc� deseja fazer?\n1- Vizualizar\n2- Adicionar\n3- Modificar\n4- Excluir\n5- Sair\n:>");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer de entrada
        switch (opcao) {
            case 1:
                vizualiza();
                break;
            case 2:
                adiciona();
                break;
            case 3:
                modifica();
                break;
            case 4:
                exclui();
                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Op��o inv�lida. Por favor, tente novamente.\n");
        }
    } while (opcao != 5);
    return 0;
}
