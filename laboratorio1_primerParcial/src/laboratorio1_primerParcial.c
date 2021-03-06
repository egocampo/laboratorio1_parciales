/*
 ============================================================================
 Name        : laboratorio1_primerParcial.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Primer Parcial
 ============================================================================
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include "menues.h"
#include "gets.h"
#include "validations.h"
#include "cliente.h"
#include "compra.h"
#include "funcionesComunes.h"
#include "informes.h"
#define CANT_CLIENTES 100
#define CANT_COMPRAS 1000

int main(void) {
	Cliente listadoClientes[CANT_CLIENTES];
	Compra listadoCompras[CANT_COMPRAS];
	int contadorIdCliente = 1;
	int contadorIdCompra = 1;
	int opcionElegidaMenuPrincipal;
	char opcionElegidaSubmenuInformes;

	cliente_inicializarClientes(listadoClientes,CANT_CLIENTES);
	compra_inicializarCompras(listadoCompras,CANT_COMPRAS);

	do
	{
		opcionElegidaMenuPrincipal = 0;
		menu_imprimirMenuPrincipal();
		get_int(&opcionElegidaMenuPrincipal, 2,"¿Qué desea realizar? ","Esa no es una opción válida, intentelo nuevamente ",1,1,9,3,0);
		switch(opcionElegidaMenuPrincipal)
		{
			case 1:
				cliente_altaCliente(listadoClientes,CANT_CLIENTES,&contadorIdCliente);
				break;
			case 2:
				cliente_modificarCliente(listadoClientes, CANT_CLIENTES, contadorIdCliente);
				break;
			case 3:
				funcionesComunes_bajaCliente(listadoClientes, CANT_CLIENTES, contadorIdCliente,listadoCompras,CANT_COMPRAS);
				break;
			case 4:
				compra_altaCompra(listadoCompras, CANT_COMPRAS, listadoClientes, CANT_CLIENTES, &contadorIdCompra);
				break;
			case 5:
				compra_pagarCompra(listadoCompras, CANT_COMPRAS, contadorIdCompra, listadoClientes, CANT_CLIENTES);
				break;
			case 6:
				compra_cancelarCompra(listadoCompras, CANT_COMPRAS, contadorIdCompra, listadoClientes, CANT_CLIENTES);
				break;
			case 7:
				cliente_imprimirListadoClientesOpcion7(listadoClientes,CANT_CLIENTES,"\nLISTADO DE CLIENTES:\n\n");
				break;
			case 8:
				do
				{
					opcionElegidaSubmenuInformes = 0;
					menu_imprimirSubMenuInformes();
					get_char(&opcionElegidaSubmenuInformes, "abcdABCD",9,"Ingrese su opción: ","Opción no válida. ",3);
					switch(opcionElegidaSubmenuInformes)
					{
						case 'a':
							informes_colorBarbijoMasVeces(listadoCompras, CANT_COMPRAS);
							break;
						case 'b':
							informes_cantidadComprasPendientes(listadoCompras, CANT_COMPRAS);
							break;
						case 'c':
							informes_compraPrecioPorUnidadMasBajo(listadoCompras, CANT_COMPRAS);
							break;
					}
				}while(opcionElegidaSubmenuInformes != 'd' && opcionElegidaSubmenuInformes != 'D');
				break;
		}
	}while(opcionElegidaMenuPrincipal != 9);
	menu_imprimirMensajeDespedida();
	return EXIT_SUCCESS;
}
