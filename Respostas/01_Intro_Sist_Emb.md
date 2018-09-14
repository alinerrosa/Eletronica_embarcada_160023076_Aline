1)O que são sistemas embarcados?

R: Sistemas completos, independentes e reprogramáveis que que são encarregados de executar determinada função pré-determinada com requisitos específicos.

2)O que são sistemas microprocesssados?

R: Microprocessadores são circuitos integrados com um microprocessador (CPU), memória não-volátil (ROM), memória volátil (RAM), periféricos de entrada e saída e , no mínimo, um circuito de clock. Diferentemente dos microcontroladores, eles são mais usados para aumentar o poder computacional de alguma máquina.

3)Apresente aplicações de sistemas embarcados: (a) para a indústria automotiva; (b) para eletrodomésticos; (c) para automação industrial.

R:
a) Os carros modernos possuem diversos sistemas embarcados para, por exemplo, controle da bomba de gasolina.
b) Eletrodomésticos como geladeieras, máquinas de lavar e microondas possuem sistemas embarcados em seus painéis.
c) Sistemas embarcados são muito úteis para a automação industrial, já que são circuitos reprogramáveis, para linhas de montagem.

4)Cite arquiteturas possíveis e as diferenças entre elas.

R:
Harvard e von Neumann. 
Harvard tem a memória volátil e não-volátil separadas com seus própios endereços e barramento de dados. A principal vantagem é a eficiência já que a separação permite que a leitura (não volátil) e a operação (dados vindos da volátil) sejam executadas ao mesmo tempo. Um problema desta arquitetura é que os dados constantes (ex:tabela de consultas) devem ser armazenados na memória do programa porque é não-volátil.

von Neumann possui apenas um sistema de memória, ou seja, apenas um conjunto de endereços abrange as memórias voláteis e não-voláteis. É menos eficiente ja que vários ciclos de memória podem ser necessários para extrair uma instrução completa da memória. Contudo, é um sistema mais simples e não há diferença no acesso a variáveis constantes e variáveis dados.

5)Por que usamos o MSP430 na disciplina, ao invés de outro microcontrolador?

R:
Porque ela possui uma arquitetura von Neumann que é mais simples no acesso à memória, já que há apenas um sitema de memória, apesar de não ser tão eficiente. 
