#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Clinica.h"

using testing::Eq;

TEST(test,a1){
    Clinica cli;

    Consulta c1(2,10,3);
    Consulta c2(3,2,3);
    Consulta c3(4,10,3);
    Consulta c4(3,2,3);
    Consulta c5(4,20,2);

    vector<Consulta> vc;
    vc.push_back(c1);
    vc.push_back(c2);
    vc.push_back(c3);
    vc.push_back(c4);
    vc.push_back(c5);

    cli.addConsultas(vc,"Raul Santos");
    list<ConsultasVet> cv=cli.getConsultasDisponiveis();
    EXPECT_EQ(1,cv.size());
    BST<Consulta> consultasV=cv.front().minhasConsultas;

    Consulta consulta1=consultasV.findMin();
    EXPECT_EQ(2,consulta1.getMes());
    consultasV.remove(consulta1);
    consulta1=consultasV.findMin();
    EXPECT_EQ(3,consulta1.getMes());
    EXPECT_EQ(2,consulta1.getDia());
    consultasV.remove(consulta1);
    consulta1=consultasV.findMin();
    EXPECT_EQ(3,consulta1.getMes());
    EXPECT_EQ(10,consulta1.getDia());
    EXPECT_EQ(2,consulta1.getHora());
    consultasV.remove(consulta1);
    consulta1=consultasV.findMin();
    EXPECT_EQ(10,consulta1.getDia());
    EXPECT_EQ(4,consulta1.getHora());
    consultasV.remove(consulta1);
    EXPECT_EQ(true,consultasV.isEmpty());

    vc.clear();
    vc.push_back(c1);
    vc.push_back(c2);

    cli.addConsultas(vc,"Maria Dinis");
    cv=cli.getConsultasDisponiveis();
    EXPECT_EQ(2,cv.size());
    EXPECT_EQ("Maria Dinis",cv.front().nomeVeterinario);
}


TEST(test,a2) {
    Clinica cli;

    Consulta c1(2,10,3);
    Consulta c2(3,2,3);
    Consulta c3(4,10,3);
    Consulta c4(3,5,3);
    Consulta c5(4,20,2);

    ConsultasVet vet1("Raul Santos");
    vet1.addConsulta(c1);
    vet1.addConsulta(c2);
    vet1.addConsulta(c3);
    vet1.addConsulta(c4);
    vet1.addConsulta(c5);
    ConsultasVet vet2("Maria Dinis");
    ConsultasVet vet3("Jaime Luis");
    vet3.addConsulta(c1);
    vet3.addConsulta(c2);
    vet3.addConsulta(c3);

    cli.addConsultasDisponiveisVet(vet1);
    cli.addConsultasDisponiveisVet(vet2);
    cli.addConsultasDisponiveisVet(vet3);

    list<Consulta> res;

    res = cli.veConsultasDisponiveis(1,12,3,"Raul Santos");
    EXPECT_EQ(4,res.size());
    EXPECT_EQ(2,res.front().getDia());
    EXPECT_EQ(4,res.back().getHora());
    EXPECT_EQ(10,res.back().getDia());
    EXPECT_EQ(3,res.back().getMes());

    res = cli.veConsultasDisponiveis(1,12,3,"Maria Dinis");
    EXPECT_EQ(0,res.size());

    res = cli.veConsultasDisponiveis(1,12,3,"Carolina Silva");
    EXPECT_EQ(0,res.size());

    res = cli.veConsultasDisponiveis(12,14,3,"Jaime Luis");
    EXPECT_EQ(0,res.size());
}


TEST(test,a3) {
    Clinica cli;

    Consulta c1(2,10,3);
    Consulta c2(3,2,3);
    Consulta c3(4,10,3);
    Consulta c4(3,5,3);

    ConsultasVet vet1("Raul Santos");
    vet1.addConsulta(c1);
    vet1.addConsulta(c2);
    vet1.addConsulta(c3);
    vet1.addConsulta(c4);

    cli.addConsultasDisponiveisVet(vet1);

    int horaC=3, diaC=2, mesC=3;
    bool res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
    EXPECT_EQ(true,res);
    EXPECT_EQ(2,diaC);
    BST<Consulta> consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
    Consulta consX=consultasX.findMin();
    consultasX.remove(consX);
    consX=consultasX.findMin();
    consultasX.remove(consX);
    consX=consultasX.findMin();
    consultasX.remove(consX);
    EXPECT_EQ(true,consultasX.isEmpty());

    horaC=4, diaC=5, mesC=3;
    res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
    EXPECT_EQ(true,res);
    EXPECT_EQ(2,horaC);
    EXPECT_EQ(10,diaC);
    consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
    consX=consultasX.findMin();
    consultasX.remove(consX);
    consX=consultasX.findMin();
    consultasX.remove(consX);
    EXPECT_EQ(true,consultasX.isEmpty());

    horaC=4, diaC=15, mesC=3;
    res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Raul Santos");
    EXPECT_EQ(false,res);
    consultasX=cli.getConsultasDisponiveis().front().minhasConsultas;
    consX=consultasX.findMin();
    consultasX.remove(consX);
    consX=consultasX.findMin();
    consultasX.remove(consX);
    EXPECT_EQ(true,consultasX.isEmpty());

    ConsultasVet vet2("Maria Dinis");
    cli.addConsultasDisponiveisVet(vet2);

    res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Maria Dinis");
    EXPECT_EQ(false,res);

    res=cli.marcaConsulta(horaC,diaC,mesC,"bobby", "Joana Lima");
    EXPECT_EQ(false,res);
}


TEST(test,b1)  {
    Clinica cli;
    Animal a1=cli.fimConsulta("bobby","cao");
    EXPECT_EQ("bobby", a1.getNome());
    EXPECT_EQ(1, a1.getNumConsultas());

    a1=cli.fimConsulta("tareco","gato");
    EXPECT_EQ("tareco", a1.getNome());
    EXPECT_EQ(1, a1.getNumConsultas());

    a1=cli.fimConsulta("bobby","cao");
    a1=cli.fimConsulta("bobby","cao");
    EXPECT_EQ("bobby", a1.getNome());
    EXPECT_EQ(3, a1.getNumConsultas());

    a1=cli.fimConsulta("dori","peixe");
    EXPECT_EQ("dori", a1.getNome());
    EXPECT_EQ(1, a1.getNumConsultas());

    EXPECT_EQ(3,cli.getAnimais().size());
}


TEST(test,b2) {
    Clinica cli;

    Animal a1("bobby", "cao");
    Animal a2("dori", "peixe");
    Animal a3("kurika","cao");
    Animal a4("nero","cao");
    Animal a5("nemo","peixe");
    cli.addAnimal(a1);
    cli.addAnimal(a2);
    cli.addAnimal(a3);
    cli.addAnimal(a4);
    cli.addAnimal(a5);
    EXPECT_EQ(3,cli.numAnimaisEspecie("cao"));
}


TEST(test,c1) {
    Clinica cli;

    Veterinario vet1("Joao Santos");
    vet1.addAnimal("bobby");
    vet1.addAnimal("tareco");
    vet1.addAnimal("dori");
    cli.addVeterinario(vet1);

    Veterinario vet2("Jaime Dinis");
    cli.addVeterinario(vet2);

    Veterinario vet3("Maria Silva");
    vet3.addAnimal("tareco");
    vet3.addAnimal("lassie");
    cli.addVeterinario(vet3);

    Veterinario vetX=cli.alocaVeterinario("romi");
    EXPECT_EQ("Jaime Dinis", vetX.getNome());
    EXPECT_EQ(1,vetX.getAnimais().size());
    EXPECT_EQ(3,cli.getVeterinarios().size());

    vetX=cli.alocaVeterinario("bravo");
    EXPECT_EQ("Jaime Dinis", vetX.getNome());

    vetX=cli.alocaVeterinario("baba");
    EXPECT_EQ("Jaime Dinis", vetX.getNome());

    vetX=cli.alocaVeterinario("kurika");
    EXPECT_EQ("Maria Silva", vetX.getNome());
    EXPECT_EQ(3,vetX.getAnimais().size());
    EXPECT_EQ(3,cli.getVeterinarios().size());
}


TEST(test,c2)  {
    Clinica cli;

    Veterinario vet1("Joao Santos");
    vet1.addAnimal("bobby");
    vet1.addAnimal("tareco");
    vet1.addAnimal("dori");
    cli.addVeterinario(vet1);

    Veterinario vet2("Jaime Dinis");
    cli.addVeterinario(vet2);

    Veterinario vet3("Maria Silva");
    vet3.addAnimal("tareco");
    vet3.addAnimal("lassie");
    cli.addVeterinario(vet3);

    Veterinario vet4("Carlos Pereira");
    vet4.addAnimal("bobby");
    vet4.addAnimal("tareco");
    vet4.addAnimal("dori");
    vet4.addAnimal("lassie");
    cli.addVeterinario(vet4);

    list<string> res=cli.veterinariosMaisN(1);
    EXPECT_EQ(3,res.size());
    EXPECT_EQ("Carlos Pereira",res.front());
    res.pop_front();
    EXPECT_EQ("Joao Santos",res.front());

    res=cli.veterinariosMaisN(6);
    EXPECT_EQ(0,res.size());
}
