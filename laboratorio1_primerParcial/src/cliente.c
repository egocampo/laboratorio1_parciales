/*
 * cliente.c
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "gets.h"
#include "validations.h"

/**
* \brief Obtiene el indice del listado de clientes a partir del id porporcionado
* \param Cliente* listadoClientes Array de tipo Cliente del cual deseamos retornar el indice
* \param int lenClientes Tamaño del Array listadoClientes
* \param int id Id del cliente proporcionado para realizar la búsqueda
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no encontró el número (-1)
* 			o el número de id correspondiente (>=0)
*/
int cliente_getIndexById(Cliente* listadoClientes, int lenClientes, int idCliente)
{
	int returnFunction = -2;
	int i;
	if(listadoClientes != NULL && lenClientes > 0 && idCliente > 0)
	{
		returnFunction = -1;
		for(i=0;i<lenClientes;i++)
		{
			if(listadoClientes[i].idCliente == idCliente)
			{
				returnFunction = i;
				break;
			}
		}
	}
	return returnFunction;
}

/**
* \brief Inicializa el listado de clientes seteando los campos isEmpty y cantidad compras
* \param Cliente* listadoClientes Array de tipo Cliente a inicializar
* \param int lenClientes Tamaño del Array listadoClientes
* \return Devuelve ERROR de validación de entrada (-1) o EXITO (0)
*/
int cliente_inicializarClientes(Cliente* listadoClientes, int lenClientes)
{
	int returnFunction = -1;
	int i;
	if(listadoClientes != NULL && lenClientes > 0)
	{
		returnFunction = 0;
		for(i=0;i<lenClientes;i++)
		{
			listadoClientes[i].isEmpty = 1;
			listadoClientes[i].cantidadCompras = 0;
		}
	}
	return returnFunction;
}

/**
* \brief Obtiene el primer índice vacío del listado de clientes
* \param Cliente* listadoClientes Array de tipo Cliente del cual deseamos retornar primer índice vacío
* \param intlenClientes Tamaño del Array listadoClientes
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no encontró ningún índice vacío (-1)
* 			o el primer número de índice vacío (>=0)
*/
int cliente_buscarIndexEmtpy(Cliente* listadoClientes, int lenClientes)
{
	int returnFunction = -2;
	int i;
	if(listadoClientes != NULL && lenClientes > 0)
	{
		returnFunction = -1;
		for(i=0;i<lenClientes;i++)
		{
			if(listadoClientes[i].isEmpty == 1)
			{
				returnFunction = i;
				break;
			}
		}
	}
	return returnFunction;
}

/**
* \brief Crear una nueva entrada en el listado de clientes.
* \param Cliente* listadoClientes Array de tipo Cliente donde almacenaremos los datos
* \param int lenClientes Tamaño del Array listadoClientes
* \param int *contadorIdCliente Id del cliente proporcionado para asignar al nuevo cliente
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no pudo crear la entrada (-1)
* 			o EXITO (0)
*/
int cliente_altaCliente(Cliente* listadoClientes, int len, int* contadorIdCliente)
{
	int returnFunction = -2;
	int indiceEmpty;
	Cliente buffer;
	if(listadoClientes != NULL)
	{
		returnFunction = -1;
		system("clear");
		printf("ALTA CLIENTE\n"
				"‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
		if((indiceEmpty = cliente_buscarIndexEmtpy(listadoClientes, len)) >= 0)
		{
			if(get_name(buffer.nombre,32,"Ingrese el nombre del cliente: ","Error. ",3)==1 && strncmp(buffer.nombre,"",32)!=0)
			{
				if(get_name(buffer.apellido,32,"Ingrese el apellido del cliente: ","Error. ",3)==1 && strncmp(buffer.apellido,"",32)!=0)
				{
					if(get_cuit(buffer.cuit,"Ingrese el cuit (sin guiones): ","Cuit no válido. ",3)==1)
					{
						returnFunction = 0;
						listadoClientes[indiceEmpty].idCliente = *contadorIdCliente;
						strncpy(listadoClientes[indiceEmpty].nombre,buffer.nombre,32);
						strncpy(listadoClientes[indiceEmpty].apellido,buffer.apellido,32);
						strncpy(listadoClientes[indiceEmpty].cuit,buffer.cuit,12);
						listadoClientes[indiceEmpty].isEmpty = 0;
						*contadorIdCliente = *contadorIdCliente + 1;
						printf("\nNumero de identificador generado: %d\nPresione una tecla para continuar...",listadoClientes[indiceEmpty].idCliente);
						getchar();
					}
				}
				else
				{
					printf("Apellido no puede estar vacío.\nPresione cualquier tecla para continuar...");
					getchar();
				}
			}
			else
			{
				printf("Nombre no puede estar vacío.\nPresione cualquier tecla para continuar...");
				getchar();
			}
		}
		else
		{
			printf("No hay espacio disponible en el listado de Clientes. Comuniquese con el programador.");
		}

	}
	__fpurge(stdin);
	return returnFunction;
}

/**
* \brief Modifica una entrada del listado de clientes
* \param Cliente* listadoClientes Array de tipo Cliente donde se encuentra la entrada a modificar
* \param int lenClientes Tamaño del Array listadoClientes
* \param int idCliente Id del cliente a modificar
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no pudo modificar la entrada (-1)
* 			o EXITO (0)
*/
int cliente_modificarCliente(Cliente* listadoClientes, int lenClientes, int idCliente)
{
	int returnFunction = -2;
	int opcionElegida;
	int indiceDelId;
	Cliente buffer;
	if(listadoClientes != NULL && lenClientes > 0 && idCliente > 0)
	{
		returnFunction = -1;
		system("clear");
		printf("MODIFICAR CLIENTE\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
		cliente_imprimirListadoClientes(listadoClientes,lenClientes,"Listado de Clientes:\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
		printf("\n");
		if(get_int(&opcionElegida,4,"Seleccionar Cliente: ","Cliente no encontrado.\n",1,1,idCliente-1,3,0)==1)
		{
			indiceDelId = cliente_getIndexById(listadoClientes, lenClientes, opcionElegida);
			if(listadoClientes[indiceDelId].isEmpty == 0)
			{
				buffer.idCliente = opcionElegida;
				if(get_name(buffer.nombre,32,"\nIngrese el nombre del cliente: ","Error. ",3)==1 && strncmp(buffer.nombre,"",32) != 0)
				{
					if(get_name(buffer.apellido,32,"Ingrese el apellido del cliente: ","Error. ",3)==1 && strncmp(buffer.apellido,"",32) != 0)
					{
						if(get_cuit(buffer.cuit,"Ingrese el cuit (sin guiones): ","Cuit no válido. ",3)==1)
						{
							returnFunction = 0;
							strncpy(listadoClientes[indiceDelId].nombre,buffer.nombre,32);
							strncpy(listadoClientes[indiceDelId].apellido,buffer.apellido,32);
							strncpy(listadoClientes[indiceDelId].cuit,buffer.cuit,12);
						}
					}
					else
						{
							printf("Apellido no puede estar vacío.\nPresione cualquier tecla para continuar...");
							getchar();
						}
				}
				else
				{
					printf("Nombre no puede estar vacío.\nPresione cualquier tecla para continuar...");
					getchar();
				}
			}
			else
			{
				printf("Cliente no encontrado. \n");
				getchar();
			}
		}

	}
	__fpurge(stdin);
	return returnFunction;
}

/**
* \brief Imprime por pantalla el listado de clientes
* \param Cliente* listadoClientes Array de tipo Cliente a imprimir
* \param int lenClientes Tamaño del Array listadoClientes
* \param char* mensaje Puntero a dirección de memoria del mensaje a imprimir antes del listado.
* \return Devuelve ERROR de validación de entrada (-1)
* 			o EXITO (0)
*/
int cliente_imprimirListadoClientes(Cliente* listadoClientes, int len, char* mensaje)
{
	int returnFunction = -1;
	int i;
	if(listadoClientes != NULL && len > 0 && mensaje != NULL)
	{
		returnFunction = 0;
		printf("%s",mensaje);
		system("clear");
		printf("IMPRIMIR CLIENTES\n"
				"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
		for(i=0;i<len;i++)
		{
				if(listadoClientes[i].isEmpty == 0)
				{
					printf("Id %d) %s, %s - CUIT: %s - Compras: %d\n",listadoClientes[i].idCliente,
							listadoClientes[i].apellido,
							listadoClientes[i].nombre,
							listadoClientes[i].cuit,
							listadoClientes[i].cantidadCompras);
			}
		}
	}
	__fpurge(stdin);
	return returnFunction;
}

/**
* \brief Imprime por pantalla una posición del listado de clientes
* \param Cliente* listadoClientes Array de tipo Cliente a imprimir
* \param char* mensaje Puntero a dirección de memoria del mensaje a imprimir antes del cliente
* \param int indice Posición dentro del array del cliente a imprimir
* \return Devuelve ERROR de validación de entrada (-1)
* 			o EXITO (0)
*/
int cliente_imprimirClientePorIndice(Cliente* listadoClientes, char* mensaje,int indice)
{
	int returnFunction = -1;
	if(listadoClientes != NULL && mensaje != NULL && indice >= 0)
	{
		returnFunction = 0;
		printf("%s",mensaje);
		printf("\nId %d) %s, %s - CUIT: %s \n",listadoClientes[indice].idCliente,listadoClientes[indice].apellido,listadoClientes[indice].nombre,listadoClientes[indice].cuit);
	}
	return returnFunction;
}