/*
 * cliente.h
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

typedef struct
{
	char nombre[32];
	char apellido[32];
	char cuit[12];
	int idCliente;
	int cantidadCompras;
	int isEmpty;
}Cliente;

int cliente_getIndexById(Cliente* listadoClientes, int len, int id);
int cliente_inicializarClientes(Cliente* listadoClientes, int len);
int cliente_buscarIndexEmtpy(Cliente* listadoClientes, int len);
int cliente_altaCliente(Cliente* listadoClientes, int len, int* idCliente);
int cliente_modificarCliente(Cliente* listadoClientes, int len, int contadorIdCliente);
int cliente_imprimirListadoClientes(Cliente* listadoClientes, int len, char* mensaje);
int cliente_imprimirListadoClientesOpcion7(Cliente* listadoClientes, int len, char* mensaje);
int cliente_imprimirClientePorIndice(Cliente* listadoClientes, char* mensaje,int indice);

#endif /* CLIENTE_H_ */
