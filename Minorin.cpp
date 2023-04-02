#include <bits/stdc++.h>

using namespace std;

void chatbot(int mensagem)
{
    ifstream texto;
    string linha;

    texto.open("dados.txt");
    
    if (texto.is_open()) {

        while (getline(texto, linha)) {
            continue;
        }
    }

    texto.close();

    // texto e o texto do usúario e mensagem e uma das 3 mensagens possiveis para cada resposta

    // vamos quebrar a fase em varias partes por um espaço
    vector<string> partes_frase;
    string nova = "";
    int tamanho = linha.length();

    for (int i = 0; i < tamanho; i++) {
        if (linha[i] != ' ') {
            nova += linha[i];

        } else {
            partes_frase.push_back(nova);
            nova = "";
        }
    }

    partes_frase.push_back(nova);
    nova = "";

    // procurando palavras chaves no vector

    map<string, int> palavras;
    palavras["ola"] = 1;
    palavras["tchau"] = 2;
    palavras["sair"] = 2;
    palavras["conta"] = 3;
    palavras["total"] = 3;

    int id_mensagem = 0;
    // resposta do chatbot
    vector<string> resposta;

    tamanho = partes_frase.size();

    // caso o computador veja que a frase e um pedido ele vai anotar ser não ele vai tentar responde apartir de palavras chaves
    // mensagem e o codigo da mensagem que o usúario vai receber

    if (find(partes_frase.begin(), partes_frase.end(), "pedido") != partes_frase.end() or find(partes_frase.begin(), partes_frase.end(), "pedir") != partes_frase.end() or find(partes_frase.begin(), partes_frase.end(), "pizza") != partes_frase.end() or find(partes_frase.begin(), partes_frase.end(), "refrigerante") != partes_frase.end() or find(partes_frase.begin(), partes_frase.end(), "coca") != partes_frase.end()) {
        // variavel pedido va anota o pedido
        // a variavel pas vai indica ser já passou das palavras do pedido
        string pedido = "";
        bool pas = false;

        for (int i = 0; i < partes_frase.size(); i++) {
            if (partes_frase[i] == "uma" and pas == false) {
                pedido += partes_frase[i];
                pas = true;
            
            } else if (partes_frase[i] == "pedido" and pas == false or partes_frase[i] == "pedir" and pas == false) {
                pas = true;

            } else if (partes_frase[i] == "refrigerante" and pas == false or partes_frase[i] == "refrigerantes" and pas == false or partes_frase[i] == "pizza" and pas == false or partes_frase[i] == "pizzas" and pas == false or partes_frase[i] == "coca" and pas == false or partes_frase[i] == "cocas" and pas == false ) {
                pedido += partes_frase[i - 1] + " " + partes_frase[i];
                pas = true;

            } else if (pas == true) {
                pedido += " " + partes_frase[i];

            }
        }

        // resposta

        switch (mensagem) {
            case 0:
                resposta.push_back("Seu pedido foi anotado");
                break;

            case 1:
                resposta.push_back("Um otimo pedido senho ja vai sair");
                break;
            
            case 2:
                resposta.push_back("O perdido " + pedido + " foi anotado, volte sempre");
                break;
        }

        // vamos sava o pedido

        ofstream pedido_ano;
        pedido_ano.open("pedidos.txt");
        pedido_ano << pedido;
        pedido_ano.close();
    
    } else if (find(partes_frase.begin(), partes_frase.end(), "cardapio") != partes_frase.end()) {
        // cardapio
        switch (mensagem) {
            case 0:
                resposta.push_back("Claro, hoje temos pizza por 10R$ refrigerante por 2R$ coca por 5R$.");
                break;
                        
            case 1:
                resposta.push_back("pizza por 10R$ refrigerante por 2R$ e coca por 5R$.");
                break;

            case 2:
                resposta.push_back("pizza 10R$, refrigerante 2R$, coca 5R$.");
                break;

            }


    } else {

        for (int i = 0; i < tamanho; i++) {
            id_mensagem = palavras[partes_frase[i]];

            switch (id_mensagem) {
                // chave ola == 1
                case 1:
                    switch (mensagem) {
                        case 0:
                            resposta.push_back("Ola, oque voce vai perdir hoje ?.");
                            break;
                        
                        case 1:
                            resposta.push_back("Ola o que voce gostaria de pedir hoje.");
                            break;

                        case 2:
                            resposta.push_back("Ola sou a Minorin e estou aqui para ter ajuda !.");
                            break;

                    }

                    break;

                // chave tchau e sair == 3
                case 2:
                    switch (mensagem) {
                        case 0:
                            resposta.push_back("Obrigador pela preferencia, volte sempre.");
                            break;
                        
                        case 1:
                            resposta.push_back("Ate mais espero ver voce novamente outro dia.");
                            break;

                        case 2:
                            resposta.push_back("Volte sempre.");
                            break;

                    }
                    
                    break;
                
                // chave conta e total == 4
                case 3:
                    switch (mensagem) {
                        case 0:
                            resposta.push_back("Ainda nao sei fazer contas, porfavor procure uma pessoa.");
                            break;
                        
                        case 1:
                            resposta.push_back("Para obter o valor a pagar procure um dos nossos funcionarios.");
                            break;

                        case 2:
                            resposta.push_back("infelizmente nao sei fazer conta, procure um funcionario.");
                            break;

                    }
                    
                    break;

            }

            if (i == partes_frase.size() - 1 and resposta.size() == 0) {
                switch (mensagem)
                {
                case 0:
                    resposta.push_back("Desculpe nao consigo entede");
                    break;

                case 1:
                    resposta.push_back("Poderia me explicar melhor o que voce deseja ?");
                    break;

                case 2:
                    resposta.push_back("Poderia me falar seu pedido ?");
                    break;
                }
            }

        }
    }


    // return resposta[0];

    ofstream texto1;

    texto1.open("dados.txt");

    texto1 << resposta[0];

    texto1.close();
}