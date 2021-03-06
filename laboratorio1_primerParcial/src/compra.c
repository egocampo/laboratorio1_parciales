/*
 * compra.c
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#include <stdio_ext.h>
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
			if(cliente_imprimirListadoClientes(listadoClientes, lenClientes, "Listado de Clientes\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n")==0)
			{
				get_int(&clienteSeleccionado, 4,"\nSeleccione un cliente: ","Cliente no encontrado. ",1,1,lenClientes-1,3,0);
				indiceDelIdCliente = cliente_getIndexById(listadoClientes, lenClientes, clienteSeleccionado);
				if(listadoClientes[indiceDelIdCliente].isEmpty == 0 && indiceDelIdCliente >= 0)
				{
					if(get_int(&buffer.cantidadDeBarbijos,5,"\nCantidad de barbijos: ","Error. ",1,1,9999,3,0)==1)
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
								printf("\n¡OPERACION AGREGADA CORRECTAMENTE AL SISTEMA!\n\nNumero de identificador generado: %d\n",listadoCompras[indiceEmpty].idVenta);
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
		}
		else
		{
			printf("No hay espacio disponible en el listado de Clientes.\n Comuniquese con el programador.");
		}

	}
	printf("\nPresione cualquier tecla para continuar...");
	getchar();
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
		if(returnFunction == -1)
			printf("El cliente no tiene compras registradas.\n");
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
		if(returnFunction==-1)
		{
			printf("No hay compras con estado pendiente...\n");
		}
	}
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
		if(compra_imprimirListadoComprasEstadoPendiente(listadoCompras, lenCompras, "Listado de compras en estado \"PENDIENTE\"\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n") == 0)
		{
			if(get_int(&idCompraSeleccionado, 5, "\nSeleccione la venta a pagar: ","Error. ",1,1,contadorIdCompra-1,3,0)==1)
			{
				indiceDeIdCompraSeleccionado = compra_getIndexById(listadoCompras, lenCompras, idCompraSeleccionado);
				if(listadoCompras[indiceDeIdCompraSeleccionado].isEmpty == 0 && listadoCompras[indiceDeIdCompraSeleccionado].estadoDelCobro == PENDIENTE)
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
					printf("\nNo es una venta válida.\n");
				}
			}
		}
		printf("\nPresione cualquier tecla para continuar...");
		getchar();
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
	int indiceCliente;
	if(listadoCompras != NULL && lenCompras > 0 && listadoClientes != NULL && lenClientes > 0)
	{
		returnFunction = 0;
		system("clear");
		printf("CANCELAR COMPRA\n"
				"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
		if(compra_imprimirListadoCompras(listadoCompras, lenCompras, "Listado de compras\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n")==0)
		{
			if(get_int(&idCompraSeleccionado, 5, "\nSeleccione la compra a cancelar: ","Error. ",1,1,contadorIdCompra-1,3,0)==1)
			{
				indiceDeIdCompraSeleccionado = compra_getIndexById(listadoCompras, lenCompras, idCompraSeleccionado);
				if(listadoCompras[indiceDeIdCompraSeleccionado].isEmpty == 0)
				{
					cliente_imprimirClientePorIndice(listadoClientes,"\nCliente que realizó la compra\n",cliente_getIndexById(listadoClientes,lenClientes,listadoCompras[indiceDeIdCompraSeleccionado].idCliente));
					if(get_char(&confirmarCancelacion,listaBlanca,4,"\n¿Confirma el borrado de la compra? (S/N): ","Error. ",3) == 1)
					{
						if(confirmarCancelacion == 's' || confirmarCancelacion == 'S')
						{
							if(listadoCompras[indiceDeIdCompraSeleccionado].estadoDelCobro == PENDIENTE)
							{
								listadoCompras[indiceDeIdCompraSeleccionado].isEmpty = 1;
								indiceCliente = cliente_getIndexById(listadoClientes, lenClientes, listadoCompras[indiceDeIdCompraSeleccionado].idCliente);
								(listadoClientes[indiceCliente].cantidadCompras)--;
							}
							else
							{
								printf("\nNo se puede borrar. La compra ya fue abonada.\n\nPresione cualquier tecla para continuar...");
								getchar();
							}
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
		else
		{
			printf("No hay compras...\n\nPresione cualquier tecla para continuar...");
			getchar();
		}
	}
	__fpurge(stdin);
	return returnFunction;
}
