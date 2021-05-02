/*
 * compra.c
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compra.h"
#include "cliente.h"
#include "gets.h"
#define PENDIENTE 1
#define COBRADO 0

/**
* \brief Obtiene el indice del listado de compras a partir del id porporcionado
* \param Compra* listadoCompras Array de tipo Compras del cual deseamos retornar el indice
* \param int lenCompras Tamaño del Array listadoCompras
* \param int idCompra Id de la compra proporcionado para realizar la búsqueda
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no encontró el número (-1)
*			o el número de id correspondiente (>=0)
*/
int compra_getIndexById(Compra* listadoCompras, int lenCompras, int idCompra)
{
	int returnFunction = -2;
	int i;
	if(listadoCompras != NULL && lenCompras > 0 && idCompra > 0)
	{
		returnFunction = -1;
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].idVenta == idCompra)
			{
				returnFunction = i;
				break;
			}
		}
	}
	return returnFunction;
}

/**
* \brief Obtiene el primer índice vacío del listado de compras
* \param Compra* listadoCompras Array de tipo Compra del cual deseamos retornar primer índice vacío
* \param int lenCompras Tamaño del Array listadoCompras
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no encontró ningún índice vacío (-1)
* 			o el primer número de índice vacío (>=0)
*/
int compra_buscarIndexEmpty(Compra* listadoCompras, int lenCompras)
{
	int returnFunction = -2;
	int i;
	if(listadoCompras != NULL && lenCompras > 0)
	{
		returnFunction = -1;
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].isEmpty == 1)
			{
				returnFunction = i;
				break;
			}
		}
	}
	return returnFunction;
}

/**
* \brief Inicializa el listado de compras seteando los campos isEmpty, importe pagado y estado del cobro
* \param Compra* listadoCompras Array de tipo Compra a inicializar
* \param int lenCompras Tamaño del Array listadoCompras
* \return Devuelve ERROR de validación de entrada (-1) o EXITO (0)
*/
int compra_inicializarCompras(Compra* listadoCompras, int lenCompras)
{
	int returnFunction = -1;
	int i;
	if(listadoCompras != NULL && lenCompras > 0)
	{
		returnFunction = 0;
		for(i=0;i<lenCompras;i++)
		{
			listadoCompras[i].importePagado = -1;
			listadoCompras[i].estadoDelCobro = -1;
			listadoCompras[i].isEmpty = 1;
		}
	}
	return returnFunction;
}

/**
* \brief Crear una nueva entrada en el listado de compras
* \param Compra* listadoCompras Array de tipo Compra donde almacenaremos los datos
* \param int lenCompras Tamaño del Array listadoCompras
* \param Cliente* listadoClientes Array de tipo Cliente desde donde imprimiremos los datos del mismo
* \param int lenClientes Tamaño del Array listadoClientes
* \param int* contadorIdCompra Id del cliente proporcionado para asignar a la nueva compra
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no pudo crear la entrada (-1)
* 			o EXITO (0)
*/
int compra_altaCompra(Compra* listadoCompras, int lenCompras,
		Cliente* listadoClientes,int lenClientes,int* contadorIdCompra)
{
	int returnFunction = -1;
	int indiceEmpty;
	int clienteSeleccionado;
	int indiceDelIdCliente;
	Compra buffer;
	if(listadoCompras != NULL && lenCompras > 0 && listadoClientes != NULL && lenClientes > 0 && contadorIdCompra != NULL)
	{
		returnFunction = -1;
		if((indiceEmpty = compra_buscarIndexEmpty(listadoCompras, lenCompras)) >= 0)
		{
			system("clear");
			printf("REALIZAR COMPRA\n"
					"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
			cliente_imprimirListadoClientes(listadoClientes, lenClientes, "Listado de Clientes\n\n");
			printf("\n");
			get_int(&clienteSeleccionado, 4,"Seleccione un cliente: ","Cliente no encontrado. ",1,1,lenClientes-1,3,0);
			indiceDelIdCliente = cliente_getIndexById(listadoClientes, lenClientes, clienteSeleccionado);
			if(listadoClientes[indiceDelIdCliente].isEmpty == 0 && indiceDelIdCliente >= 0)
			{
				if(get_int(&buffer.cantidadDeBarbijos,5,"Cantidad de barbijos: ","Error. ",1,1,9999,3,0)==1)
				{
					if(get_text(buffer.direccionDeEntrega,64,"Dirección de entrega: ","Error. ",3)==1)
					{
						if(get_name(buffer.color,32,"Color de barbijos: ","Error. ",3)==1 && strncmp(buffer.color,"",32) != 0)
						{
							returnFunction = 0;
							buffer.idCliente = clienteSeleccionado;
							buffer.idVenta = *contadorIdCompra;
							buffer.estadoDelCobro = PENDIENTE;
							buffer.isEmpty = 0;
							listadoClientes[indiceDelIdCliente].cantidadCompras = listadoClientes[indiceDelIdCliente].cantidadCompras + 1;
							listadoCompras[indiceEmpty] = buffer;
							*contadorIdCompra = *contadorIdCompra + 1;
							printf("\nNumero de identificador generado: %d\n\nPresione una tecla para continuar...",listadoCompras[indiceEmpty].idVenta);
							getchar();
						}
					}
				}
			}
			else
			{
				printf("Cliente no encontrado. \n");
				getchar();
			}
		}
		else
		{
			printf("No hay espacio disponible en el listado de Clientes. Comuniquese con el programador.");
		}

	}
	return returnFunction;
}

/**
* \brief Imprime por pantalla las compras de un cliente dado.
* \param Compra* listadoCompras Array de tipo Compra con los datos a verificar e imprimir
* \param int lenCompras Tamaño del Array listadoCompras
* \param int idCliente Cliente a comparar para imprimir
* \return Devuelve ERROR de validación de entrada (-2)
* 			que no encontró ninguna compra del cliente (-1)
* 			o EXITO (0)
*/
int compra_imprimirComprasPorIdCliente(Compra* listadoCompras, int lenCompras, int idCliente)
{
	int returnFunction = -2;
	int i;
	if(listadoCompras != NULL && lenCompras > 0 && idCliente > 0)
	{
		returnFunction = -1;
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].idCliente == idCliente && listadoCompras[i].isEmpty == 0)
			{
				returnFunction = 0;
				compra_imprimirCompraPorIndice(listadoCompras, i);
			}
		}
	}
	return returnFunction;
}

/**
* \brief Imprime por pantalla una posición del listado de compras
* \param Compra* listadoCompras Array de tipo Compra a imprimir
* \param int indice Posición dentro del array de la compra a imprimir
* \return Devuelve ERROR de validación de entrada (-1)
* 			o EXITO (0)
*/
int compra_imprimirCompraPorIndice(Compra* listadoCompras, int indice)
{
	int returnFunction = -1;
	if(listadoCompras != NULL && indice >= 0)
	{
		returnFunction = 0;
		if(listadoCompras[indice].importePagado > 0 && listadoCompras[indice].isEmpty == 0)
		{
			printf("Id Compra: %d) Cant: %d - Dirección: %s - Color: %s\n",
					listadoCompras[indice].idVenta,
					listadoCompras[indice].cantidadDeBarbijos,
					listadoCompras[indice].direccionDeEntrega,
					listadoCompras[indice].color);
		}
	}
	return returnFunction;
}

/**
* \brief Borrado de entradas listado de compras de las compras de un determinado cliente, cambiando su campo isEmpty a 1
* \param Compra* listadoCompras Array de tipo Compra donde está la entrada a borrar
* \param int lenCompras Tamaño del Array listadoCompras
* \param int idCliente Id del cliente a buscar para eliminar sus compras relacionadas.
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no encontró ninguna compra del cliente (-1)
* 			o EXITO (0)
*/
int compra_bajaCompraPorIdCliente(Compra* listadoCompras, int len, int idCliente)
{
	int returnFunction = -2;
	int indiceCompra;
	if(listadoCompras != NULL && len > 0 && idCliente > 0)
	{
		returnFunction = -1;
		for(indiceCompra=0;indiceCompra<len;indiceCompra++)
		{
			if(listadoCompras[indiceCompra].idCliente == idCliente)
			{
				returnFunction = 0;
				listadoCompras[indiceCompra].isEmpty = 1;
			}
		}
	}
	return returnFunction;
}

/**
* \brief Imprime por pantalla el listado de compras
* \param Compra* listadoClientes Array de tipo Compra a imprimir
* \param int lenCompras Tamaño del Array listadoCompras
* \param char* mensaje Puntero a dirección de memoria del mensaje a imprimir antes del listado.
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no imprime ninguno (-1)
* 			o EXITO (0)
*/
int compra_imprimirListadoCompras(Compra* listadoCompras, int lenCompras, char* mensaje)
{
	int returnFunction = -2;
	int i;
	if(listadoCompras != NULL && lenCompras > 0 && mensaje != NULL)
	{
		returnFunction = -1;
		printf("%s",mensaje);
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].isEmpty == 0)
			{
				returnFunction = 0;
				compra_imprimirCompraPorIndice(listadoCompras, i);
			}
		}
	}
	return returnFunction;
}

/**
* \brief Imprime por pantalla el listado de compras con estado pendiente
* \param Compra* listadoClientes Array de tipo Compra a imprimir
* \param int lenCompras Tamaño del Array listadoCompras
* \param char* mensaje Puntero a dirección de memoria del mensaje a imprimir antes del listado.
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no imprime ninguno (-1)
* 			o EXITO (0)
*/
int compra_imprimirListadoComprasEstadoPendiente(Compra* listadoCompras, int lenCompras, char* mensaje)
{
	int returnFunction = -2;
	int i;
	if(listadoCompras != NULL && lenCompras > 0 && mensaje != NULL)
	{
		returnFunction = -1;
		printf("%s",mensaje);
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].isEmpty == 0 && listadoCompras[i].estadoDelCobro == PENDIENTE)
			{
				returnFunction = 0;
				compra_imprimirCompraPorIndice(listadoCompras, i);
			}
		}
	}
	return returnFunction;
}
