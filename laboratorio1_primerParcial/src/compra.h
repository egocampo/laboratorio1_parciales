/*
 * compra.h
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#ifndef COMPRA_H_
#define COMPRA_H_
#include "cliente.h"


typedef struct
{
	int idCliente;
	int cantidadDeBarbijos;
	char direccionDeEntrega[64];
	char color[32];
	int idVenta;
	float importePagado;
	int estadoDelCobro;
	float precioPorUnidad;
	int isEmpty;
}Compra;

int compra_getIndexById(Compra* listadoCompras, int len, int id);
int compra_inicializarCompras(Compra* listadoCompras, int len);
int compra_altaCompra(Compra* listadoCompras, int lenCompras, Cliente* listadoClientes,int lenClientes,int* contadorIdCompra);
int compra_buscarIndexEmpty(Compra* listadoCompras, int len);
int compra_imprimirListadoCompras(Compra* listadoCompras, int len, char* mensaje);
int compra_imprimirComprasPorIdCliente(Compra* listadoCompras, int lenCompras, int idCliente);
int compra_imprimirCompraPorIndice(Compra* listadoCompras, int indice);
int compra_bajaCompraPorIdCliente(Compra* listadoCompras, int len, int idCliente);
int compra_imprimirListadoComprasEstadoPendiente(Compra* listadoCompras, int len, char* mensaje);


#endif /* COMPRA_H_ */
