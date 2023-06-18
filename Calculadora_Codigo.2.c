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


//constantes definidas, esses valores n�o sofrer�o altera��o durante o c�digo


//Essa struct � meio que uma gambiarrazinha pra uma fun��o conseguir retornar mais de um valor. Ao inv�s de retornar s� um int, um float ou um double, ele retorna a struct inteira, o que facilitou na hora de armazenar os resultados das equa��es de segundo e terceiro grau. Um vetor poderia ser usado tamb�m, por�m fica bem mais leg�vel com struct, ent�o achei melhor utiliz�-la.


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

//fun��es declaradas, criamos fun��es para cada opera��o utlizada, al�m de algumas auxiliares

int main(void) {
  system("cls");
  system("color 02");

  int var_controle_1, var_controle_2, controle_menu = 0;
  int var_controle_3, var_controle_4, i;
  int identificador_equacao, var_controle_operacoes;

  //vari�veis de controle do c�digo, que ser�o alteradas  para que do-whiles sejam continuados ou quebrados, fazendo com que o c�digo funcione perfeitamente

  float num[MAX][3];
  char sinal[MAX];
  //vetores que ser�o utilizados nas opera��es aritm�ticas

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
  //definida a string variavel "nome", com o tamanho pr�-estabelecido

  float x1, x2;
  //Definidas vari�veis a serem usadas nas equa��es

  puts("***** CALCULADORA 2021.3 *****\n");
  printf("Insira seu nome: ");
  /*come�o da interface, apresentando o projeto e solicitando o nome do usu�rio*/

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
  /*ap�s solicitar o nome do usu�rio, exibe apresenta��o e o menu da calculadora, solicitando o c�lculo desejado.*/

    printf("Opcao: ");
    scanf("%d", &var_controle_1);
    /*coleta qual op��o foi escolhida pelo usu�rio e atribui seu valor � variavel de controle, que ser� utilizada no switch case.*/

    system("cls");
    puts("Carregando...");
    sleep(1); //Est�tica

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
        puts("\n----------------------\n"); //Explica��es ao usu�rio

        var_controle_1 = 0; //Para que o do-while maior comece j� com a condi��o sendo satisfeita


        do{
          i = 0;

          var_controle_2 = 0; //para que o do-while menor comece j� com a condi��o sendo satisfeita

          scanf("%f %c %f", &num[i][0], &sinal[i], &num[i][1]);
          goto Pulinho; //Esse pulinho impede o outro scanf no caso de o usu�rio querer utilizar o resultado anterior

          do{
            i++; //Para salvar em lugares diferentes do array
            printf("%.4f", num[i-1][2]); //Printa o n�mero anterior, que foi solicitado pelo usu�rio
            scanf(" %c %f" , &sinal[i] , &num[i][1] ); //scan do sinal e do n�mero
            num[i][0] = num[i-1][2]; //O primeiro n�mero dessa opera��o � resultado da coluna anterior

            Pulinho:
            switch (sinal[i]){
              case '+': //Caso soma
                system("cls");
                num[i][2] = soma(num[i][0], num[i][1]); //Fun��o soma

                Escolha_Soma: //Label para quando o usu�rio digitar errado
                printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                menu_aritmeticas(); //Fun��o para mostrar o menu
                printf("\nOpcao: ");
                scanf("%d", &var_controle_3 );


            switch(var_controle_3){
              case 1:
                system("cls");
                break;

              case 2:
                limpar_historico(); //Fun��o que limpa o hist�rico das opera��es, a pedido do usu�rio
                var_controle_2 = 1; //Quebra o do-while menor, reseta o contador (e assim o hist�rico) e ele volta para a parte em que h� um scanf de 2 numeros e 1 sinal
                break;

              case 3:
                historico(num,sinal,i); //Mostra o hist�rico de opera��es, a pedido do usu�rio
                goto Escolha_Soma;
                break;

              case 4:
                var_controle_1 = 1; //Quebra o do-while menor
                var_controle_2 = 1;//Quebra o do-while maior e volta para o menu de opera��es aritm�ticas
                volta_menu();
                break;

              default:
                system("cls");
                printf("Digite uma Opcao valida: ");
                goto Escolha_Soma; //Tratamento de erro
                break;
            }
            break;

              case '-': //Caso subtra��o
                system("cls");
                num[i][2] = sub(num[i][0], num[i][1]); //fun��o subtra��o

                Escolha_Sub: //Label para tratamento de erro
                printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                menu_aritmeticas(); //Fun��o para mostrar o menu

                printf("\nOpcao: ");
                scanf("%d",&var_controle_3 );

                switch(var_controle_3){
                  case 1:
                    system("cls");
                    break;

                  case 2:
                    limpar_historico(); //Limpa o hist�rico, a pedidos do usu�rio
                    var_controle_2 = 1;//Quebra o do-while menor, assim resetando o contador, ent�o come�ando as opera��es do zero
                    break;

                  case 3:
                    historico(num,sinal,i); //Mostra o hist�rico, como solicitado ao usu�rio
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
                    goto Escolha_Sub; //Volta para a escolha de op��e, j� que o usu�rio digitou algo inv�lido
                    break;
                }
                break;

                case '*': //Caso multiplica��o
                  system("cls");
                  num[i][2] = mult(num[i][0], num[i][1]); //Fun��o multiplica��o

                  Escolha_Mult: //Label para tratamento de erro
                  printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                  menu_aritmeticas(); //Fun��o para mostrar o menu

                  printf("\nOpcao: ");
                  scanf("%d",&var_controle_3 );

                  switch(var_controle_3){
                    case 1:
                      system("cls");
                      break;

                    case 2:
                      limpar_historico(); //Limpa o hist�rico, a pedidos do usu�rio
                      var_controle_2 = 1; //Quebra o do-while menor, assim resetando o contador, ent�o come�ando as opera��es do zero
                      break;

                    case 3:
                      historico(num,sinal,i);
                      //Mostra o hist�rico, como solicitado ao usu�rio
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
                      goto Escolha_Mult; //Volta para a escolha de op��es, j� que o usu�rio digitou algo inv�lido
                      break;
                  }
                  break;

                case '/':
                  system("cls"); //Caso divis�o
                  num[i][2] = divisao(num[i][0], num[i][1]); //Fun��o Divis�o

                  Escolha_Div: //Label para tratamento de erro
                  printf("%.4f %c %.4f = %.4f\n", num[i][0], sinal[i], num[i][1], num[i][2]);

                  menu_aritmeticas(); //Fun��o para mostrar o menu

                  printf("\nOpcao: ");
                  scanf("%d",&var_controle_3 );

                  switch(var_controle_3){
                    case 1:
                      system("cls");
                      break;

                    case 2:
                      limpar_historico(); //Limpa o hist�rico, a pedidos do usu�rio
                      var_controle_2 = 1; //Quebra o do-while menor, assim resetando o contador, ent�o come�ando as opera��es do zero
                      break;

                    case 3:
                      historico(num,sinal,i);//Mostra o hist�rico, como solicitado ao usu�rio
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
                      goto Escolha_Div; //Volta para a escolha de op��es, j� que o usu�rio digitou algo inv�lido
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
                    limpar_historico(); //Limpa o hist�rico, como solicitado do usu�rio
                    var_controle_2 = 1;//Quebra o do-while menor, para que o contador resete
                    break;

                  case 3:
                    historico(num,sinal,i); //Mostra o hist�rico
                    goto Escolha_Potencia; //Vai para a escolha de op��es quando o hist�rico termina
                    break;

                  case 4:
                    var_controle_1 = 1; //Quebra o do-while maior
                    var_controle_2 = 1; //Quebra o do-while menor
                    volta_menu(); //Fun��o que volta para o menu
                    break;

                  default:
                    system("cls");
                    printf("Digite uma Opcao valida:\n\n");
                    goto Escolha_Potencia; //Vai para a escolha de op��es, tratando o erro do usu�rio
                    break;
                }

                break;


              }

          }while(var_controle_2 == 0); //Declara��o do do-while menor

        }while(var_controle_1 ==  0); //Declara��o do do-while maior

            break;







      case 2 :
        var_controle_2 = 0;//Para que o do-while maior j� comece com a condi��o sendo satisfeita
         //declara��o de vari�veis dos �ndicides da equacao

        int contador_segundo_grau = 0; //contador do hist�rico setado como 0

        identificador_equacao = 2;

        do{
          system("cls");


          puts("-----EQUACAO DE SEGUNDO GRAU-----\n");
          puts("Ax^2 + Bx + C");
          printf("\n%s, digite os indices A, B e C da equacao do segundo grau nessa, ordem:\n", nome);
          scanf("%f %f %f", &resultados_segundo_grau[contador_segundo_grau][0], &resultados_segundo_grau[contador_segundo_grau][1], &resultados_segundo_grau[contador_segundo_grau][2]); //Pega os �ndices da equacao, armazenando sempre nas posi��es 0,1 e 2, respectivamente,  do vetor resultados

          /*
            resultados_segundo_grau[contador_segundo_grau][0] = indice a
            resultados_segundo_grau[contador_segundo_grau][1] = indice b
            resultados_segundo_grau[contador_segundo_grau][0] = indice c
          */


          if(resultados_segundo_grau[contador_segundo_grau][0] == 0) //se o indice a � igual a 0, n�o � uma equacao do segund grau
            puts("\nIndice A = 0, essa nao e uma equacao de segundo grau\n");

          else{
            printf("\n%.2fx^2 + %.2fx + %.2f = 0\n", resultados_segundo_grau[contador_segundo_grau][0], resultados_segundo_grau[contador_segundo_grau][1], resultados_segundo_grau[contador_segundo_grau][2]);
            //print da equacao

            equacao_segundo_grau(resultados_segundo_grau[contador_segundo_grau][0], resultados_segundo_grau[contador_segundo_grau][1], resultados_segundo_grau[contador_segundo_grau][2], &x1, &x2); //Realiza a equacao do segundo grau
            if (x1 == NUM_RAIZ_NAO_REAL){ //Esse � o valor que retorna se a equacao n�o tem ra�zes reais
              resultados_segundo_grau[contador_segundo_grau][3] = x1; //Para ser identificado na hora de printar o hist�rico
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
            if (resultados_segundo_grau[j][3] == NUM_RAIZ_NAO_REAL){ //Se x1 � o valor das ra�zes n�o reais
              printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao ha raizes reais\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que n�o h� ra�zes
            }
            else if (resultados_segundo_grau[j][0] == 0){ //Se a = 0
              printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao eh uma equacao do segundo grau\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que n�o � uma equacao do segundo grau
            }
            else{
              printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f, x2 = %.4f\n\n",j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2], resultados_segundo_grau[j][3], resultados_segundo_grau[j][4]); //Printa devidamente a equa��o do segundo grau e suas ra�zes reais, quando existirem
            }
          }
          */

          puts("\n");
          contador_segundo_grau = menu_equacoes_raiz(identificador_equacao, &var_controle_1, &var_controle_2, contador_segundo_grau, resultados_segundo_grau);
        }while(var_controle_2 == 0);
        break;








      case 3:
      var_controle_4 = 0;//Para que o do-while maior j� comece com a condi��o sendo satisfeita
      float x3;
      int contador_eq_terceiro_grau = 0; //contador do vetor setado como 0
      identificador_equacao = 3;

        do{

          system("cls");

          puts("-----EQUACAO DE TERCEIRO GRAU-----\n");
          puts("Ax^3 + Bx^2 + Cx + D");
          printf("\n%s, digite os indices A, B, C e D da equacao do terceiro grau, nessa ordem:\n", nome);

          scanf("%f %f %f %f", &resultados_terceiro_grau[contador_eq_terceiro_grau][0], &resultados_terceiro_grau[contador_eq_terceiro_grau][1], &resultados_terceiro_grau[contador_eq_terceiro_grau][2], &resultados_terceiro_grau[contador_eq_terceiro_grau][3]); //scanf dos 4 �ndices que ser�o utilizados na equacao


          if(resultados_terceiro_grau[contador_eq_terceiro_grau][0] == 0){ //se o indice a � igual a 0, n�o � uma equacao do terceiro grau
            puts("\nIndice A = 0, essa nao e uma equacao de terceiro grau\n");
          }


          else{
            printf("\n%.2fx^3 + %.2fx^2 + %.2fx + %.2f = 0\n",resultados_terceiro_grau[contador_eq_terceiro_grau][0],resultados_terceiro_grau[contador_eq_terceiro_grau][1], resultados_terceiro_grau[contador_eq_terceiro_grau][2], resultados_terceiro_grau[contador_eq_terceiro_grau][3]);

            equacao_cubica(resultados_terceiro_grau[contador_eq_terceiro_grau][0], resultados_terceiro_grau[contador_eq_terceiro_grau][1], resultados_terceiro_grau[contador_eq_terceiro_grau][2], resultados_terceiro_grau[contador_eq_terceiro_grau][3], &x1, &x2, &x3); //Fun��o da equacao de terceiro grau

            resultados_terceiro_grau[contador_eq_terceiro_grau][4] = x1;
            resultados_terceiro_grau[contador_eq_terceiro_grau][5] = x2;
            resultados_terceiro_grau[contador_eq_terceiro_grau][6] = x3;

            if (x3 == NUM_RAIZ_NAO_REAL){ //Valor para ra�z n�o real
              if (x2 == NUM_RAIZ_NAO_REAL){ //Valor para ra�z n�o real
                printf("Essa eh a raiz da equacao: %f", x1); //se x2 e x3 tem o valor de ra�z n�o real, apenas x1 � raiz real

              }
              else{
                printf("Essas sao as raizes da equacao: %f %f", x1, x2); //se x3 tem o valor de ra�z n�o real, apenas x1 e x2 s�o ra�zes reais
              }
            }
            else{
              printf("Essas sao as raizes da equacao: %f %f %f", x1, x2, x3); //As 3 ra�zes s�o reais
            }
          }


          puts("\n");
          contador_eq_terceiro_grau = menu_equacoes_raiz(identificador_equacao, &var_controle_3, &var_controle_4, contador_eq_terceiro_grau, resultados_terceiro_grau);

        }while(var_controle_4 == 0); //declara��o do do-while utilizado no case
        break;
      break;




      case 4:
        system("cls");
        identificador_equacao = 4;
        int contador_fatorial = 0; //Contador de fatorial setado como 0 para que o vetor do hist�rico inicie em 0
        printf("%s, essa eh a nossa calculadora de fatorial\n\n", nome);
        var_controle_3 = 0; //Para que a vari�vel do do-while j� inicie satisfazendo a condi��o

        do{

          printf("Digite o numero: ");
          scanf("%lld", &resultados_fatorial[contador_fatorial][0]); //Primeira posi��o do array � preenchido com o n�mero digitado
          resultados_fatorial[contador_fatorial][1] = fatorial(resultados_fatorial[contador_fatorial][0]); //Fun��o fatorial, segunda posi��o do array � preenchido com o resultado

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
              contador_fatorial++; //contador incrementado, para que o hist�rico sea propriamente exibido
              break;


            case 2:
              historico_fatorial(contador_fatorial, resultados_fatorial); //utiliza��o da fun��o de hist�rico de fatorial
              goto escolha_de_opcoes_fatorial; //Vai para as op��es

              break;

            case 3:
              volta_menu();
              var_controle_3 = 1; //Quebra o do-while

              break;

            default:
              system("cls");
              puts("Digite uma opcao valida ");
              goto escolha_de_opcoes_fatorial; //Vai para o come�o de escolhas, como tratamento de erro
              break;
          }

        }while(var_controle_3 == 0);
      break;

      case 5:
        identificador_equacao = 5;
        var_controle_4 = 0; //var setada em 0 para que a condi��o do do-while j� seja satisfeita de in�cio
        int contador_raiz_quadrada = 0; //contador definido como 0 par que o array comece sendo preenchido em 0

        system("cls");
        printf("%s, essa eh a nossa calculadora de raizes quadradas.\nTal operacao pode ser feita dentro das operacoes aritmeticas,elevando um numero a 0.5,\nmas preferimos tambem colocar uma opcao no menu para que o usuario possa fazer tal operacao\n\n", nome);

        do{
          if (contador_raiz_quadrada != 0){
                system("cls");
          }

          var_controle_3 = 0;//var setada em 0 para que a condi��o do do-while j� seja satisfeita de in�cio
          printf("Digite o numero: ");
          scanf("%f", &resultados_raiz_quadrada[contador_raiz_quadrada][0]); //scanf do n�mero que ser� calculada a raiz quadrada

          resultados_raiz_quadrada[contador_raiz_quadrada][1] = raiz_quadrada(resultados_raiz_quadrada[contador_raiz_quadrada][0]); //O resultado ocupa a segunda posi��o do vetor

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

    /*utiliza��o do switch case para as diferentes op��es apresentadas, alternando o comando de acordo com cada escolha*/

    }
  }while(controle_menu == 0);

  return 0;
}

void corretor_de_enter(char nome[]){
  int tam;
  tam = strlen(nome);

    if (nome[tam - 1] == '\n'){ //Se o pen�ltimo char for um \n
      nome[tam - 1] = '\0'; //Transform�-lo em \0 (finalizador)
    }
}


float raiz_quadrada(float numero){
  float auxiliar, raiz_quadrada;
  //M�todo babil�nico, a base desse m�todo � encontrar um quadrado de lados que sejam a ra�z do n�mero pretendido a partir da diminui��o progressiva da base e do aumento progressivo da altura, at� que os dois se igualem

  //Pense que o n�mero 101 foi entrado pelo
  raiz_quadrada = numero / 2; //50.5
  auxiliar = 0;

  while(raiz_quadrada != auxiliar){
    auxiliar = raiz_quadrada; //50.5 //Na segunda rodada: 26.25
    raiz_quadrada = (numero/auxiliar + auxiliar) / 2;
  } // ((101/50.5) + 50.5)/2 = 26.25 //Na segunda rodada: ((101/26.25) + 26.25)/2 = 15.048809 e assim vai, at� auxiliar e raiz quadrada forem iguais, que nesse caso � quando forem 10.049875, que � a raiz de 101

  return raiz_quadrada;
}

void equacao_segundo_grau(float a, float b, float c, float *x1, float *x2){
  float delta;

  delta = b*b - 4*a*c; //C�lculo do delta

  if (delta < 0){
    *x1 = NUM_RAIZ_NAO_REAL; //Indica que n�o h� ra�zes reais
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
      if ( (expoente != expoente_exato)/*testa de o expoente � n�o exato*/ && (aux == aux_exata)/* testa se o expoente multiplicado por dois se torna exato*/ ){
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
    Divide todos �ndices por A
  */
  A = b/a;
  B = c/a;
  C = d/a;


  float p, q;
  p = B - ((A*A)/3);
  q = C + ((2*A*A*A)/27) - ((A*B)/3);

  /* p e q ser�o vari�veis importantes daqui pra l�, ent�o, set�-las foi necess�rio*/

  //x = y - A/3. Houve uma mudan�a de vari�vel, agora � uma fun��o y^3 + y^2 + y + z = 0

  float delta;
  delta = ((q*q)/4) + ((p*p*p)/27); //delta_1. Se ele for maior ou igual a 0, 2 deltas s�o usados

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
        *x3 = NUM_RAIZ_NAO_REAL; //Ra�z n�o real


      }
      else{
        y2 = -y1 + raiz_quadrada(delta_2)/2;
        y3 = -y1 - raiz_quadrada(delta_2)/2;
        *x1 = y1 - A/3;
        *x2 = y2 - A/3;
        *x3 = y3 - A/3; //Todas ra�zes reais

      }
    }
    else {
      *x1 = y1 - A/3;
      *x2 = NUM_RAIZ_NAO_REAL;
      *x3 = NUM_RAIZ_NAO_REAL; //Duas ra�zes n�o reai
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
      *x3 = y3 - A/3; //Todas ra�zes reais
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
  puts("4. Voltar ao menu"); //Est�tica

}

void historico(float n[MAX][3], char sinal[], int i ){

  system("cls");

  puts("----------Historico----------\n");

  for(int j = 0; j <= i; j++) /*uso do la�o de repeti��o for para repetir os comandos de acordo com o valor da vari�vel i (que ser� definida de acordo com a quantidade de opera��es realizadas pelo usu�rio)*/
    printf("%d: %.4f %c %.4f = %.4f\n\n", j+1, n[j][0], sinal[j], n[j][1], n[j][2]); //Exibi��o do hist�rico

  puts("-----------------------------\n");

  system("pause");

  system("cls");
}

void limpar_historico(){
  system("cls");

  puts("Limpando Historico...");
  sleep(1);           //Est�tica
  system("cls");


}

void volta_menu(){
  system("cls");
  puts("Voltando ao menu...");
  sleep(1);           //Est�tica
  system("cls");
}

void historico_eq_segundo_grau(int i, float *resultados_segundo_grau[MAX]){
  system("cls");
  for (int i = 0; i < MAX; i++){
    resultados_segundo_grau[i] = (float*)malloc(5*sizeof(float));
  }

  puts("----------Historico----------\n");

  for (int j = 0; j <= i; j++){
    if (resultados_segundo_grau[j][3] == NUM_RAIZ_NAO_REAL){ //Se x1 � o valor das ra�zes n�o reais
      printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao ha raizes reais\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que n�o h� ra�zes
    }
    else if (resultados_segundo_grau[j][0] == 0){ //Se a = 0
      printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> Nao eh uma equacao do segundo grau\n\n", j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2]); //Printa que n�o � uma equacao do segundo grau
    }
    else{
      printf(" %d: %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f, x2 = %.4f\n\n",j+1, resultados_segundo_grau[j][0], resultados_segundo_grau[j][1], resultados_segundo_grau[j][2], resultados_segundo_grau[j][3], resultados_segundo_grau[j][4]); //Printa devidamente a equa��o do segundo grau e suas ra�zes reais, quando existirem
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
        printf(" %d: %.4fx^3 + %.4fx^2 + %.4fx + %.4f = 0 ==> Nao eh uma equacao do terceiro grau\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3]); //Printa a �nica ra�z real
      }
    else if (resultados_terceiro_grau[j][6] == NUM_RAIZ_NAO_REAL){ //Se x2 � uma ra�z n�o real
      if (resultados_terceiro_grau[j][5] == NUM_RAIZ_NAO_REAL){ //Se x2 e x3 n�o s�o ra�zes reais
        printf(" %d: %.4fx^3 + %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3], resultados_terceiro_grau[j][4]); //Printa a �nica ra�z real
      }
      else { //Se x1 e x3 s�o ra�zes reais
        printf(" %d: %.4fx^3 + %.4fx^2 + %.4fx + %.4f = 0 ==> x1 = %.4f, x2 = %.4f\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3], resultados_terceiro_grau[j][4], resultados_terceiro_grau[j][5]); //Printa as duas ra�zes reais
      }
    }
    else{ //Se as 3 ra�zes s�o reais
      printf(" %d: %.4fx^3 + %f.4x^2 + %.4fx + %f = 0 ==> x1 = %.4f, x2 = %.4f, x3 = %.4f\n\n", j+1, resultados_terceiro_grau[j][0], resultados_terceiro_grau[j][1],resultados_terceiro_grau[j][2], resultados_terceiro_grau[j][3], resultados_terceiro_grau[j][4], resultados_terceiro_grau[j][5], resultados_terceiro_grau[j][6]); //Printa as 3 ra�zes reais
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
  } //Printa o hist�rico de fatorial

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
    printf("%d: raiz quadrada de %.4f = %.4f\n\n", j+1, resultados_raiz_quadrada[j][0], resultados_raiz_quadrada[j][1]); //Printa o hist�rico de raiz quadrada
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
        historico_eq_segundo_grau(contador, vetor_equacao); //fun��o que printa o historico da equacao do segundo grau
      }
      else if(equacao == 3){
        historico_eq_terceiro_grau(contador, vetor_equacao); //fun��o que printa o historico da equacao do segundo grau
      }
      else if(equacao == 5){
         historico_raiz_quadrada(contador, vetor_equacao); //fun��o que printa o historico da equacao do segundo grau
      }

      goto Escolha_de_opcoes;
      break;

    case 3:
      *quebra_menu = 1;
      volta_menu(); //Utiliza��o da fun��o criada para o retorno ao Menu do programa
      break;


    default:
      system("cls");
      sleep(1); //Espera um segundo antes de mostrar as pr�ximas sa�das
      puts("Opcao Invalida!\n");
      puts("Escolha uma opcao valida:\n");
      goto Escolha_de_opcoes; //Vai para o in�cio das escolhas, tratando o erro do usu�rio
      break;
  }
}
