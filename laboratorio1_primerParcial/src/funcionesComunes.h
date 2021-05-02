/*
 * funcionesComunes.h
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#ifndef FUNCIONESCOMUNES_H_
#define FUNCIONESCOMUNES_H_

int funcionesComunes_bajaCliente(Cliente* listadoClientes, int lenClientes, int contadorIdCliente,
		Compra* listadoCompras, int lenCompras);
int compra_pagarCompra(Compra* listadoCompras, int lenCompras, int contadorIdCompra,
		Cliente* listadoClientes, int lenClientes);
int compra_cancelarCompra(Compra* listadoCompras, int lenCompras, int contadorIdCompra,
		Cliente* listadoClientes, int lenClientes);



#endif /* FUNCIONESCOMUNES_H_ */