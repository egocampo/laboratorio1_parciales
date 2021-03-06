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
		if(cliente_imprimirListadoClientes(listadoClientes,lenClientes,"Listado de Clientes\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n")==0)
		{
			printf("\n");
			if(get_int(&idClienteSeleccionado,4,"Ingrese el n° Id. del cliente a borrar: ","Cliente no encontrado.\n",1,1,contadorIdCliente-1,3,0)==1)
			{
				returnFunction = -1;
				indiceDelIdCliente = cliente_getIndexById(listadoClientes, lenClientes, idClienteSeleccionado);
				if(listadoClientes[indiceDelIdCliente].isEmpty == 0)
				{	printf("\nListado de compras del Cliente seleccionado\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
					compra_imprimirComprasPorIdCliente(listadoCompras, lenCompras, idClienteSeleccionado);
					get_char(&confirmaBorrado,"snSN",5,"\n¿Seguro que desea eliminar el cliente? S/N: ","error",3);
					if(confirmaBorrado == 's' || confirmaBorrado == 'S')
					{
						returnFunction = 0;
						compra_bajaCompraPorIdCliente(listadoCompras, lenCompras, idClienteSeleccionado);
						listadoClientes[indiceDelIdCliente].isEmpty = 1;
						printf("\n¡CLIENTE BORRADO CORRECTAMENTE DEL SISTEMA!\n");
					}
				}
				else
				{
					printf("Cliente no encontrado. \n");
				}
			}
		}
		printf("\nPresione cualquier tecla para continuar...");
		getchar();
	}
	__fpurge(stdin);
	return returnFunction;
}

