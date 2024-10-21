#include <stdio.h>
#include <math.h>

float CalcularSigma(double r, double c) {
    return 1 / (2 * r * c);
}

float CalcularOmegaAoQuadrado(double l, double c) {
    return 1 / (l * c);
}

void CalcularSistema(double a1, double b1, double c1, double a2, double b2, double c2, double* x, double* y) {
    double D, Dx, Dy;

    D = a1 * b2 - a2 * b1;     // determinante matriz dos coeficientes
    Dx = c1 * b2 - c2 * b1;    // determinante x
    Dy = a1 * c2 - a2 * c1;    // determinante  y

    // valores dos determinantes 
    //printf("Determinante D = %.10f\n", D);
    //printf("Determinante Dx = %.10f\n", Dx);
   // printf("Determinante Dy = %.10f\n", Dy);

    // Verificar se o sistema tem solução (D != 0)
    if (fabs(D) > 1e-10) { // Usando uma tolerância para evitar problemas com precisão
        // Calculando x e y
        *x = Dx / D;
        *y = Dy / D;

      //  printf("A solução é: x = %.10f, y = %.10f\n", *x, *y);
    } else {
        // Sistema sem solução única
        if (fabs(Dx) < 1e-10 && fabs(Dy) < 1e-10) {
            printf("O sistema tem infinitas soluções (as equações são dependentes).\n");
        } else {
            printf("O sistema não tem solução (as equações são inconsistentes).\n");
        }
    }
}

int main() {
    double sigma, omega;
    double sigmaaoquadrado, omegaquadrado;
    int expoentec, expoenter, expoentel;
    double capacitancia, indutancia, resistencia;
    double correntei, tensaoi;
    int expoenteci, expoenteil;
    double a1, a2; 
    double d1=0, d2;
    double b1=0, b2;
    double s1, s2;
    double ir0, ic0;
    double tm=0;
    double vtm=0;

    printf("\n==============================CALCULADORA DE CIRCUITOS RLC EM PARARELO==============================\n");

    printf("\nAutores: Helena Souto e Matheus Morais\n");

    printf("\n-----------------VALORES DOS COMPONENTES-----------------\n");

    printf("Digite o valor da capacitancia: ");
    scanf("%lf", &capacitancia);
    printf("Informe o expoente da unidade na base 10: ");
    scanf("%d", &expoentec);
    printf("Digite o valor da resistencia: ");
    scanf("%lf", &resistencia);
    printf("Informe o expoente da unidade na base 10: ");
    scanf("%d", &expoenter);
    printf("Digite o valor da indutancia: ");
    scanf("%lf", &indutancia);
    printf("Informe o expoente da unidade na base 10:");
    scanf("%d", &expoentel);
    printf("\n");

    printf("-----------------VALORES INICIAIS DOS COMPONENTES-----------------\n");
    printf("Digite a tensao inicial no capacitor: ");
    scanf("%lf", &tensaoi);
    printf("Informe o expoente da unidade na base 10: ");
    scanf("%d", &expoenteci);
    printf("Digite a corrente inicial no indutor: ");
    scanf("%lf", &correntei);
    printf("Informe o expoente da unidade na base 10:");
    scanf("%d", &expoenteil);
    printf("\n");

    float fatorC = pow(10, expoentec);
    float fatorR = pow(10, expoenter);
    float fatorL = pow(10, expoentel);
    float fatorI = pow(10, expoenteil);

    //para encontrar sigma e omega
    sigma = CalcularSigma(resistencia * fatorR, capacitancia * fatorC);
    omegaquadrado = CalcularOmegaAoQuadrado(indutancia * fatorL, capacitancia * fatorC);

    sigmaaoquadrado = sigma * sigma;
    omega = sqrt(omegaquadrado);

    printf("Sigma: %.0f\n", sigma);
    printf("Sigma ao quadrado: %.0f\n", sigmaaoquadrado);
    printf("omega: %.0f\n", omega);
    printf("omega ao quadrado: %.0f\n", omegaquadrado);

    //para descobrir o tipo de circuito 

    double discriminante = sigmaaoquadrado - omegaquadrado;

     if (discriminante > 0) {

        printf("Tipo: Circuito superamortecido\n");

        s1 = -sigma + sqrt(discriminante);
        s2 = -sigma - sqrt(discriminante);
        
        
        printf("s1 = %.0f , s2 = %.0f\n", s1, s2);

        // lógica para descobrir a1 e a2
        ir0 = tensaoi / (resistencia*fatorR); // Corrente inicial no resistor
        ic0 = -ir0 - (correntei*fatorI); // Corrente inicial no capacitor
       // printf("ir0: %.10f, ic0: %.10f\n", ir0, ic0);

        // Resolver o sistema de equações:
        CalcularSistema(1, 1, tensaoi, (s1*(capacitancia*fatorC)), (s2*(capacitancia*fatorC)), ic0, &a1, &a2);

        
        printf("a1 (calculado): %.2f, a2 (calculado): %.2f\n", a1, a2);
       // printf("tensaoi: %.2f, s1: %.2f, s2: %.2f\n", tensaoi, s1, s2);

        printf("V(t)= %.2lf e^(%.0lf)t + %2.lf e^(%.0lf)t (V)\n", a1, s1, a2, s2);

        double modulos1 = fabs(s1);
        double modulos2 = fabs(s2);
        double moduloa1 = fabs(a1);
        double moduloa2 = fabs(a2);

        if (fabs(s2 - s1) > 1e-10) {

        tm = (1 / ((modulos2-modulos1)) * log((moduloa2*modulos2)/(moduloa1*modulos1)));
        printf("tm = %.10lf\n (s)",tm);

        //testes para verificar todos os valores na formula de tm:

        /* double subtm = modulos2 - modulos1;
        printf("s2-s1= %.2lf\n", subtm);
        double quociente1tm = 1 / subtm;
        printf("1/s2-s1= %.10lf\n", quociente1tm);
        double produto1tm = moduloa2*modulos2;
        printf("a2*s2=%.2lf\n", produto1tm);
        double produto2tm = moduloa1*modulos1;
        printf("a1*s1=%.2lf\n", produto2tm);
        double quociente2tm = produto1tm/ produto2tm;
        printf("(a2*s2)/(a1*s1)=%.2lf\n",quociente2tm);
        double lntm = log(quociente2tm);
        printf("log((a2*s2)/(a1*s1))=%.10lf\n", lntm);*/
        
        double exponente1m = s1 * tm;
        double exponente2m = s2 * tm;
        double exponencial1 = exp(exponente1m); 
        double exponencial2 = exp(exponente2m); 

        vtm = a1 * exponencial1 + a2 * exponencial2;
        printf("vtm = %.10lf(V)", vtm);
        } else{
            printf("Erro: s2 - s1 é zero ou próximo de zero, não é possível calcular tm.\n");
        }
    } else if (discriminante == 0) {

        printf("Tipo: Circuito criticamente amortecido\n");
        ir0 = tensaoi / (resistencia*fatorR); // Corrente inicial no resistor
        ic0 = -ir0 - (correntei*fatorI); // Corrente inicial no capacitor
       // printf("ir0: %.10f, ic0: %.10f\n", ir0, ic0);

        // descobrir d1 e d2 
        d2 = tensaoi;
        d1 = (ic0 + (sigma *tensaoi * capacitancia *fatorC))/(capacitancia*fatorC);

        printf("d1: %.2lf, d2: %.2lf\n", d1, d2);

        double modulosigma = fabs(sigma);
        double s = -sigma;

        printf("v(t)= (%.2lft + %.2lf) e ^ (%.2lft) (V)\n", d1, d2, s);

        tm = 1 / modulosigma;
        printf("tm = %.10lf(s)\n", tm);
        double expoentetm = (s * tm);
        double exponencial = exp(expoentetm);
        double mult = d1 *tm;

        vtm = ((d1*tm + d2) * exponencial);
        printf("vtm = %.10lf(V)\n", vtm);

        

    } else {
        printf("Tipo: Circuito subamortecido\n");

        double wd = sqrt(omegaquadrado - sigmaaoquadrado);
        printf("wd: %.2f\n", wd);
        ir0 = tensaoi / (resistencia*fatorR); // Corrente inicial no resistor
        ic0 = -ir0 - (correntei*fatorI); // Corrente inicial no capacitor
        //printf("ir0: %.10f, ic0: %.10f\n", ir0, ic0);

        b1 = tensaoi;
        double dvodt = ic0 / (capacitancia*fatorC);

        b2 = (dvodt + (sigma*tensaoi)) / wd;
        double s = -sigma;

        printf("b1: %.2lf, b2: %.2lf\n", b1,b2);
        
        printf("v(t)= [%.2lfcos(%.2lft)%.2lfsen(%.2lft)] e ^ (%.2lft) (V)\n", b1, wd, b2, wd, s);

        double arctan = atan(b2/b1);

        tm = fabs((1 / wd) * arctan);
        printf("tm = %.10lf (s)\n ", tm);
        double exponentem = s * tm;
        double exponencial = exp(exponentem); 
        vtm = ((b1 * cos(wd *tm) + b2 * sin(wd*tm))* exponencial);
        printf("vtm = %.10lf\n (V)", vtm);
    }

    return 0;
}
