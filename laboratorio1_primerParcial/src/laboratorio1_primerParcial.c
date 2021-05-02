/*
 ============================================================================
 Name        : laboratorio1_primerParcial.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Parcial
 ============================================================================
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
#define CANT_CLIENTES 100
#define CANT_COMPRAS 1000

int main(void) {
	Cliente listadoClientes[CANT_CLIENTES];
	Compra listadoCompras[CANT_COMPRAS];
	int contadorIdCliente = 2; // harcodeado, volver a 1 !!!!!!
	int contadorIdCompra = 1;
	int opcionElegidaMenuPrincipal;
	char opcionElegidaSubmenuInformes;

	cliente_inicializarClientes(listadoClientes,CANT_CLIENTES);
	compra_inicializarCompras(listadoCompras,CANT_COMPRAS);

	listadoClientes[0].idCliente = 1;
	strncpy(listadoClientes[0].nombre,"Gabriel",32);
	strncpy(listadoClientes[0].apellido,"Ocampo",32);
	strncpy(listadoClientes[0].cuit,"23328116979",12);
	listadoClientes[0].isEmpty = 0;

	do
	{
		opcionElegidaMenuPrincipal = 0;
		system("clear");
		printf("BARBIJOS GUTIERREZ S.R.L.\n"
				"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n");
		printf("MENU PRINCIPAL\n"
				"‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n"
				"1) ALTA Cliente\n"
				"2) MODIFICAR Cliente\n"
				"3) BAJA Cliente\n"
				"4) Realizar Compra\n"
				"5) Pagar Venta\n"
				"6) Cancelar compra\n"
				"7) Imprimir Clientes\n"
				"8) Menú Informes\n"
				"9) Salir del programa\n\n");
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
				cliente_imprimirListadoClientes(listadoClientes,CANT_CLIENTES,"\nLISTADO DE CLIENTES:\n\n");
				printf("\nPresione cualquier tecla para continuar...");
				getchar();
				break;
			case 8:
				do
				{
					system("clear");
					printf("Submenú de informes:\n"
							"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n"
							"a) Color de barbijo que se compró mas veces.\n"
							"b) Cantidad de compras pendientes.\n"
							"c) Compra con precio por unidad mas bajo.\n"
							"d) Volver al Menú Principal.\n\n");
					opcionElegidaSubmenuInformes = 0;
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
	printf("\nSaliendo de la aplicación ¡Hasta luego!\n\nSoftware desarrollado por EGOProg\nwww.redactando.com.ar\n");
	return EXIT_SUCCESS;
}
