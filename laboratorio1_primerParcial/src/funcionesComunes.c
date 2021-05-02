/*
 * funcionesComunes.c
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "gets.h"
#include "validations.h"
#include "cliente.h"
#include "compra.h"
#define PENDIENTE 1
#define COBRADO 0

/**
* \brief Borrado de entrada de un listado de clientes, y compras asociadas, cambiando sus campos isEmpty a 1
* \param Cliente* listadoClientes Array de tipo Cliente
* \param int lenClientes Tamaño del Array listadoClientes
* \param int contadorIdCliente Maximo valor de Cliente asignado
* \param Compra* listadoCompras Array de tipo Compra
* \param int lenCompras Tamaño del Array listadoCompras
* \return Devuelve ERROR de validación de entrada (-3),
* 			que ingresó un cliente inválido (-2),
* 			que el cliente está disponible (-1)
* 			o EXITO (0)
*/
int funcionesComunes_bajaCliente(Cliente* listadoClientes, int lenClientes,int contadorIdCliente,
		Compra* listadoCompras, int lenCompras)
{
	int returnFunction = -3;
	int idClienteSeleccionado;
	int indiceDelIdCliente;
	char confirmaBorrado;
	if(listadoClientes != NULL && contadorIdCliente > 0)
	{
		returnFunction = -2;
		system("clear");
		printf("BAJA CLIENTE\n"
				"‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
		cliente_imprimirListadoClientes(listadoClientes,lenClientes,"Listado de Clientes\n\n");
		printf("\n");
		if(get_int(&idClienteSeleccionado,4,"Seleccionar Cliente: ","Cliente no encontrado.\n",1,1,contadorIdCliente-1,3,0)==1)
		{
			returnFunction = -1;
			indiceDelIdCliente = cliente_getIndexById(listadoClientes, lenClientes, idClienteSeleccionado);
			if(listadoClientes[indiceDelIdCliente].isEmpty == 0)
			{	printf("\nListado de compras del Cliente seleccionado\n\n");
				compra_imprimirComprasPorIdCliente(listadoCompras, lenCompras, idClienteSeleccionado);
				get_char(&confirmaBorrado,"snSN",5,"\n¿Seguro que desea eliminar el cliente? S/N: ","error",3);
				if(confirmaBorrado == 's' || confirmaBorrado == 'S')
				{
					returnFunction = 0;
					compra_bajaCompraPorIdCliente(listadoCompras, lenCompras, idClienteSeleccionado);
					listadoClientes[indiceDelIdCliente].isEmpty = 1;
				}
			}
			else
			{
				printf("Cliente no encontrado. \n");
			}
		}
		printf("Presione cualquier tecla para continuar...");
		getchar();
	}
	__fpurge(stdin);
	return returnFunction;
}

/**
* \brief Registra el pago de de entrada de un listado de compras
* \param Compra* listadoCompras Array de tipo Compra
* \param int lenCompras Tamaño del Array listadoCompras
* \param int contadorIdCompra Maximo valor de Compra asignado
* \param Cliente* listadoClientes Array de tipo Cliente
* \param int lenClientes Tamaño del Array listadoClientes
* \return Devuelve ERROR de validación de entrada (-1)
* 			o EXITO (0)
*/
int compra_pagarCompra(Compra* listadoCompras, int lenCompras, int contadorIdCompra,
		Cliente* listadoClientes, int lenClientes)
{
	int returnFunction = -1;
	int idCompraSeleccionado;
	int indiceDeIdCompraSeleccionado;
	float importePagado;
	char confirmarCambioEstado;
	if(listadoCompras != NULL && lenCompras > 0 && listadoClientes != NULL && lenClientes > 0 && contadorIdCompra > 0)
	{
		returnFunction = 0;
		system("clear");
		printf("PAGAR VENTA\n"
				"‾‾‾‾‾‾‾‾‾‾‾\n\n");
		if(compra_imprimirListadoComprasEstadoPendiente(listadoCompras, lenCompras, "Listado de compras en estado \"PENDIENTE\"\n\n") == -1)
		{
			printf("No hay compras con estado pendiente...\n");
		}
		if(get_int(&idCompraSeleccionado, 5, "\nSeleccione la venta a pagar: ","Error. ",1,1,contadorIdCompra-1,3,0)==1)
		{
			indiceDeIdCompraSeleccionado = compra_getIndexById(listadoCompras, lenCompras, idCompraSeleccionado);
			if(listadoCompras[indiceDeIdCompraSeleccionado].isEmpty == 0)
			{
				cliente_imprimirClientePorIndice(listadoClientes,"\nDatos del Cliente\n",cliente_getIndexById(listadoClientes,lenClientes,listadoCompras[indiceDeIdCompraSeleccionado].idCliente));
				if(get_float(&importePagado, 6,"\nIngrese el importe pagado: $","Error. ",1,1,99999,3,0) == 1)
				{
					listadoCompras[indiceDeIdCompraSeleccionado].importePagado = importePagado;
					get_char(&confirmarCambioEstado,"snSN",4,"\n¿Confirma cambio de estado? (S/N): ","Error. ", 3);
					if(confirmarCambioEstado == 's' || confirmarCambioEstado == 'S')
					{
						listadoCompras[indiceDeIdCompraSeleccionado].estadoDelCobro = COBRADO;
					}
				}
			}
			else
			{
				printf("\nNo es una venta válida.\nPresione cualquier tecla para continuar...");
				getchar();
			}
		}
	}
	__fpurge(stdin);
	return returnFunction;
}

/**
* \brief Da de baja una entrada de un listado de compras, , cambiando su campo isEmpty a 1
* \param Compra* listadoCompras Array de tipo Compra
* \param int lenCompras Tamaño del Array listadoCompras
* \param int contadorIdCompra Maximo valor de Compra asignado
* \param Cliente* listadoClientes Array de tipo Cliente
* \param int lenClientes Tamaño del Array listadoClientes
* \return Devuelve ERROR de validación de entrada (-1)
* 			o EXITO (0)
*/
int compra_cancelarCompra(Compra* listadoCompras, int lenCompras, int contadorIdCompra,
		Cliente* listadoClientes, int lenClientes)
{
	int returnFunction = -1;
	int idCompraSeleccionado;
	int indiceDeIdCompraSeleccionado;
	char confirmarCancelacion;
	char listaBlanca[5]="snSN";
	if(listadoCompras != NULL && lenCompras > 0 && listadoClientes != NULL && lenClientes > 0)
	{
		returnFunction = 0;
		system("clear");
		printf("CANCELAR COMPRA\n"
				"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
		if(compra_imprimirListadoCompras(listadoCompras, lenCompras, "Listado de compras\n\n")==-1)
			printf("No hay compras...\n");
		if(get_int(&idCompraSeleccionado, 5, "\nSeleccione la compra a cancelar: ","Error. ",1,1,contadorIdCompra-1,3,0)==1)
		{
			indiceDeIdCompraSeleccionado = compra_getIndexById(listadoCompras, lenCompras, idCompraSeleccionado);
			if(listadoCompras[indiceDeIdCompraSeleccionado].isEmpty == 0)
			{
				cliente_imprimirClientePorIndice(listadoClientes,"\nCliente que realizó la compra\n",cliente_getIndexById(listadoClientes,lenClientes,listadoCompras[indiceDeIdCompraSeleccionado].idCliente));
				if(get_char(&confirmarCancelacion,listaBlanca,4,"\n¿Confirma el borrado de la compra? (S/N): ","Error. ",3) == 1)
				{
					if(listadoCompras[indiceDeIdCompraSeleccionado].estadoDelCobro == PENDIENTE)
					{
						listadoCompras[indiceDeIdCompraSeleccionado].isEmpty = 1;
					}
					else if(confirmarCancelacion == 's' || confirmarCancelacion == 'S')
					{
						printf("\nNo se puede borrar. La compra ya fue abonada.\n\nPresione cualquier tecla para continuar...");
						getchar();
					}
				}
			}
			else
			{
				printf("\nLa compra seleccionada no existe.\n\nPresione cualquier tecla para continuar...");
				getchar();
			}
		}
	}
	__fpurge(stdin);
	return returnFunction;
}