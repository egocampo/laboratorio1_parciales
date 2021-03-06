/*
 * informes.c
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "gets.h"
#include "validations.h"
#include "cliente.h"
#include "compra.h"
#include "funcionesComunes.h"
#include "informes.h"
#define CANT_COMPRAS 1000
#define PENDIENTE 1
#define COBRADO 0

/*_| |____________________________________________| |__
(__   ____________________________________________   __)
   | |                                            | |
   | |                 INFORME A                  | |
 __| |____________________________________________| |__
(__   ____________________________________________   __)
   | |                                            | |*/

/**
* \brief Informa el color que se pidió en la mayor cantidad de Compras (OPCION A DEL SUBMENU)
* \param Compra* listadoCompras Array de tipo Compra donde buscar
* \param int lenCompras Tamaño del Array listadoCompras
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_colorBarbijoMasVeces(Compra* listadoCompras, int lenCompras)
{
	int returnFunction = -1;
	if(listadoCompras != NULL && lenCompras > 0)
	{
		returnFunction = 0;
		Colores listadoColores[lenCompras];
		informes_inicializarColores(listadoColores, lenCompras);
		informes_generarListadoColores(listadoCompras, lenCompras, listadoColores);
		informes_acumularComprasPorColor(listadoCompras, lenCompras, listadoColores);
//		informes_contarComprasPorColor(listadoCompras, lenCompras, listadoColores); // NO SABIA SI ERA CON CONTADOR O CON ACUMULADOR, HICE AMBAS
		informes_ImprimirColorPorIndice(listadoColores, lenCompras, informes_buscarIndiceMaximoColor(listadoColores, lenCompras));
	}
	return returnFunction;
}

/**
* \brief Completa el campo cantidad de compras de un listado de Compras
* \param Compra* listadoCompras Array de tipo Compra
* \param int lenCompras Tamaño del Array listadoCompras
* \param Colores* listadoColores Listado donde obtener valores únicos para comparar
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_acumularComprasPorColor(Compra* listadoCompras, int lenCompras, Colores* listadoColores)
{
	int returnFunction = -1;
	int i,j;
	if(listadoCompras != NULL && lenCompras > 0 && listadoColores != NULL)
	{
		returnFunction = 0;
		for(i=0;i<lenCompras;i++)
		{
			if(listadoColores[i].isEmpty == 0)
			{
				for(j=0;j<lenCompras;j++)
				{
					if(strncmp(listadoColores[i].color,listadoCompras[j].color,32) == 0)
					{
						(listadoColores[i].cantidadCompras) += (listadoCompras[j].cantidadDeBarbijos);
					}
				}
			}
		}
	}
	return returnFunction;
}

/**
* \brief Completa el campo cantidad de compras de un listado de Compras
* \param Compra* listadoCompras Array de tipo Compra
* \param int lenCompras Tamaño del Array listadoCompras
* \param Colores* listadoColores Listado donde obtener valores únicos para comparar
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_contarComprasPorColor(Compra* listadoCompras, int lenCompras, Colores* listadoColores)
{
	int returnFunction = -1;
	int i,j;
	if(listadoCompras != NULL && lenCompras > 0 && listadoColores != NULL)
	{
		returnFunction = 0;
		for(i=0;i<lenCompras;i++)
		{
			if(listadoColores[i].isEmpty == 0)
			{
				for(j=0;j<lenCompras;j++)
				{
					if(strncmp(listadoColores[i].color,listadoCompras[j].color,32) == 0)
					{
						(listadoColores[i].cantidadCompras)++;
					}
				}
			}
		}
	}
	return returnFunction;
}

/**
* \brief Inicializa el listado de Colores
* \param Colores* listadoColores Array de tipo Colores a inicializar
* \param int lenColores Tamaño del Array listadoColores
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_inicializarColores(Colores* listadoColores, int lenColores)
{
	int returnFunction = -1;
	int i;
	if(listadoColores != NULL && lenColores > 0)
	{
		returnFunction = 0;
		for(i=0;i<lenColores;i++)
		{
			strncpy(listadoColores[i].color,"",32);
			listadoColores[i].cantidadCompras = 0;
			listadoColores[i].isEmpty = 1;
		}
	}
	return returnFunction;
}

/**
* \brief Genera un listado de colores sin repetidos
* \param Compra* listadoCompras Array de tipo Compra para comparar valores
* \param int lenCompras Tamaño del Array listadoCompras
* \param Colores* listadoColores Array de tipo Colores con los valores unicos
* \param int* contadorIdColores Primer posición disponible del Array listadoColores para utilizar
* \return Devuelve ERROR de validación de entrada (-1),
* 			que el numero existe (1)
* 			o EXITO (0)
*/
int informes_generarListadoColores(Compra* listadoCompras, int lenCompras, Colores* listadoColores)
{
	int flagExiste = -1;
	int i,j;
	int primerIndiceVacioColores;
	if(listadoCompras != NULL && lenCompras > 0 && listadoColores != NULL)
	{
		for(i=0;i<lenCompras;i++)
		{
			flagExiste = 0;
			if(listadoCompras[i].isEmpty == 0)
			{
				for(j=0;j<lenCompras;j++)
				{
					if(strncmp(listadoCompras[i].color,listadoColores[j].color,32) == 0)
					{
						flagExiste = 1;
					}
				}
				if(flagExiste == 0)
				{
					primerIndiceVacioColores = informes_buscarIndexEmptyColores(listadoColores, lenCompras);
					strncpy(listadoColores[primerIndiceVacioColores].color,listadoCompras[i].color,32);
					listadoColores[primerIndiceVacioColores].isEmpty = 0;
				}
			}
		}
	}
	return flagExiste;
}

/**
* \brief Obtiene el primer índice vacío del listado de colores
* \param Colores* listadoColores Array de tipo Colores del cual deseamos retornar primer índice vacío
* \param int lenColores Tamaño del Array listadoColores
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no encontró ningún índice vacío (-1)
* 			o el primer número de índice vacío (>=0)
*/
int informes_buscarIndexEmptyColores(Colores* listadoColores, int lenColores)
{
	int returnFunction = -2;
	int i;
	if(listadoColores != NULL && lenColores > 0)
	{
		returnFunction = -1;
		for(i=0;i<lenColores;i++)
		{
			if(listadoColores[i].isEmpty == 1)
			{
				returnFunction = i;
				break;
			}
		}
	}
	return returnFunction;
}

/**
* \brief Busca el valor máximo de cantidad de compras de un color del listado de colores y devuelve su indice
* \param Colores* listadoColores Array de tipo Colores donde buscar
* \param int lenColores Tamaño del Array listadoColores
* \return Devuelve ERROR de validación de entrada (-2),
* 			que no encontró ningún índice vacío (-1)
* 			o el primer número de índice vacío (>=0)
*/
int informes_buscarIndiceMaximoColor(Colores* listadoColores, int lenColores)
{
	int indiceMaximoColor = -1;
	int i, valorMaximo;
	if(listadoColores != NULL && lenColores > 0)
	{
		indiceMaximoColor = 0;
		valorMaximo = listadoColores[0].cantidadCompras;
		for(i=0;i<lenColores;i++)
		{
			if(listadoColores[i].cantidadCompras > valorMaximo)
			{
				valorMaximo = listadoColores[i].cantidadCompras;
				indiceMaximoColor = i;
			}
		}
	}
	return indiceMaximoColor;
}

/**
* \brief Imprime el campo color de un elemento listado de colores por su indice
* \param Colores* listadoColores Array de tipo Colores donde buscar
* \param int lenColores Tamaño del Array listadoColores
* \param int indiceColorMasVendido Indice a imprimir
* \return Devuelve ERROR de validación de entrada (-1),
* 			que no encontró ningún índice vacío (-1)
* 			o el primer número de índice vacío (>=0)
*/
int informes_ImprimirColorPorIndice(Colores* listadoColores, int lenColores,int indiceColorMasVendido)
{
	int returnFunction = -1;
	if(listadoColores != NULL && lenColores > 0)
	{
		returnFunction = 0;
		system("clear");
		printf("Color de barbijo que se compró mas veces\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
		if(listadoColores[indiceColorMasVendido].isEmpty == 0)
		{
			printf("El color con mayor cantidad de compras es: %s con %d unidades vendidas\n\n",listadoColores[indiceColorMasVendido].color,listadoColores[indiceColorMasVendido].cantidadCompras);
		}
		else
		{
			printf("No se registró ninguna compra\n\n");
		}
		printf("Presione cualquier tecla para continuar...");
		getchar();
	}
	return returnFunction;
}

/*_| |____________________________________________| |__
(__   ____________________________________________   __)
   | |                                            | |
   | |                 INFORME B                  | |
 __| |____________________________________________| |__
(__   ____________________________________________   __)
   | |                                            | |*/

/**
* \brief Informa la cantidad de Compras en estado de pago Pendiente (OPCION B DEL SUBMENU)
* \param Compra* listadoCompras Array de tipo Compra donde buscar
* \param int lenCompras Tamaño del Array listadoCompras
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_cantidadComprasPendientes(Compra* listadoCompras, int lenCompras)
{
	int returnFuncion = -1;
	int i;
	int contadorComprasPendientes = 0;
	if(listadoCompras != NULL && lenCompras > 0)
	{
		returnFuncion = 0;
		system("clear");
		printf("Cantidad de compras en estado \"PENDIENTE\"\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].estadoDelCobro==PENDIENTE && listadoCompras[i].isEmpty == 0)
			{
				contadorComprasPendientes++;
			}
		}
		printf("La cantidad de compras pendientes es: %d\n\nPresione cualquier tecla para continuar...",contadorComprasPendientes);
		getchar();
	}
	return returnFuncion;
}

/*_| |____________________________________________| |__
(__   ____________________________________________   __)
   | |                                            | |
   | |                 INFORME C                  | |
 __| |____________________________________________| |__
(__   ____________________________________________   __)
   | |                                            | |*/

/**
* \brief Informa el precio por unidad mas bajo de las compras en estado COBRADO (OPCION C DEL SUBMENU)
* \param Compra* listadoCompras Array de tipo Compra donde realizar las operaciones
* \param int lenCompras Tamaño del Array listadoCompras
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_compraPrecioPorUnidadMasBajo(Compra* listadoCompras, int lenCompras)
{
	int returnFunction = -1;
	int indiceCompraPrecioPorUnidadMasBajo;
	if(listadoCompras != NULL && lenCompras > 0)
	{
		returnFunction = 0;
		informes_calcularPreciosPorUnidad(listadoCompras, lenCompras);
		informes_buscarPosicionDeMinimoPrecioPorUnidad(listadoCompras, lenCompras, &indiceCompraPrecioPorUnidadMasBajo);
		system("clear");
		printf("Compra con precio por unidad mas bajo\n‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n");
		if(listadoCompras[indiceCompraPrecioPorUnidadMasBajo].estadoDelCobro == COBRADO)
		{
			compra_imprimirCompraPorIndice(listadoCompras, indiceCompraPrecioPorUnidadMasBajo);
			printf(" -El importe abonado es: $ %.2f\n -El precio por unidad es: $ %.2f\n\n",listadoCompras[indiceCompraPrecioPorUnidadMasBajo].importePagado,listadoCompras[indiceCompraPrecioPorUnidadMasBajo].precioPorUnidad);
		}
		else
		{
			printf("No hay compras con estado \"COBRADA\".\n\n");
		}
		printf("Presione cualquier tecla para continuar...");
		getchar();
	}
	return returnFunction;
}

/**
* \brief Calcula el precio por unidad de cada compra de un listado de compras y lo almacena en el campo correspondiente
* \param Compra* listadoCompras Array de tipo Compra donde realizar las operaciones
* \param int lenCompras Tamaño del Array listadoCompras
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_calcularPreciosPorUnidad(Compra* listadoCompras, int lenCompras)
{
	int returnFunction = -1;
	int i;
	if(listadoCompras != NULL && lenCompras > 0)
	{
		returnFunction = 0;
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].isEmpty == 0 && listadoCompras[i].estadoDelCobro == COBRADO)
			{
				listadoCompras[i].precioPorUnidad = listadoCompras[i].importePagado / listadoCompras[i].cantidadDeBarbijos;
			}
		}
	}
	return returnFunction;
}

/**
* \brief Busca el mínimo precio por unidad de cada compra de un listado de compras y retorna el indice del mismo
* \param Compra* listadoCompras Array de tipo Compra donde buscar
* \param int lenCompras Tamaño del Array listadoCompras
* \param int* pPosicionRetorno Puntero a la dirección de memoria donde almacenar el indice obtenido
* \return Devuelve ERROR de validación de entrada (-1),
* 			o EXITO (0)
*/
int informes_buscarPosicionDeMinimoPrecioPorUnidad(Compra* listadoCompras, int lenCompras,int* pPosicionRetorno)
{
	int retorno = -1;
	int posicionDelMinimoPrecioPorUnidad;
	int i;
	int flagPrimero = 1;
	float minimoPrecioPorUnidad;
	if(listadoCompras != NULL && lenCompras > 0)
	{
		retorno = 0;
		for(i=0;i<lenCompras;i++)
		{
			if(listadoCompras[i].isEmpty == 0 && listadoCompras[i].estadoDelCobro == COBRADO)
			{
				if(flagPrimero == 1)
				{
					minimoPrecioPorUnidad = listadoCompras[i].precioPorUnidad;
					posicionDelMinimoPrecioPorUnidad = i;
					flagPrimero = 0;
				}
				else if(listadoCompras[i].precioPorUnidad < minimoPrecioPorUnidad)
				{
					minimoPrecioPorUnidad = listadoCompras[i].precioPorUnidad;
					posicionDelMinimoPrecioPorUnidad = i;
				}
			}
		}
		*pPosicionRetorno = posicionDelMinimoPrecioPorUnidad;
	}
	return retorno;
}





