/*
 * menues.c
 *
 *  Created on: 4 may. 2021
 *      Author: gabriel
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

void menu_imprimirMenuPrincipal(void)
{
	system("clear");
			printf("BARBIJOS GUTIERREZ S.R.L.\n"
					"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n"
					"MENU PRINCIPAL\n"
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
}

void menu_imprimirSubMenuInformes(void)
{
	system("clear");
	printf("Submenú de informes:\n"
			"‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n\n"
			"a) Color de barbijo que se compró mas veces.\n"
			"b) Cantidad de compras pendientes.\n"
			"c) Compra con precio por unidad mas bajo.\n"
			"d) Volver al Menú Principal.\n\n");
}

void menu_imprimirMensajeDespedida(void)
{
	system("clear");
	printf("\nSaliendo de la aplicación... ¡Hasta luego!\n"
			"\n"
			"     _________\n"
			"    / ======= \\ \n"
			"   / __________\\ \n"
			"  | ___________ | \n"
			"  | |         | | \n"
			"  | | GO-Prog | | \n"
			"  | |_________| | \n"
			"  \\=____________/ \n"
			"  / ''''''''''' \\ \n"
			" / ::::::::::::: \\ \n"
			"(_________________) \n"
			"\n"
			"\nSoftware desarrollado por:\n"
			"\n"
			"█▀▀ █▀█   █▀█ █▀█ █▀█ █▀▀\n"
			"█▄█ █▄█   █▀▀ █▀▄ █▄█ █▄█\n"
			"\n"
			"Buenos Aires, Argentina\n"
			"web: www.redactando.com.ar\n"
			"whatsapp: 11-2233-4455\n\n");


}

