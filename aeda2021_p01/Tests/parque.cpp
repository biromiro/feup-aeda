#include "parque.h"
#include <vector>
#include <string>
#include <algorithm>

unsigned ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}


int ParqueEstacionamento::posicaoCliente(const std::string &nome) const {
    std::vector<InfoCartao>::const_iterator it1, it2;
    it1 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, true));
    it2 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, false));
    if(it1 == clientes.end() && it2 == clientes.end())
        return -1;
    else if(it2 == clientes.end())
        return std::distance<std::vector<InfoCartao>::const_iterator>(clientes.begin(),it1);
    else
        return std::distance<std::vector<InfoCartao>::const_iterator>(clientes.begin(),it2);
}

bool ParqueEstacionamento::adicionaCliente(const std::string &nome) {
    if(clientes.size() == numMaximoClientes)
        return false;
    else {
        clientes.emplace_back(InfoCartao(nome, false));
        return true;
    }
}


bool ParqueEstacionamento::entrar(const std::string &nome) {
    if(vagas == 0)
        return false;
    else {
        std::vector<InfoCartao>::const_iterator it1, it2;
        it1 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, true));
        it2 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, false));
        if((it1 == clientes.end() && it2 == clientes.end()) || it1 != clientes.end())
            return false;
        else{
            int index = std::distance<std::vector<InfoCartao>::const_iterator>(clientes.begin(),it2);
            clientes.at(index).presente = true;
            vagas--;
            return true;
        }
    }
}

bool ParqueEstacionamento::retiraCliente(const std::string &nome) {
    std::vector<InfoCartao>::const_iterator it1, it2;
    it1 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, true));
    it2 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, false));
    if((it1 == clientes.end() && it2 == clientes.end()) || it1 != clientes.end())
        return false;
    else{
        clientes.erase(it2+1);
        return true;
    }
}

bool ParqueEstacionamento::sair(const std::string &nome) {

    std::vector<InfoCartao>::const_iterator it1, it2;
    it1 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, true));
    it2 = std::find(clientes.begin(), clientes.end(),InfoCartao(nome, false));
    if((it1 == clientes.end() && it2 == clientes.end()) || it2 != clientes.end())
        return false;
    else {
        int index = std::distance<std::vector<InfoCartao>::const_iterator>(clientes.begin(), it1);
        clientes.at(index).presente = false;
        vagas++;
        return true;
    }
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const {
    return std::count_if(clientes.begin(),clientes.end(), [](const InfoCartao &x){return x.presente;});
}

unsigned ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}

