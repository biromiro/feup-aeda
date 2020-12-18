
#include <algorithm>
#include "Clinica.h"

//Animal

Animal::Animal(string umNome, string umaEspecie, int numeroConsultas):
nome(umNome), especie(umaEspecie), numConsultas(numeroConsultas)
{}

string Animal::getNome() const
{ return nome; }

string Animal::getEspecie() const
{ return especie; }

int Animal::getNumConsultas() const
{ return numConsultas; }

void Animal::incNumConsultas()
{ numConsultas++; }


// Veterinario

Veterinario::Veterinario(string umNome):nome(umNome)
{}

string Veterinario::getNome() const
{ return nome; }

list<string> Veterinario::getAnimais() const
{ return meusAnimais; }

void Veterinario::addAnimal(string umNomeAnimal)
{ meusAnimais.push_back(umNomeAnimal); }


// Consulta

Consulta::Consulta(int umaHora, int umDia, int umMes, string umNomeAnimal):
	hora(umaHora), dia(umDia), mes(umMes), nomeAnimal(umNomeAnimal)
{}

string Consulta::getNomeAnimal() const
{ return nomeAnimal; }

int Consulta::getHora() const { return hora; }
int Consulta::getDia() const { return dia; }
int Consulta::getMes() const { return mes; }


void ConsultasVet::addConsulta(const Consulta &c1)
{ minhasConsultas.insert(c1); }


//Clinica

Clinica::Clinica()
{}

list<ConsultasVet> Clinica::getConsultasDisponiveis() const
{ return consultasDisponiveis; }

hashAnimal Clinica::getAnimais() const
{ return animais; }

priority_queue<Veterinario> Clinica::getVeterinarios() const
{ return veterinarios; }

void Clinica::addConsultasDisponiveisVet(const ConsultasVet &v1)
{ consultasDisponiveis.push_front(v1); }

void Clinica::addAnimal(const Animal &a1)
{ animais.insert(a1); }

void Clinica::addVeterinario(const Veterinario &v1)
{ veterinarios.push(v1); }


/////////////////////////////////////////////////////////////////////////

//TODO: Implementar corretamente o construtor e inicializacao da BST!
ConsultasVet::ConsultasVet(string umNomeVet): nomeVeterinario(umNomeVet),
        minhasConsultas(Consulta(0,0,0,""))
{

}

BST<Consulta> ConsultasVet::getConsultas() {
    return minhasConsultas;
}


bool Consulta::operator < (const Consulta &c2) const {
    if(mes < c2.mes) return true;
    else if(mes > c2.mes) return false;
    else if(dia < c2.dia) return true;
    else if(dia > c2.dia) return false;
    else return hora < c2.hora;
}

bool Veterinario::operator<(const Veterinario& v1) const
{
	if(meusAnimais.size() > v1.meusAnimais.size()) return true;
	else if(meusAnimais.size() < v1.meusAnimais.size()) return false;
	else return nome > v1.nome;
}

void Clinica::addConsultas(const vector<Consulta> consultas1, string nomeVet) {
    for(auto& elem: consultasDisponiveis){
        if(elem.nomeVeterinario == nomeVet){
            for(const auto consulta: consultas1){
                elem.addConsulta(consulta);
            }
            return;
        }
    }
    ConsultasVet consultas(nomeVet);
    for(const auto elem: consultas1) consultas.addConsulta(elem);
    consultasDisponiveis.push_front(consultas);
}

list<Consulta> Clinica::veConsultasDisponiveis(int dia1, int dia2, int mesC, string nomeVet) const {
    list<Consulta> a;
    for(auto elem: consultasDisponiveis){
        if(elem.nomeVeterinario == nomeVet){
            BST<Consulta> tree = elem.getConsultas();
            for(BSTItrIn<Consulta> bItr(tree); !bItr.isAtEnd(); bItr.advance()){
                Consulta consulta = bItr.retrieve();
                if(consulta.getMes() != mesC) continue;
                if(consulta.getDia() >= dia1 && consulta.getDia() <= dia2){
                    a.push_back(consulta);
                }
            }
        }
    }
    return a;
}

bool Clinica::marcaConsulta(int &horaC, int &diaC, int &mesC, string nomeAnimal, string nomeVet) {
    for(auto it = consultasDisponiveis.begin(); it != consultasDisponiveis.end(); it++){
        if(it->nomeVeterinario == nomeVet){
            BST<Consulta> consultas = (it->getConsultas());
            for(BSTItrIn<Consulta> bItr(consultas); !bItr.isAtEnd(); bItr.advance()){
                Consulta consulta = bItr.retrieve();
                if(consulta.getMes() < mesC) continue;
                else if(consulta.getDia() < diaC && consulta.getMes() == mesC) continue;
                else if(consulta.getHora() < horaC && consulta.getMes() == mesC && consulta.getDia() == diaC) continue;
                horaC = consulta.getHora(); diaC = consulta.getDia(); mesC = consulta.getMes();
                consultas.remove(consulta);
                it->minhasConsultas = consultas;
                return true;
            }
            return false;
        }
    }
    return false;
}

Animal Clinica::fimConsulta(string umNomeAnimal, string umNomeEspecie) {
    auto it = animais.find(Animal(umNomeAnimal,"",0));
    if(it != animais.end()){
        Animal animal(it->getNome(),it->getEspecie(),it->getNumConsultas()+1);
        animais.erase(it);
        animais.insert(animal);
        return animal;
    }else{
        Animal animal(umNomeAnimal,umNomeEspecie,1);
        animais.insert(animal);
        return animal;
    }
}

int Clinica::numAnimaisEspecie(string umNomeEspecie) const {
    return count_if(animais.begin(), animais.end(), [&umNomeEspecie](const Animal& animal){
        return animal.getEspecie() == umNomeEspecie;});
}

Veterinario Clinica::alocaVeterinario(string umNomeAnimal) {
    if(veterinarios.empty()) return Veterinario("");
    Veterinario v = veterinarios.top();
    veterinarios.pop();
    v.addAnimal(umNomeAnimal);
    veterinarios.push(v);
    return v;
}

list<string> Clinica::veterinariosMaisN(int n) const {
    list<string> a;
    priority_queue<Veterinario> temp = veterinarios;
    while(!temp.empty()){
        Veterinario top = temp.top();
        temp.pop();
        if(top.getAnimais().size() >= n){
            a.push_front(top.getNome());
        }
    }
    return a;
}
