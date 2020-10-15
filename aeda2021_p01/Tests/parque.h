#include <iostream>
#include <string>
#include <vector>

class InfoCartao {
public:
	std::string nome;
	bool presente;
    InfoCartao(const std::string &nm, bool pres): nome(nm), presente(pres){};
    bool operator==(InfoCartao cliente) const{
        return (cliente.nome == nome && cliente.presente == presente);
    }
};

class ParqueEstacionamento {
	unsigned int vagas;
	const unsigned int lotacao;
	std::vector<InfoCartao> clientes;
	const unsigned int numMaximoClientes;
public:
	ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli)
	: vagas(lot), lotacao(lot), clientes(), numMaximoClientes(nMaxCli){};
	bool adicionaCliente(const std::string & nome);
	bool retiraCliente(const std::string & nome);
	bool entrar(const std::string & nome);
	bool sair(const std::string & nome);
	int posicaoCliente(const std::string & nome) const;
	unsigned getNumLugares() const;
	unsigned getNumMaximoClientes() const;
	unsigned getNumLugaresOcupados() const;
	unsigned getNumClientesAtuais() const;
	const ParqueEstacionamento& operator += (const ParqueEstacionamento & p2);
};