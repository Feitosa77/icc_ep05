#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

double styblinski(double *x, int order)
{
    double aux, sum = 0.0;

    for (int i = 0; i < order; ++i) 
    {
        aux  = x[i];
        sum += 5*aux;   /* + 5x_i */
        aux *= aux;
        sum -= 16*aux;  /* - 16x^2_i */
        sum += aux*aux; /* + x^4_i */
    }

    return sum/2;
}


// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double styblinskiTang(double a, double b, int namostras, int d)
{
  double resultado;
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = 2\n", a, b, namostras);
  
  double t_inicial = timestamp();
  
  /* AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL PELO MÉTODO DE MONTE CARLO */
  
  double x[d];

  for (int j = 0; j < namostras; ++j)
  {
    for (int i = 0; i < d; ++i) 
      x[i] = a + ((double) random()/RAND_MAX)*(b-a); /* Intervalo Aleatorio */

    soma += styblinski(&x, d); 
  }

  resultado = (soma/namostras)*(b-a);
    
  /* */
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


double retangulos_xy(double a, double b, int npontos) {

  double h = (b-a)/npontos;
  double resultado;
  double soma = 0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);
  
  double t_inicial = timestamp();
  
  /* AQUI IMPLEMENTE O CÁLCULO DA INTEGRAL PELO MÉTODO DOS RETÂNGULOS */

  double x[2], aux;

  for (int i = 0; i < npontos; ++i)
  {
    x[0] = (a+h*i);
    for (int j = 0; j < npontos; ++j)
    {
      x[1] = (a+h*j);
      soma += styblinski(&x, 2);
    }
  }

  resultado = soma * h * h;
    
  /* */
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}


int main(int argc, char **argv) {

  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int n_amostras = atoi(argv[3]);
  int n_variaveis = atoi(argv[4]);

  // INICIAR VALOR DA SEMENTE
  srandom(20232);
    
  // CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
  printf("Resultado: %lf\n\n", styblinskiTang(a, b, n_amostras, n_variaveis));
  printf("Resultado: %lf\n\n", retangulos_xy(a, b, n_amostras));
  
  return 0;
}

