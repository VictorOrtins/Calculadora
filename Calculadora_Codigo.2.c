#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

//bibliotecas adicionadas

#define TAM_STRING 60
#define PI 3.14159265
#define MAX 100
#define NUM_RAIZ_NAO_REAL -9283929
#define TAM_EQ_SEGUNDO_GRAU 5
#define TAM_EQ_TERCEIRO_GRAU 7
#define TAM_RAIZ_QUADRADA 2


//constantes definidas, esses valores não sofrerão alteração durante o código


//Essa struct é meio que uma gambiarrazinha pra uma função conseguir retornar mais de um valor. Ao invés de retornar só um int, um float ou um double, ele retorna a struct inteira, o que facilitou na hora de armazenar os resultados das equações de segundo e terceiro grau. Um vetor poderia ser usado também, porém fica bem mais legível com struct, então achei melhor utilizá-la.


void corretor_de_enter();
float soma(float n1, float n2);
float sub(float n1, float n2);
float mult(float n1, float n2);
float divisao(float n1, float n2);
long long int fatorial(long long int numero);
float raiz_quadrada(float numero);
void equacao_segundo_grau(float a, float b, float c, float *x1, float *x2);
float potencia(float base, float expoente);
void equacao_cubica(float a, float b, float c, float d, float *x1, float *x2, float *x3);
void menu_aritmeticas();
void historico(float n[MAX][3], char sinal[], int i );
void limpar_historico();
void volta_menu();
void historico_eq_segundo_grau(int i, float *resultados_segundo_grau[MAX]);
void historico_eq_terceiro_grau(int i, float *resultados_terceiro_grau[MAX]);
void historico_fatorial(int i, long long int resultados_fatorial[MAX][2]);
void historico_raiz_quadrada (int i, float *resultados_raiz_quadrada[MAX]);
int menu_equacoes_raiz(int equacao, int *controle, int *quebra_menu, int contador, float **vetor_equacao);

//funções declaradas, criamos funções para cada operação utlizada, além de algumas auxiliares

int main(void) {
  system("cls");
  system("color 02");

  int var_controle_1, var_controle_2, controle_menu = 0;
  int var_controle_3, var_controle_4, i;
  int identificador_equacao, var_controle_operacoes;

  //variáveis de controle do código, que serão alteradas  para que do-whiles sejam continuados ou quebrados, fazendo com que o código funcione perfeitamente

  float num[MAX][3];
  char sinal[MAX];
  //vetores que serão utilizados nas operações aritméticas

  float *resultados_segundo_grau[MAX];
  for (int i = 0; i < MAX; i++){
    resultados_segundo_grau[i] = (float*)malloc(TAM_EQ_SEGUNDO_GRAU*sizeof(float));
  }

  float *resultados_terceiro_grau[MAX];
  for (int i = 0; i < MAX; i++){
    resultados_terceiro_grau[i] = (float*)malloc(TAM_EQ_TERCEIRO_GRAU*sizeof(float));
  }

  long long int resultados_fatorial[MAX][2];
  float *resultados_raiz_quadrada[MAX];
  for (int i = 0; i < MAX; i++){
    resultados_raiz_quadrada[i] = (float*)malloc(TAM_RAIZ_QUADRADA*sizeof(float));
  }


  char nome[TAM_STRING];
  //definida a string variavel "nome", com o tamanho pré-estabelecido

  float x1, x2;
  //Definidas variáveis a serem usadas nas equações

  puts("***** CALCULADORA 2021.3 *****\n");
  printf("Insira seu nome: ");
  /*começo da interface, apresentando o projeto e solicitando o nome do usuário*/

  fgets(nome,TAM_STRING, stdin);
  corretor_de_enter(nome);

  printf("\nOla %s!\nBem-vindo ao menu da Calculadora 2021.3, alem de resolver"
   " operacoes aritmeticas,\nesse programa tambem calcula equacoes de segundo e"
   " terceiro grau.\n\n", nome);

  do{
    puts("------------MENU------------\n");
    puts("1. Operacoes Aritmeticas");
    puts("2. Equacao de Segundo Grau");
    puts("3. Equacao de Terceiro Grau");
    puts("4. Fatorial");
    puts("5. Raiz Quadrada");
    puts("6. Encerrar\n");
  /*após solicitar o nome do usuário, exibe apresentação e o menu da calculadora, solicitando o cálculo desejado.*/

    printf("Opcao: ");
    scanf("%d", &var_controle_1);
    /*coleta qual opção foi escolhida pelo usuário e atribui seu valor à variavel de controle, que será utilizada no switch case.*/

    system("cls");
    puts("Carregando...");
    sleep(1); //Estética

    switch(var_controle_1){

      case 1:
        identificador_equacao = 1;
        system("cls");

        puts("Insira o primeiro numero, o caracter da operacao desejada, e o segundo numero (no formato x + y)\n");
        puts("Obs: Para calcular o valor da raiz quadrada de um numero, utilize o operador '@', elevando o numero a 0.5");
        puts("No formato (X^0.5 = Y)");
        puts("\n------Operadores------\n");
        puts(" + --> adicao");
        puts(" - --> subtracao");
        puts(" * --> multiplicacao");
        puts(" / --> divisao");
        puts(" @ --> potenciacao");
        puts("\n----------------------\n"); //Explicações ao usuário

        var_controle_1 = 0; //Para que o do-while maior comece já com a condição sendo satisfeita


        do{
          i = 0;

          var_controle_2 = 0; //para que o do-while menor comece já com a condição sendo satisfeita

          scanf("%f %c %f", &num[i][0], &sinal[i], &num[i][1]);
          goto Pulinho; //Esse pulinho impede o outro scanf no caso de o usuário querer utilizar o resultado anterior

          do{
            i++; //Para salvar em lugares diferentes do array
            printf("%.4f", num[i-1][2]); //Printa o número anterior, que foi solicitado pelo usuário
            scanf(" %c %f" , &sinal[i] , &num[i][1] ); //scan do sinal e do número
            num[i][0] = num[i-1][2]; //O primeiro número dessa operação é resultado da coluna anterior

            Pulinho:
            switch (sinal[i]){
              case '+': //Caso soma
                system("cls");
                num[i][2] = soma(num[i][0], num[i][1]); //Função soma

                Escolha_Soma: //Label para quando o usuário digitar errado
                printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                menu_aritmeticas(); //Função para mostrar o menu
                printf("\nOpcao: ");
                scanf("%d", &var_controle_3 );


            switch(var_controle_3){
              case 1:
                system("cls");
                break;

              case 2:
                limpar_historico(); //Função que limpa o histórico das operações, a pedido do usuário
                var_controle_2 = 1; //Quebra o do-while menor, reseta o contador (e assim o histórico) e ele volta para a parte em que há um scanf de 2 numeros e 1 sinal
                break;

              case 3:
                historico(num,sinal,i); //Mostra o histórico de operações, a pedido do usuário
                goto Escolha_Soma;
                break;

              case 4:
                var_controle_1 = 1; //Quebra o do-while menor
                var_controle_2 = 1;//Quebra o do-while maior e volta para o menu de operações aritméticas
                volta_menu();
                break;

              default:
                system("cls");
                printf("Digite uma Opcao valida: ");
                goto Escolha_Soma; //Tratamento de erro
                break;
            }
            break;

              case '-': //Caso subtração
                system("cls");
                num[i][2] = sub(num[i][0], num[i][1]); //função subtração

                Escolha_Sub: //Label para tratamento de erro
                printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                menu_aritmeticas(); //Função para mostrar o menu

                printf("\nOpcao: ");
                scanf("%d",&var_controle_3 );

                switch(var_controle_3){
                  case 1:
                    system("cls");
                    break;

                  case 2:
                    limpar_historico(); //Limpa o histórico, a pedidos do usuário
                    var_controle_2 = 1;//Quebra o do-while menor, assim resetando o contador, então começando as operações do zero
                    break;

                  case 3:
                    historico(num,sinal,i); //Mostra o histórico, como solicitado ao usuário
                    goto Escolha_Sub;
                    break;

                  case 4:
                    var_controle_1 = 1; //Quebra o do-while maior
                    var_controle_2 = 1;//Quebra o do-while menor
                    volta_menu();
                    break;

                  default:
                    system("cls");
                    printf("Digite uma Opcao valida:\n\n");
                    goto Escolha_Sub; //Volta para a escolha de opçõe, já que o usuário digitou algo inválido
                    break;
                }
                break;

                case '*': //Caso multiplicação
                  system("cls");
                  num[i][2] = mult(num[i][0], num[i][1]); //Função multiplicação

                  Escolha_Mult: //Label para tratamento de erro
                  printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                  menu_aritmeticas(); //Função para mostrar o menu

                  printf("\nOpcao: ");
                  scanf("%d",&var_controle_3 );

                  switch(var_controle_3){
                    case 1:
                      system("cls");
                      break;

                    case 2:
                      limpar_historico(); //Limpa o histórico, a pedidos do usuário
                      var_controle_2 = 1; //Quebra o do-while menor, assim resetando o contador, então começando as operações do zero
                      break;

                    case 3:
                      historico(num,sinal,i);
                      //Mostra o histórico, como solicitado ao usuário
                      goto Escolha_Mult;
                      break;

                    case 4:
                      var_controle_1 = 1; //Quebra o do-while maior
                      var_controle_2 = 1; //Quebra o do-while menor
                      volta_menu();
                      break;

                    default:
                      system("cls");
                      printf("Digite uma Opcao valida:\n\n");
                      goto Escolha_Mult; //Volta para a escolha de opções, já que o usuário digitou algo inválido
                      break;
                  }
                  break;

                case '/':
                  system("cls"); //Caso divisão
                  num[i][2] = divisao(num[i][0], num[i][1]); //Função Divisão

                  Escolha_Div: //Label para tratamento de erro
                  printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                  menu_aritmeticas(); //Função para mostrar o menu

                  printf("\nOpcao: ");
                  scanf("%d",&var_controle_3 );

                  switch(var_controle_3){
                    case 1:
                      system("cls");
                      break;

                    case 2:
                      limpar_historico(); //Limpa o histórico, a pedidos do usuário
                      var_controle_2 = 1; //Quebra o do-while menor, assim resetando o contador, então começando as operações do zero
                      break;

                    case 3:
                      historico(num,sinal,i);//Mostra o histórico, como solicitado ao usuário
                      goto Escolha_Div;

                      break;

                    case 4:
                      var_controle_1 = 1; //Quebra o do-while maior
                      var_controle_2 = 1; //Quebra o do-while menor
                      volta_menu();
                      break;

                    default:
                      system("cls");
                      printf("Digite uma Opcao valida:\n\n");
                      goto Escolha_Div; //Volta para a escolha de opções, já que o usuário digitou algo inválido
                      break;
                  }

                  break;

              case '@':
                system("cls");
                num[i][2] = potencia(num[i][0], num[i][1]);//Resultado

                Escolha_Potencia: //Label para tratamento de erro
                printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                menu_aritmeticas(); //Mostra o menu


                printf("\nOpcao: ");
                scanf("%d",&var_controle_3 );

                switch(var_controle_3){
                  case 1:
                    system("cls");
                    break;

                  case 2:
                    limpar_historico(); //Limpa o histórico, como solicitado do usuário
                    var_controle_2 = 1;//Quebra o do-while menor, para que o contador resete
                    break;

                  case 3:
                    historico(num,sinal,i); //Mostra o histórico
                    goto Escolha_Potencia; //Vai para a escolha de opções quando o histórico termina
                    break;

                  case 4:
                    var_controle_1 = 1; //Quebra o do-while maior
                    var_controle_2 = 1; //Quebra o do-while menor
                    volta_menu(); //Função que volta para o menu
                    break;

                  default:
                    system("cls");
                    printf("Digite uma Opcao valida:\n\n");
                    goto Escolha_Potencia; //Vai para a escolha de opções, tratando o erro do usuário
                    break;
                }

                break;


              }

          }while(var_controle_2 == 0); //Declaração do do-while menor

        }while(var_controle_1 ==  0); //Declaração do do-while maior

            break;







      case 2 :
        var_controle_2 = 0;//Para que o do-while maior já comece com a condição sendo satisfeita
         //declaração de variáveis dos índicides da equacao

        int contador_segundo_grau = 0; //contador do histórico setado como 0

        identificador_equacao = 2;

        do{
          system("cls");


          puts("-----EQUACAO DE SEGUNDO GRAU-----\n");
          puts("Ax^2 + Bx + C");
          printf("\n%s, digite os indices A, B e C da equacao do segundo grau nessa, ordem:\n", nome);
          scanf("%f %f %f", &resultados_segundo_grau[contador_segundo_grau][0], &resultados_segundo_grau[contador_segundo_grau][1], &resultados_segundo_grau[contador_segundo_grau][2]); //Pega os índices da equacao, armazenando sempre nas posições 0,1 e 2, respectivamente,  do vetor resultados

          /*
            resultados_segundo_grau[contador_segundo_grau][0] = indice a
            resultados_segundo_grau[contador_segundo_grau][1] = indice b
            resultados_segundo_grau[contador_segundo_grau][0] = indice c
          */


          if(resultados_segundo_grau[contador_segundo_grau][0] == 0) //se o indice a é igual a 0, não é uma equacao do segund grau
            puts("\nIndice A = 0, essa nao e uma equacao de segundo grau\n");

          else{
            printf("\n%.2fx^2 + %.2fx + %.2f = 0\n", resultados_segundo_grau[contador_segundo_grau][0], resultados_segundo_grau[contador_segundo_grau][1], resultados_segundo_grau[contador_segundo_grau][2]);
            //print da equacao

            equacao_segundo_grau(resultados_segundo_grau[contador_segundo_grau][0], resultados_segundo_grau[contador_segundo_grau][1], resultados_segundo_grau[contador_segundo_grau][2], &x1, &x2); //Realiza a equacao do segundo grau
            if (x1 == NUM_RAIZ_NAO_REAL){ //Esse é o valor que retorna se a equacao não tem raízes reais
              resultados_segundo_grau[contador_segundo_grau][3] = x1; //Para ser identificado na hora de printar o histórico
              printf("Essa equacao nao tem raizes reais");
            }
            else {
              resultados_segundo_grau[contador_segundo_grau][3] = x1;
              resultados_segundo_grau[contador_segundo_grau][4] = x2;
              printf("Essas sao as raizes da equacao do segundo grau: %f %f", x1, x2);
            }
          }
            /*
          for (int j = 0; j <= contador_segundo_grau; j++){
            if (resultados_segundo_grau[j][3] == NUM_RAIZ_NAO_REAL){ //Se x1 é o valor das raízes não reais
              printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao ha raizes reais\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que não há raízes
            }
            else if (resultados_segundo_grau[j][0] == 0){ //Se a = 0
              printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao eh uma equacao do segundo grau\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que não é uma equacao do segundo grau
            }
            else{
              printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f, x2 = %.4f\n\n",j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2], resultados_segundo_grau[j][3], resultados_segundo_grau[j][4]); //Printa devidamente a equação do segundo grau e suas raízes reais, quando existirem
            }
          }
          */

          puts("\n");
          contador_segundo_grau = menu_equacoes_raiz(identificador_equacao, &var_controle_1, &var_controle_2, contador_segundo_grau, resultados_segundo_grau);
        }while(var_controle_2 == 0);
        break;








      case 3:
      var_controle_4 = 0;//Para que o do-while maior já comece com a condição sendo satisfeita
      float x3;
      int contador_eq_terceiro_grau = 0; //contador do vetor setado como 0
      identificador_equacao = 3;

        do{

          system("cls");

          puts("-----EQUACAO DE TERCEIRO GRAU-----\n");
          puts("Ax^3 + Bx^2 + Cx + D");
          printf("\n%s, digite os indices A, B, C e D da equacao do terceiro grau, nessa ordem:\n", nome);

          scanf("%f %f %f %f", &resultados_terceiro_grau[contador_eq_terceiro_grau][0], &resultados_terceiro_grau[contador_eq_terceiro_grau][1], &resultados_terceiro_grau[contador_eq_terceiro_grau][2], &resultados_terceiro_grau[contador_eq_terceiro_grau][3]); //scanf dos 4 índices que serão utilizados na equacao


          if(resultados_terceiro_grau[contador_eq_terceiro_grau][0] == 0){ //se o indice a é igual a 0, não é uma equacao do terceiro grau
            puts("\nIndice A = 0, essa nao e uma equacao de terceiro grau\n");
          }


          else{
            printf("\n%.2fx^3 + %.2fx^2 + %.2fx + %.2f = 0\n",resultados_terceiro_grau[contador_eq_terceiro_grau][0],resultados_terceiro_grau[contador_eq_terceiro_grau][1], resultados_terceiro_grau[contador_eq_terceiro_grau][2], resultados_terceiro_grau[contador_eq_terceiro_grau][3]);

            equacao_cubica(resultados_terceiro_grau[contador_eq_terceiro_grau][0], resultados_terceiro_grau[contador_eq_terceiro_grau][1], resultados_terceiro_grau[contador_eq_terceiro_grau][2], resultados_terceiro_grau[contador_eq_terceiro_grau][3], &x1, &x2, &x3); //Função da equacao de terceiro grau

            resultados_terceiro_grau[contador_eq_terceiro_grau][4] = x1;
            resultados_terceiro_grau[contador_eq_terceiro_grau][5] = x2;
            resultados_terceiro_grau[contador_eq_terceiro_grau][6] = x3;

            if (x3 == NUM_RAIZ_NAO_REAL){ //Valor para raíz não real
              if (x2 == NUM_RAIZ_NAO_REAL){ //Valor para raíz não real
                printf("Essa eh a raiz da equacao: %f", x1); //se x2 e x3 tem o valor de raíz não real, apenas x1 é raiz real

              }
              else{
                printf("Essas sao as raizes da equacao: %f %f", x1, x2); //se x3 tem o valor de raíz não real, apenas x1 e x2 são raízes reais
              }
            }
            else{
              printf("Essas sao as raizes da equacao: %f %f %f", x1, x2, x3); //As 3 raízes são reais
            }
          }


          puts("\n");
          contador_eq_terceiro_grau = menu_equacoes_raiz(identificador_equacao, &var_controle_3, &var_controle_4, contador_eq_terceiro_grau, resultados_terceiro_grau);

        }while(var_controle_4 == 0); //declaração do do-while utilizado no case
        break;
      break;




      case 4:
        system("cls");
        identificador_equacao = 4;
        int contador_fatorial = 0; //Contador de fatorial setado como 0 para que o vetor do histórico inicie em 0
        printf("%s, essa eh a nossa calculadora de fatorial\n\n", nome);
        var_controle_3 = 0; //Para que a variável do do-while já inicie satisfazendo a condição

        do{

          printf("Digite o numero: ");
          scanf("%lld", &resultados_fatorial[contador_fatorial][0]); //Primeira posição do array é preenchido com o número digitado
          resultados_fatorial[contador_fatorial][1] = fatorial(resultados_fatorial[contador_fatorial][0]); //Função fatorial, segunda posição do array é preenchido com o resultado

          printf("\nEsse eh o resultado de %lld! = %lld\n", resultados_fatorial[contador_fatorial][0], resultados_fatorial[contador_fatorial][1]);

          puts("\n");
          escolha_de_opcoes_fatorial: //Label para tratamento de erro
          puts("O que deseja fazer agora?\n");
          puts("1. Realizar outra operacao com fatorial");
          puts("2. Historico de Fatorial");
          puts("3. Retornar ao menu\n");
          scanf("%d", &var_controle_4);

          switch(var_controle_4){
            case 1:
              system("cls");
              puts("Preparando outra operacao...");
              sleep(1);
              system("cls");
              contador_fatorial++; //contador incrementado, para que o histórico sea propriamente exibido
              break;


            case 2:
              historico_fatorial(contador_fatorial, resultados_fatorial); //utilização da função de histórico de fatorial
              goto escolha_de_opcoes_fatorial; //Vai para as opções

              break;

            case 3:
              volta_menu();
              var_controle_3 = 1; //Quebra o do-while

              break;

            default:
              system("cls");
              puts("Digite uma opcao valida ");
              goto escolha_de_opcoes_fatorial; //Vai para o começo de escolhas, como tratamento de erro
              break;
          }

        }while(var_controle_3 == 0);
      break;

      case 5:
        identificador_equacao = 5;
        var_controle_4 = 0; //var setada em 0 para que a condição do do-while já seja satisfeita de início
        int contador_raiz_quadrada = 0; //contador definido como 0 par que o array comece sendo preenchido em 0

        system("cls");
        printf("%s, essa eh a nossa calculadora de raizes quadradas.\nTal operacao pode ser feita dentro das operacoes aritmeticas,elevando um numero a 0.5,\nmas preferimos tambem colocar uma opcao no menu para que o usuario possa fazer tal operacao\n\n", nome);

        do{
          if (contador_raiz_quadrada != 0){
                system("cls");
          }

          var_controle_3 = 0;//var setada em 0 para que a condição do do-while já seja satisfeita de início
          printf("Digite o numero: ");
          scanf("%f", &resultados_raiz_quadrada[contador_raiz_quadrada][0]); //scanf do número que será calculada a raiz quadrada

          resultados_raiz_quadrada[contador_raiz_quadrada][1] = raiz_quadrada(resultados_raiz_quadrada[contador_raiz_quadrada][0]); //O resultado ocupa a segunda posição do vetor

          printf("\nEssa eh a raiz quadrada de %.4f: %f\n", resultados_raiz_quadrada[contador_raiz_quadrada][0], resultados_raiz_quadrada[contador_raiz_quadrada][1]);

          puts("\n");
          contador_raiz_quadrada = menu_equacoes_raiz(identificador_equacao, &var_controle_4, &var_controle_3, contador_raiz_quadrada, resultados_raiz_quadrada);

        }while(var_controle_3 == 0);

        break;

      case 6:
          controle_menu = 1; //Quebra o do-while do menu
          system("cls");
          puts("Programa Encerrado com Sucesso");
          break;


      default : //Tratamento de erro
        system("cls");
        puts("Opcao Invalida!\n");
        puts("Escolha uma opcao valida:\n");
      break;

    /*utilização do switch case para as diferentes opções apresentadas, alternando o comando de acordo com cada escolha*/

    }
  }while(controle_menu == 0);

  return 0;
}

void corretor_de_enter(char nome[]){
  int tam;
  tam = strlen(nome);

    if (nome[tam - 1] == '\n'){ //Se o penúltimo char for um \n
      nome[tam - 1] = '\0'; //Transformá-lo em \0 (finalizador)
    }
}


float raiz_quadrada(float numero){
  float auxiliar, raiz_quadrada;
  //Método babilônico, a base desse método é encontrar um quadrado de lados que sejam a raíz do número pretendido a partir da diminuição progressiva da base e do aumento progressivo da altura, até que os dois se igualem

  //Pense que o número 101 foi entrado pelo
  raiz_quadrada = numero / 2; //50.5
  auxiliar = 0;

  while(raiz_quadrada != auxiliar){
    auxiliar = raiz_quadrada; //50.5 //Na segunda rodada: 26.25
    raiz_quadrada = (numero/auxiliar + auxiliar) / 2;
  } // ((101/50.5) + 50.5)/2 = 26.25 //Na segunda rodada: ((101/26.25) + 26.25)/2 = 15.048809 e assim vai, até auxiliar e raiz quadrada forem iguais, que nesse caso é quando forem 10.049875, que é a raiz de 101

  return raiz_quadrada;
}

void equacao_segundo_grau(float a, float b, float c, float *x1, float *x2){
  float delta;

  delta = b*b - 4*a*c; //Cálculo do delta

  if (delta < 0){
    *x1 = NUM_RAIZ_NAO_REAL; //Indica que não há raízes reais
  }
  else{
      *x1 = (-b + raiz_quadrada(delta))/(2*a);
      *x2 = (-b - raiz_quadrada(delta))/(2*a);
  }
}

float potencia(float base, float expoente){
  int expoente_exato, aux_exata;
  float aux;

  aux = expoente*2;
  expoente_exato = expoente;
  aux_exata = aux;

  if (expoente == 0){
    return 1;
  }
  else {
    if (expoente > 0){
      if ( (expoente != expoente_exato)/*testa de o expoente é não exato*/ && (aux == aux_exata)/* testa se o expoente multiplicado por dois se torna exato*/ ){
        return raiz_quadrada(potencia(base,aux));
      }
      else if(aux != aux_exata){
        puts("ERRO");
        return 0;
      }
      else{
        return base*potencia(base, expoente - 1);
      }
    }
    else{
      if( (expoente != expoente_exato) && (aux == aux_exata) ){
        return raiz_quadrada(potencia(base,aux));
      }

    else if(aux != aux_exata){
      puts("ERRO");
      return 0;
    }

      else{
        return (1/base)*potencia(base, expoente + 1);
      }
    }
  }
}

void equacao_cubica(float a, float b, float c, float d, float *x1, float *x2, float *x3){

  float A, B, C;
  /*
    Divide todos índices por A
  */
  A = b/a;
  B = c/a;
  C = d/a;


  float p, q;
  p = B - ((A*A)/3);
  q = C + ((2*A*A*A)/27) - ((A*B)/3);

  /* p e q serão variáveis importantes daqui pra lá, então, setá-las foi necessário*/

  //x = y - A/3. Houve uma mudança de variável, agora é uma função y^3 + y^2 + y + z = 0

  float delta;
  delta = ((q*q)/4) + ((p*p*p)/27); //delta_1. Se ele for maior ou igual a 0, 2 deltas são usados

  if (delta >= 0){ //Se delta for maior que 0
    float y1;

    y1 = cbrt((-q)/2 + raiz_quadrada(delta)) + cbrt((-q)/2 - raiz_quadrada(delta));
    float y2, y3, delta_2;
    delta_2 = -(3*y1*y1 + 4*p);

    if (delta_2 >= 0){
      if (delta_2 == 0){
        y2 = -y1/2;
        *x1 = y1 - A/3;
        *x2 = y2 - A/3;
        *x3 = NUM_RAIZ_NAO_REAL; //Raíz não real


      }
      else{
        y2 = -y1 + raiz_quadrada(delta_2)/2;
        y3 = -y1 - raiz_quadrada(delta_2)/2;
        *x1 = y1 - A/3;
        *x2 = y2 - A/3;
        *x3 = y3 - A/3; //Todas raízes reais

      }
    }
    else {
      *x1 = y1 - A/3;
      *x2 = NUM_RAIZ_NAO_REAL;
      *x3 = NUM_RAIZ_NAO_REAL; //Duas raízes não reai
    }
  }

    else{
      float P, teta;
      P = raiz_quadrada((q*q)/4 + raiz_quadrada(potencia(delta,2)));
      teta = acos(-q/(2*P));
      float y1, y2, y3;

      y1 = 2*(cbrt(P))*cos(teta/3);
      y2 = 2*(cbrt(P))*cos((teta + 2*PI)/3);
      y3 = 2*(cbrt(P))*cos((teta + 4*PI)/3);

      *x1 = y1 - A/3;
      *x2 = y2 - A/3;
      *x3 = y3 - A/3; //Todas raízes reais
    }
  }


  float soma(float n1, float n2){
    float soma;

    soma = n1+n2;

    return soma;
}


float sub(float n1, float n2) {
    float sub;

    sub = n1-n2;

    return sub;

}

float mult(float n1, float n2) {
    float mult;

    mult = n1*n2;

    return mult;
}


float divisao(float n1, float n2){
    float divisao;

    divisao = n1/n2;

    return divisao;
}

long long int fatorial(long long int numero){

  if (numero == 0){

    return 1;

  }

  else if (numero < 0){

	return 0;

  }

  else{

    return numero*fatorial(numero - 1);

  }

}

void menu_aritmeticas(){

  puts("\n---------------------Menu---------------------\n");
  puts("1. Continuar utilizando o resultado anterior");
  puts("2. Limpar o historico e continuar");
  puts("3. Mostrar historico");
  puts("4. Voltar ao menu"); //Estética

}

void historico(float n[MAX][3], char sinal[], int i ){

  system("cls");

  puts("----------Historico----------\n");

  for(int j = 0; j <= i; j++) /*uso do laço de repetição for para repetir os comandos de acordo com o valor da variável i (que será definida de acordo com a quantidade de operações realizadas pelo usuário)*/
    printf("%d: %.4f %c %.4f = %.4f\n\n", j+1, n[j][0], sinal[j], n[j][1], n[j][2]); //Exibição do histórico

  puts("-----------------------------\n");

  system("pause");

  system("cls");
}

void limpar_historico(){
  system("cls");

  puts("Limpando Historico...");
  sleep(1);           //Estética
  system("cls");


}

void volta_menu(){
  system("cls");
  puts("Voltando ao menu...");
  sleep(1);           //Estética
  system("cls");
}

void historico_eq_segundo_grau(int i, float *resultados_segundo_grau[MAX]){
  system("cls");
  for (int i = 0; i < MAX; i++){
    resultados_segundo_grau[i] = (float*)malloc(5*sizeof(float));
  }

  puts("----------Historico----------\n");

  for (int j = 0; j <= i; j++){
    if (resultados_segundo_grau[j][3] == NUM_RAIZ_NAO_REAL){ //Se x1 é o valor das raízes não reais
      printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao ha raizes reais\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que não há raízes
    }
    else if (resultados_segundo_grau[j][0] == 0){ //Se a = 0
      printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao eh uma equacao do segundo grau\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que não é uma equacao do segundo grau
    }
    else{
      printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f, x2 = %.4f\n\n",j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2], resultados_segundo_grau[j][3], resultados_segundo_grau[j][4]); //Printa devidamente a equação do segundo grau e suas raízes reais, quando existirem
    }
  }

  puts("-----------------------------\n");

  system("pause");

  system("cls");

}

void historico_eq_terceiro_grau(int i, float *resultados_terceiro_grau[MAX]){
  system("cls");
  for (int i = 0; i < MAX; i++){
    resultados_terceiro_grau[i] = (float*)malloc(7*sizeof(float));
  }

  puts("----------Historico----------\n");

  for (int j = 0; j <= i; j++){
    if (resultados_terceiro_grau[j][0] == 0){
        printf(" %d: %.4fx^3 + %.4fx^2 + %.4fx + %.4f = 0 ==> Nao eh uma equacao do terceiro grau\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3]); //Printa a única raíz real
      }
    else if (resultados_terceiro_grau[j][6] == NUM_RAIZ_NAO_REAL){ //Se x2 é uma raíz não real
      if (resultados_terceiro_grau[j][5] == NUM_RAIZ_NAO_REAL){ //Se x2 e x3 não são raízes reais
        printf(" %d: %.4fx^3 + %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3], resultados_terceiro_grau[j][4]); //Printa a única raíz real
      }
      else { //Se x1 e x3 são raízes reais
        printf(" %d: %.4fx^3 + %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f, x2 = %.4f\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3], resultados_terceiro_grau[j][4], resultados_terceiro_grau[j][5]); //Printa as duas raízes reais
      }
    }
    else{ //Se as 3 raízes são reais
      printf(" %d: %.4fx^3 + %f.4x^2 + %.4fx + %f = 0 ==> x1 = %.4f, x2 = %.4f, x3 = %.4f\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3], resultados_terceiro_grau[j][4], resultados_terceiro_grau[j][5], resultados_terceiro_grau[j][6]); //Printa as 3 raízes reais
    }
  }

  puts("-----------------------------\n");

  system("pause");

  system("cls");

}

void historico_fatorial(int i, long long int resultados_fatorial[MAX][2]){
  system("cls");


  puts("----------Historico----------\n");

  for (int j = 0; j <= i; j++){
    printf("%d: %lld! = %lld\n", j+1, resultados_fatorial[j][0], resultados_fatorial[j][1]);
  } //Printa o histórico de fatorial

  puts("-----------------------------\n");

  system("pause");

  system("cls");

}

void historico_raiz_quadrada (int i, float *resultados_raiz_quadrada[MAX]){
  system("cls");

  for (int i = 0; i < MAX; i++){
    resultados_raiz_quadrada[i] = (float*)malloc(2*sizeof(float));
  }

   puts("----------Historico----------\n");

  for (int j = 0; j <= i; j++){
    printf("%d: raiz quadrada de %.4f = %.4f\n\n", j+1, resultados_raiz_quadrada[j][0], resultados_raiz_quadrada[j][1]); //Printa o histórico de raiz quadrada
  }

  puts("-----------------------------\n");

  system("pause");

  system("cls");

}

int menu_equacoes_raiz(int equacao, int *controle,int *quebra_menu, int contador, float *vetor_equacao[MAX]){

  Escolha_de_opcoes: //Label para tratamento de erro

  if (equacao == 2){
    /*
    for (int i = 0; i < MAX; i++){
      vetor_equacao[i] = (float*)malloc(TAM_EQ_SEGUNDO_GRAU*sizeof(float));
    }
    */

    puts("Escolha a opcao desejada:\n");
    puts("1. Realizar outra equacao do segundo grau");
    puts("2. Mostrar historico de equacoes do segundo grau");

  }
  else if (equacao == 3){
    /*
    for (int i = 0; i < MAX; i++){
      vetor_equacao[i] = (float*)malloc(TAM_EQ_TERCEIRO_GRAU*sizeof(float));
    }
    */

    puts("Escolha a opcao desejada:\n");
    puts("1. Realizar outra equacao do terceiro grau");
    puts("2. Mostrar historico de equacoes do terceiro grau");

  }
  else if (equacao == 5){
    /*
    for (int i = 0; i < MAX; i++){
      vetor_equacao[i] = (float*)malloc(TAM_RAIZ_QUADRADA*sizeof(float));
    }
    */

    puts("Escolha a opcao desejada:\n");
    puts("1. Realizar outra operacao de raiz quadrada");
    puts("2. Mostrar historico de operacoes de raizes quadradas");


  }

  puts("3. Retornar ao Menu\n");
  printf("Opcao: ");
  scanf("%d", &*controle);

  switch(*controle){

    case 1:
      system("cls");
      puts("Preparando outra operacao...");
      if (equacao == 5){
        system("cls");
      }
      sleep(1);
      if (equacao == 5){
        sleep(2);
      }
      contador++;
      break;

    case 2:
      if (equacao == 2){
        historico_eq_segundo_grau(contador, vetor_equacao); //função que printa o historico da equacao do segundo grau
      }
      else if(equacao == 3){
        historico_eq_terceiro_grau(contador, vetor_equacao); //função que printa o historico da equacao do segundo grau
      }
      else if(equacao == 5){
         historico_raiz_quadrada(contador, vetor_equacao); //função que printa o historico da equacao do segundo grau
      }

      goto Escolha_de_opcoes;
      break;

    case 3:
      *quebra_menu = 1;
      volta_menu(); //Utilização da função criada para o retorno ao Menu do programa
      break;


    default:
      system("cls");
      sleep(1); //Espera um segundo antes de mostrar as próximas saídas
      puts("Opcao Invalida!\n");
      puts("Escolha uma opcao valida:\n");
      goto Escolha_de_opcoes; //Vai para o início das escolhas, tratando o erro do usuário
      break;
  }
}
