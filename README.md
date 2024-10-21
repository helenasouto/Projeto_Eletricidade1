# Projeto_Eletricidade1

# Calculadora de Circuitos RLC em Paralelo

Este projeto é uma calculadora para analisar circuitos RLC em paralelo, determinando o tipo de amortecimento (superamortecido, criticamente amortecido, ou subamortecido) e calculando o valor de `tm` e `vtm`. O programa foi implementado em C, utilizando conceitos de equações diferenciais para análise dos circuitos.

## Autores
- Helena Souto
- Matheus Morais

## Funcionalidades

O programa realiza os seguintes cálculos:
1. **Cálculo de Sigma**: Determina a constante de amortecimento.
2. **Cálculo de Omega**: Calcula a frequência natural do sistema.
3. **Determinação do tipo de circuito**: Identifica se o circuito é superamortecido, criticamente amortecido, ou subamortecido.
4. **Resolução de sistema de equações**: Resolve sistemas de equações para encontrar os coeficientes das soluções no caso de circuitos superamortecidos e criticamente amortecidos.
5. **Cálculo de `tm` e `vtm`**: Calcula o tempo de máximo e a tensão nesse ponto para cada tipo de circuito.

## Como usar

### Entrada:
- O usuário deve fornecer os valores de capacitância, resistência, indutância e as condições iniciais (tensão no capacitor e corrente no indutor).
- Também é necessário fornecer os expoentes das unidades para que os valores possam ser ajustados corretamente.

### Exemplo de uso:
Ao rodar o programa, ele solicitará as seguintes entradas:
- Capacitância (em Farads) e seu expoente.
- Resistência (em Ohms) e seu expoente.
- Indutância (em Henrys) e seu expoente.
- Tensão inicial no capacitor (em Volts) e seu expoente.
- Corrente inicial no indutor (em Amperes) e seu expoente.

O programa então calculará os valores necessários e exibirá o tipo de circuito, as soluções para a tensão no tempo `t`, o valor de `tm` (tempo no qual a tensão máxima ocorre), e o valor de `vtm` (tensão no tempo `tm`).

### Exemplo de saída:
==============================CALCULADORA DE CIRCUITOS RLC EM PARARELO==============================

Autores: Helena Souto e Matheus Morais

Digite o valor da capacitancia: 0.0001 
Informe o expoente da unidade na base 10: -6 
Digite o valor da resistencia: 100 
Informe o expoente da unidade na base 10: 0 
Digite o valor da indutancia: 0.1 
Informe o expoente da unidade na base 10: -3

Tipo: Circuito subamortecido 
wd: 3000.00 
v(t)= [125.00cos(3000.00t) - 250.00sen(3000.00t)] e ^ (-4000.00t) (V) 
tm = 0.0003690496 (s) 
vtm = -38.3214144256 (V)


## Compilação e Execução

1. Para compilar o programa, utilize um compilador C, como `gcc`:
    ```
    gcc calculadora_rlc.c -o calculadora_rlc -lm
    ```

2. Para executar o programa:
    ```
    ./calculadora_rlc
    ```

## Dependências

- O programa requer a biblioteca matemática `math.h` para realizar cálculos com funções como `sqrt`, `exp`, e `log`.

## Observações

Este projeto foi desenvolvido como parte de um estudo sobre circuitos RLC em paralelo na disciplina de ELETRICIDADE E CIRCUITOS PARA COMPUTAÇÃO I 

