
#include "Cooperativa.h"

//TODO: Implementar corretamente o construtor e inicializacao da BST!
Cooperativa::Cooperativa(): vinhos(Vinho("",0))
{}

bool Vinho::operator<(const Vinho& v1) const {
    if(ano > v1.ano) return true;
    else if(ano < v1.ano) return false;
    return nome < v1.nome;
}

bool Vinho::operator==(const Vinho& v1) const {
    return ano == v1.ano && nome == v1.nome;
}

bool Vinicola::operator<(const Vinicola& v1) const {
    if(vinhos > v1.vinhos) return true;
    else if(vinhos < v1.vinhos) return false;
    return nome > v1.nome;
}

bool Vinicola::operator==(const Vinicola& v1) const {
    return nome == v1.nome && vinhos == v1.vinhos;
}


bool Enologo::operator<(const Enologo& e1) const {
    int count1 = 0, count2 = 0;
    for(const auto& elem: vinicolas){
        count1 += elem.getVinhos();
    }
    for(const auto& elem: e1.vinicolas){
        count2 += elem.getVinhos();
    }
    return count1 < count2;
}

bool Enologo::operator==(const Enologo& e1) const {
    return nome == e1.nome;
}






void Cooperativa::addVinhos(const vector<Vinho>& vv) {
    for(const auto& elem: vv){
        vinhos.insert(elem);
    }
}

list<string> Cooperativa::vinhosDisponiveis(int ano1, int ano2) {
    list<string> a;
    for(BSTItrIn<Vinho> bItr(vinhos); !bItr.isAtEnd(); bItr.advance()){
        Vinho v = bItr.retrieve();
        if(v.getAno() >= ano1 && v.getAno() <= ano2) a.push_front(v.getNome() + " " + to_string(v.getAno()));
    }
    a.sort([](const string& vinho1, const string& vinho2){return vinho1 > vinho2;});
    if(a.size() == 0) a.push_front("Indisponivel");
    return a;
}

int Cooperativa::delVinhoNome(string umVinho) {
    int count = 0;
    for(BSTItrIn<Vinho> bItr(vinhos); !bItr.isAtEnd();){
        Vinho vinho = bItr.retrieve();
        if(vinho.getNome() == umVinho){
            vinhos.remove(vinho);
            count++;
            bItr = BSTItrIn<Vinho>(vinhos);
        }
        else bItr.advance();
    }
    return count;
}

void Cooperativa::addVinicola(string umaVinicola) {
    Vinicola v(umaVinicola);
    auto it = vinicolas.find(v);
    if(it != vinicolas.end()){
        v.setVinhos(it->getVinhos() + 1);
        vinicolas.erase(it);
    }
    vinicolas.insert(v);
}

Vinicola Cooperativa::maisOpcoes() {
    Vinicola v("");
    for(const auto& elem: vinicolas){
        if(elem < v) v = elem;
    }
    return v;
}

void Cooperativa::addEnologoVinicola(string umEnologo, string umaVinicola) {
    priority_queue<Enologo> enologosTemp;
    bool added = false;
    while(!enologos.empty()){
        Enologo enologo = enologos.top();
        enologos.pop();
        if(enologo.getNome() == umEnologo){
            list<Vinicola>& vinicolas = enologo.getVinicolas();
            for(auto& elem: vinicolas){
                if(elem.getNome() == umaVinicola){
                    elem.addVinho();
                    added = true;
                }
            }if(!added) enologo.addVinicolaInexistente(Vinicola(umaVinicola));
            added = true;
        }
        enologosTemp.push(enologo);
    }
    if(!added){
        Enologo enologo(umEnologo);
        enologo.addVinicolaInexistente(Vinicola(umaVinicola));
        enologosTemp.push(enologo);
    }
    enologos = enologosTemp;
}

list<Vinicola> Cooperativa::vinicolasMelhoresNEnologos(int n) {
    list<Vinicola> a;
    priority_queue<Enologo> enologosTemp = enologos;
    while(!enologosTemp.empty() && n){
        n--;
        Enologo enologo = enologosTemp.top();
        enologosTemp.pop();
        for(const auto& elem: enologo.getVinicolas()){
            a.push_back(elem);
        }
    }
    return a;
}


