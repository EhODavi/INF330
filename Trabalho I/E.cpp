#include <iostream>

using namespace std;

int main() {
    // Criando n (representa a quantidade de funcionários da empresa)
    // contador (representa em qual nível de hierarquia que um funcionário da empresa está)
    // maiorQtdNiveis (representa qual setor da empresa possui o maior nível de hierarquia)
    // pai (representa qual é o gerente de um dado funcionário)
    int n, contador, maiorQtdNiveis = 1, pai;

    cin >> n;

    // Criando pais (representa todos os gerentes de todos os funcionários)
    int pais[n + 1];

    for(int i = 1; i <= n; i++) {
        cin >> pais[i];
    }

    // Verificando qual setor da empresa possui o maior nível de hierarquia
    for(int i = 1; i <= n; i++) {
        // Inicialmente supomos que o funcionário i está no nível 1 da hierarquia da empresa
        contador = 1;

        pai = pais[i];

        // A partir do funcionário i, vai andando até chegar no maior chefe de todos do seu setor
        while(pai != -1) {
            contador++;
            pai = pais[pai];
        }
        
        // Se o funcionário i estiver em um nível de hierarquia maior do
        // que um já calculado, o maior nível de hierarquia da empresa
        // passa a ser igual a desse funcionário
        if(contador > maiorQtdNiveis) maiorQtdNiveis = contador;
    }

    cout << maiorQtdNiveis << "\n";
    
    return 0;
}