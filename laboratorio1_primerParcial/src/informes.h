/*
 * informes.h
 *
 *  Created on: 30 abr. 2021
 *      Author: gabriel
 */

#ifndef INFORMES_H_
#define INFORMES_H_

typedef struct
{
	int idColor;
	char color[32];
	int cantidadCompras;
	int isEmpty;
}Colores;

int informes_inicializarColores(Colores* listadoColoresSinRepetir, int lenColores);
int informes_colorBarbijoMasVeces(Compra* listadoCompras, int lenCompras);
int informes_buscarIndexEmptyColores(Colores* listadoColores, int lenColores);
int informes_generarListadoColores(Compra* listadoCompras, int lenCompras, Colores* listadoColores);
int informes_contarComprasPorColor(Compra* listadoCompras, int lenCompras, Colores* listadoColores);
int informes_acumularComprasPorColor(Compra* listadoCompras, int lenCompras, Colores* listadoColores);
int informes_buscarIndiceMaximoColor(Colores* listadoCompras, int lenCompras);
int informes_ImprimirColorPorIndice(Colores* listadoColores, int lenColores,int indiceColorMasVendido);

int informes_cantidadComprasPendientes(Compra* listadoCompras, int lenCompras);
int informes_compraPrecioPorUnidadMasBajo(Compra* listadoCompras, int lenCompras);
int informes_calcularPreciosPorUnidad(Compra* listadoCompras, int lenCompras);
int informes_buscarPosicionDeMinimoPrecioPorUnidad(Compra* listadoCompras, int lenCompras,int* pPosicionRetorno);

#endif /* INFORMES_H_ */
