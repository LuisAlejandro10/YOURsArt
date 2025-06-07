#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar strcpy

#define TAM 10 // Definición de la constante TAM para el tamaño de los arreglos

// Definición de las funciones del programa
int menu();
int menuproductos();
const char* agregarneme(int opc_menu);
void ingresardatos(FILE *estadoderesultados,void *productos[TAM][7], int opc_menu);
void mostrarproductos(void *productos[TAM][7], int opc_menu);
int verificarproductos(void *productos[TAM][7]);
void realizarventa(void *productos[TAM][7], FILE *estadoderesultados);
void ingresarproductosarchivo(FILE *archivo, void *productos[TAM][7], int opc_menu);
void registrarVentaEstadoResultados(FILE *estadoderesultados, const char *categoria, float precio, float precio_compra, const char *tipo, const char *genero);
void registrarCompraInventario(FILE *estadoderesultados, const char *categoria, float precio_compra, const char *tipo, const char *genero);
void mostrarEstadoResultados(FILE *estadoderesultados);

// Función para verificar si el código ya existe
// en el arreglo de productos
int codigoExistente(void *productos[TAM][7], int codigo) {
    for (int i = 0; i < TAM; i++) {
        if (productos[i][3] != NULL) {
            if (*(int *)productos[i][3] == codigo) {
                return 1; // El código ya existe
            }
        }
    }
    return 0; // El código no existe
}		


int main(void) { // Función principal
    FILE *archivo; // Archivo para guardar los productos
    FILE *estadoderesultados;
    int opc = 1, opc_menu = 0;
    void *productos[TAM][7];
    int opc_salir = 0;

    archivo = fopen("productos.txt", "w+"); // Abrir el archivo en modo de lectura y escritura
    if (archivo == NULL) {
        printf("Error al abrir el archivo de productos\n");
        return 1;
    }

    estadoderesultados = fopen("estadoderesultados.txt", "w+");
    if (estadoderesultados == NULL) {
        printf("Error al abrir el archivo de estado de resultados\n");
        fclose(archivo);
        return 1;
    }

    // Inicializar el arreglo de punteros a NULL
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < 7; j++) {
            productos[i][j] = NULL;
        }
    }

    do { // Bucle principal del menú
        switch (menu()) {
            case 1:
            	//int opc_salir = 0;
               do{ // Bucle para agregar productos
                
            	system("cls");
                opc_menu = menuproductos();
                switch (opc_menu) {
                    case 1:
                        system("cls"); // Limpiar la pantalla
                        printf("\n========== Playeras ==========\n");
                        
                        ingresardatos(estadoderesultados,productos, opc_menu); // Llamar a la función para ingresar datos
                        ingresarproductosarchivo(archivo, productos, opc_menu); // Llamar a la función para ingresar productos al archivo
                        /*system("pasue");
                        system("cls");*/
          
                        break;
                    case 2:
                        system("cls");
                        printf("============= Pantalones ==============\n");
                        ingresardatos(estadoderesultados,productos, opc_menu);
                        ingresarproductosarchivo(archivo, productos, opc_menu);
                        //system("cls");
        
                        break;
                    case 3:
                        system("cls");
                        printf("========== Sudaderas ==========\n");
                        ingresardatos(estadoderesultados,productos, opc_menu);
                        ingresarproductosarchivo(archivo, productos, opc_menu);
                        break;
                    case 4:
                        system("cls");
                        printf("========== Accesorios ==========\n");
                        ingresardatos(estadoderesultados,productos, opc_menu);
                        ingresarproductosarchivo(archivo, productos, opc_menu);
                        break;
                    default:
                        system("cls");
                        printf("========== ERROR ==========\n");
                        printf("Opci%cn no v%clida\n",162,160);
                        printf("Regresando al menú...\n");
                        menu();
                        break;
                }
                printf("Desea agregar otro producto? (1. S%c  2. No): ",161);
                scanf("%d", &opc_salir);
                if (opc_salir == 1) {
                    printf("Regresando al men%c...\n",163);
                    //system("pause");
                    opc_salir = 1;
                    //system("cls");
                            
                }else{
                    printf("Saliendo...\n");
                    printf("Regresando al men%c...\n",163);
         
                    opc_salir = 2;
                }
            }while (opc_salir != 2);
                break;
            case 2:{
				
            	int otr_venta = 0;
            	do{
					system("cls");
                	printf("========== Realizar una venta ==========\n");
                	if (verificarproductos(productos) == 0) {
                    	printf("No hay productos disponibles\n");
                       
                        otr_venta = 2;                        
                	} else {
                    	system("cls");
                    	realizarventa(productos, estadoderesultados);
                    	printf("Desea realizar otra venta (1.S%c 2.No): ",161);
                    	while(scanf("%d",&otr_venta) == 0){
                    		printf("Error: Ingrese una opci%cn v%clida (seleccione un numero): ",162,160);
        					while (getchar() != '\n');
						}
                	}
            	}while(otr_venta != 2);
            	system("pause");
                break;
            }
            case 3:
            	system("cls");
                printf("========== Mostrando productos ==========\n");
                if (verificarproductos(productos) == 0) {
                    printf("No hay productos disponibles\n");
                    printf("Regresando al men%c...\n",163);
                    system("pause");
                } else {
                    mostrarproductos(productos, opc_menu);
                    printf("Regresando al men%c...\n",163);
                    system("pause");
                    //system("cls")
                }
                break;
            
            case 4:
            	system("cls");
                printf("========== Mostrar estado de resultados ==========\n");
                printf("\n");
                mostrarEstadoResultados(estadoderesultados);
                printf("Regresando al men%c...\n",163);
                system("pause");
                break;
            case 5:
                printf("Seguro que desea salir (1. S%c  2. No): ",161);
                scanf("%d", &opc);
                if (opc == 1) { // Si elige salir
                    printf("Saliendo...\n");
                    opc = 0;
                } else {
                    printf("Regresando al menú...\n");
                    opc = 1;
                }
                break;
            default:
                printf("Opci%cn no v%clida\n",162,160);
                break;
        }
    } while (opc != 0);

    // Liberar memoria antes de salir
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < 7; j++) {
            if (productos[i][j] != NULL) {
                free(productos[i][j]);
            }
        }
    }

    fclose(archivo);// Cerrar el archivo de productos
    fclose(estadoderesultados);// Cerrar el archivo de estado de resultados
    printf("Gracias por usar el programa :)\n");
    return 0;
}

int menu() { // Función para mostrar el menú principal
    system("cls");
    int opc;
    printf("\n=============== YOURS ART ===============\n");
    printf("1. Agregar un producto\n");
    printf("2. Realizar una venta\n");
    printf("3. Mostrar productos\n");
    printf("4. Mostrar estado de resultados\n");
    printf("5. Salir\n");
    printf("========================================\n");
    printf("Elige una opci%cn: ", 162);
    while(scanf("%d", &opc) == 0){
        printf("Error: Ingrese una opci%cn v%clida: ",162,160);
        while (getchar() != '\n'); // Limpiar el buffer de entrada
    }
    return opc;
}

int menuproductos() { // Función para mostrar el menú de productos
    int opc;
    printf("=========== TIPO DE PRODUCTO ===========\n");
    printf("1. Playeras\n");
    printf("2. Pantalones\n");
    printf("3. Sudaderas\n");
    printf("4. Accesorios\n");
    printf("========================================\n");
    printf("Elige una opci%cn: ", 162);
    while(scanf("%d", &opc)== 0){ // Validar la entrada
        printf("Error: Ingrese una opci%cn v%clida (seleccione un numero): ",162,160);
        while (getchar() != '\n'); // Limpiar el buffer de entrada
    }
    while(opc < 1 || opc > 4){ // Validar la opción
    	printf("Error: ingrese una opci%cn v%clida: ",162,160);
    	while(scanf("%d", &opc) == 0){
    	printf("Error: Ingrese una opci%cn v%clida (seleccione un numero): ",162,160);
        while (getchar() != '\n');
    		
		}
	}
    return opc;
}


const char* agregarneme(int opc_menu) { // Cambié el nombre de la función a agregarneme
    switch (opc_menu) {
        case 1: return "Playeras"; 
        case 2: return "Pantalones";
        case 3: return "Sudaderas";
        case 4: return "Accesorios";
        default:
           // printf("Opci%cn no v%clidaaaa\n",162,160);
            return NULL; // Retornar NULL si la opción no es válida
    }
}

void ingresardatos(FILE *estadoderesultados ,void *productos[TAM][7], int opc_menu) {
    int tamP = 0, pid;
    const char *name = agregarneme(opc_menu); // Cambié el nombre de la variable a name
    if (name == NULL) return;

    int start = 0;
    while (start < TAM && productos[start][0] != NULL) start++;
    if (start == TAM) { // Verificar si el inventario está lleno
        printf("El inventario está lleno. No se pueden agregar más productos.\n");
        return;
    }

    printf("%cCu%cntos productos desea ingresar? (m%cximo %d): ",168,160,160, TAM - start);
    while(scanf("%d", &tamP) == 0){
        printf("Error: Ingrese un n%cmero v%clido: ",163,160);
        while (getchar() != '\n'); // Limpiar el buffer de entrada
    }
    while (tamP > (TAM - start) || tamP <= 0) {
        printf("El n%cmero debe estar entre 1 y %d. Ingrese un nuevo valor: ",163, TAM - start);
        while(scanf("%d", &tamP) == 0){
        	 printf("Error: Ingrese un n%cmero v%clido: ",163,160);
        	while (getchar() != '\n');
        	
		}
    }

    if(tamP > 1){
        printf("\nSon todos estos productos iguales? (1. S%c  2. No): ",161);
        while(scanf("%d", &pid)==0){
        	printf("Error: Ingrese un n%cmero v%clido: ",163,160);
        	while (getchar() != '\n');
		}   
    }

    
	// Definir variables para almacenar los datos del producto
    char  cat_tmp[25];
    float precio_tmp;
    char   talla_tmp[25];
    int   codigo_tmp;
    float preciocompra_tmp = 0.0;
    float precio_compra_tmp;
    char tipo_tmp[25];
    char genero_tmp[25];

    for (int i = 0; i < tamP; i++) {
        int idx = start + i;

        productos[idx][0] = malloc(25 * sizeof(char));//Asignar memoria en el arreglo
        if (productos[idx][0] == NULL) { // Verificar si la memoria se asignó correctamente o si no hay espacio
            printf("Error al asignar memoria\n");
            return;
        }
        productos[idx][1] = malloc(sizeof(float));
        if (productos[idx][1] == NULL) {
            printf("Error al asignar memoria\n");
            free(productos[idx][0]);
            return;
        }
        productos[idx][2] = malloc(25 * sizeof(char));
        if (productos[idx][2] == NULL) {
            printf("Error al asignar memoria\n");
            free(productos[idx][0]);
            free(productos[idx][1]);
            return;
        }
        productos[idx][3] = malloc(sizeof(int));
        if (productos[idx][3] == NULL) {
            printf("Error al asignar memoria\n");
            free(productos[idx][0]);
            free(productos[idx][1]);
            free(productos[idx][2]);
            return;
        }
        productos[idx][4] = malloc(sizeof(float));
        if (productos[idx][4] == NULL) {
            printf("Error al asignar memoria\n");
            free(productos[idx][0]);
            free(productos[idx][1]);
            free(productos[idx][2]);
            free(productos[idx][3]);

            return;
        }
        productos[idx][5] = malloc(25 * sizeof(char));
        if (productos[idx][5] == NULL) {
            printf("Error al asignar memoria\n");
            free(productos[idx][0]);
            free(productos[idx][1]);
            free(productos[idx][2]);
            free(productos[idx][3]);
            free(productos[idx][4]);

            return;
        }
        productos[idx][6] = malloc(25 * sizeof(char));
        if (productos[idx][6] == NULL) {
            printf("Error al asignar memoria\n");
            free(productos[idx][0]);
            free(productos[idx][1]);
            free(productos[idx][2]);
            free(productos[idx][3]);
            free(productos[idx][4]);
            free(productos[idx][5]);

            return;
        }
        
        // Verificar si la memoria se asignó correctamente
        if (!productos[idx][0] || !productos[idx][1] || !productos[idx][2] || !productos[idx][3] || !productos[idx][4] || !productos[idx][5]) { // Verificar si la memoria se asignó correctamente
            printf("Error al asignar memoria\n");
            exit(1);
        }

        // Verificar si el producto ya existe
        if (opc_menu == 1){
            strcpy(tipo_tmp, "Playera");
        } else if (opc_menu == 2){
            strcpy(tipo_tmp, "Pantalon");
        } else if (opc_menu == 3){
            strcpy(tipo_tmp, "Sudadera");
        } else if (opc_menu == 4){
            strcpy(tipo_tmp, "Accesorio");
        } else {
            printf("Error: Tipo de producto no válido\n");
            return;
        }

        printf("========== %s %d ==========\n", name, i + 1);   // Mostrar el nombre del producto y su número
        printf("\n");

        if (i == 0 || pid == 2) { // Si es el primer producto o el usuario indica que son diferentes
            if(opc_menu == 4){ // Si es un accesorio
                printf("=====Categor%ca del producto=====\n",161);
                printf("Gorra\n");
                printf("Bufanda\n");
                printf("Cintur%cn\n",162);
                printf("Gafas\n");
                printf("Reloj\n");
                printf("============================\n");
            } else { // Si es una playera, pantalón o sudadera
                
            	printf("=====Categor%ca del producto=====\n",161);
                printf("Basico\n");
                printf("Deportivo\n");
                printf("Elegante\n");
                printf("Casual\n");
                printf("============================\n");
            }
    	
          
        // Validar la categoría        
        int categoria_search = 0;  // Inicializar ambas variables
        const char *categoriasM[] = {"Basico", "Deportivo", "Elegante", "Casual", "Gorra", "Bufanda", "Cintur%cn", "Gafas", "Reloj"};
        const char *categoriami[] = {"basico", "deportivo", "elegante", "casual", "gorra", "bufanda", "cintur%cn", "gafas", "reloj"};

        printf("\nIngrese la categor%ca del producto: ", 161);
        fflush(stdin);
        fgets(cat_tmp,sizeof(cat_tmp),stdin);// Cambié gets por fgets para evitar problemas de buffer
        cat_tmp[strcspn(cat_tmp, "\n")] = 0; // Eliminar el salto de línea al final
        
        for (int i = 0; i < 9; i++){
            if(strcmp(cat_tmp, categoriasM[i]) == 0 || strcmp(cat_tmp, categoriami[i]) == 0){
                categoria_search = 1;
                break;
            }
        }
        while(categoria_search == 0){ // Validar la categoría
            printf("Error: Ingrese una categor%ca v%clida: ",161,160);
            fgets(cat_tmp,sizeof(cat_tmp),stdin);
            cat_tmp[strcspn(cat_tmp, "\n")] = 0; // Eliminar el salto de línea al final
            for (int i = 0; i < 9; i++){
                if(strcmp(cat_tmp, categoriasM[i]) == 0 || strcmp(cat_tmp, categoriami[i]) == 0){
                    categoria_search = 1;
                }
            }
        }  
        printf("\n========== Genero del producto ==========\n"); //Mostrar el género del producto
        printf(" - Hombre\n");
        printf(" - Mujer\n");
        //printf(" - Ni%co\n",164);
        printf(" - Infantil\n",164);
        printf("========================================\n");
        
        int genero_search = 0;
        const char *generosM[] = {"Hombre", "Mujer", "Infantil" }; // Arreglo de géneros
        const char *generosmi[] = {"hombre", "mujer", "infantil"};
        printf("\nIngrese el genero del producto: ");
        fflush(stdin);
        fgets(genero_tmp,sizeof(genero_tmp),stdin);
        genero_tmp[strcspn(genero_tmp, "\n")] = 0; // Eliminar el salto de línea al final
        for (int i = 0; i < 3; i++){
            if(strcmp(genero_tmp, generosM[i]) == 0 || strcmp(genero_tmp, generosmi[i]) == 0){
                genero_search = 1;
        
            }
        
        }
        while(genero_search == 0){
            printf("Error: Ingrese un genero v%clido: ",160);
            fflush(stdin);
            fgets(genero_tmp,sizeof(genero_tmp),stdin);
            genero_tmp[strcspn(genero_tmp, "\n")] = 0; // Eliminar el salto de línea al final
            for (int i = 0; i < 3; i++){
                if(strcmp(genero_tmp, generosM[i]) == 0 || strcmp(genero_tmp, generosmi[i]) == 0){
                    genero_search = 1;
                }
            }
        }
        

        printf("\n========== Gu%ca de tallas ==========:\n",161); // Mostrar la guía de tallas
        printf(" - Talla S\n");
        printf(" - Talla M\n");
        printf(" - Talla L\n");
        printf(" - Talla Unisex\n");
        printf("============================\n");

            // Validar la talla
        int talla_search = 0;  // Inicializar ambas variables
        const char *tallas[] = {"S", "M", "L", "Unisex"};
        const char *tallasmi[] = {"s", "m", "l", "unisex"};
        printf("\nIngrese la talla del producto: ");
        fgets(talla_tmp,sizeof(talla_tmp),stdin);
        talla_tmp[strcspn(talla_tmp, "\n")] = 0;

        for (int i = 0; i < 4; i++){
            if(strcmp(talla_tmp, tallas[i]) == 0 || strcmp(talla_tmp, tallasmi[i]) == 0){
                talla_search = 1;
            }
            
        }
        while(talla_search == 0){
            printf("Error: Ingrese una talla v%clida: ",160);
            fgets(talla_tmp,sizeof(talla_tmp),stdin);
            talla_tmp[strcspn(talla_tmp, "\n")] = 0;
            for (int i = 0; i < 4; i++){
                if(strcmp(talla_tmp, tallas[i]) == 0 || strcmp(talla_tmp, tallasmi[i]) == 0){
                    talla_search = 1;
                }
            }
        }    
            do{
                printf("\nIngrese C%cdigo (0-9999): ",162);
                scanf("%d", &codigo_tmp);

                while(codigo_tmp < 0 || codigo_tmp > 9999){
                    printf("Error: Ingrese un c%cdigo v%clido (0-9999): ",162,160);
                    scanf("%d", &codigo_tmp);
                }
 
                if (codigoExistente(productos, codigo_tmp)) {
                   printf("\nEse c%cdigo ya existe. Ingrese uno diferente.\n",162);
                }

            }while (codigoExistente(productos, codigo_tmp));

            printf("\nIngrese el precio de venta del producto (Vender): ");
            scanf("%f", &precio_tmp);
            while(precio_tmp<0){
            printf ("Error no se pueden agregar n%cmeros negativos",163);
            printf("\nIngrese el precio de venta del producto (Vender): ");
            scanf("%f", &precio_tmp);
            }

            printf("\ningresa el precio de compra del producto: ");
            scanf("%f", &preciocompra_tmp);
            while(preciocompra_tmp<0){
            printf ("Error no se pueden agregar n%cmeros negativos\n",163);
            printf("\ningresa el precio de compra del producto: ");
            scanf("%f", &preciocompra_tmp);
            }

            precio_compra_tmp += preciocompra_tmp; 

        } else {
            printf("Producto dupl%ccado: usando m%csma categor%ca, precio, talla y precio de compra.\n",161,161,161);
            codigo_tmp++;
            printf("Se asigna c%cdigo autom%cticamente: %d\n",163,160, codigo_tmp);
        }

        strcpy((char *)productos[idx][0], cat_tmp);
        *(float *)productos[idx][1] = precio_tmp;
        strcpy((char *)productos[idx][2], talla_tmp);
        *(int   *)productos[idx][3] = codigo_tmp;
        *(float *)productos[idx][4] = preciocompra_tmp;
        strcpy((char *)productos[idx][5], tipo_tmp); 
        strcpy((char *)productos[idx][6], genero_tmp); 

        registrarCompraInventario(estadoderesultados, cat_tmp, preciocompra_tmp, tipo_tmp, genero_tmp);

        printf("\nProducto agregado exitosamente.\n");
        printf("========================================\n");

        

    }
}

void ingresarproductosarchivo(FILE *archivo, void *productos[TAM][7], int opc_menu) {
    const char *productoname = agregarneme(opc_menu);
    if (productoname == NULL) return;

    fprintf(archivo, "========== %s ==========\n", productoname);
    fprintf(archivo,"\n");
    for (int i = 0; i < TAM; i++) {
        if (productos[i][0] != NULL) {
            fprintf(archivo, "Producto: %s\n", (char *)productos[i][5]);
            fprintf(archivo, "Categor%ca: %s\n",161, (char *)productos[i][0]);
            fprintf(archivo, "Genero: %s\n", (char *)productos[i][6]);
            fprintf(archivo, "Precio: %.2f\n", *(float *)productos[i][1]);
            fprintf(archivo, "Talla: %s\n", (char *)productos[i][2]);
            fprintf(archivo, "Código: %d\n", *(int *)productos[i][3]);
            fprintf(archivo, "Precio de compra: %.2f\n", *(float *)productos[i][4]);
            fprintf(archivo, "===========================\n");
        }
    }
}

void mostrarproductos(void *productos[TAM][7], int opc_menu) { 
    if (opc_menu == 0){
        printf("========== MOSTRANDO TODOS LOS PRODUCTOS ==========\n");
    } 
    printf("\n");

    for (int i = 0; i < TAM; i++) { // Mostrar todos los productos
        if (productos[i][0] != NULL) {
            printf("Producto: \t\t %s\n", (char *)productos[i][5]); // Mostrar el nombre del producto
            printf("Categor%ca: \t\t %s\n",161, (char *)productos[i][0]);
            printf("Genero: \t\t %s\n", (char *)productos[i][6]);
            printf("Talla: \t\t\t %s\n", (char *)productos[i][2]);
            printf("C%cdigo: \t\t %d\n",162, *(int *)productos[i][3]);
            printf("Precio de venta: \t $%.2f\n", *(float *)productos[i][1]);
            printf("Precio de compra: \t $%.2f\n", *(float *)productos[i][4]);
            printf("================================\n");
        }
    }
}

int verificarproductos(void *productos[TAM][7]) { // Verificar si hay productos disponibles
    for (int i = 0; i < TAM; i++) {
        if (productos[i][0] != NULL) return 1;
    }
    return 0;
}

void realizarventa(void *productos[TAM][7], FILE *estadoderesultados) { //
    int codigobuscar, encontrado = 0;
    
    printf("========== Productos disponibles ==========\n");
    printf("\n");
    mostrarproductos(productos, 0); // Mostrar todos los productos disponibles

    printf("Ingrese el c%cdigo del producto que desea vender: ",162);
    scanf("%d", &codigobuscar);

    for (int i = 0; i < TAM; i++) {
        if (productos[i][3] != NULL && *(int *)productos[i][3] == codigobuscar) {
            printf("\n========== Producto encontrado ==========\n");
            printf("\nProducto: \t\t%s\n", (char *)productos[i][5]);
            printf("Genero: \t\t%s\n", (char *)productos[i][6]);
            printf("Categor%ca: \t\t%s\n",161, (char *)productos[i][0]);
            printf("Precio:  \t\t%.2f\n", *(float *)productos[i][1]);
            printf("Talla: \t\t\t%s\n", (char *)productos[i][2]);

            registrarVentaEstadoResultados(estadoderesultados, (char *)productos[i][0], *(float *)productos[i][1], *(float *)productos[i][4], (char *)productos[i][5], (char *)productos[i][6]);

            for (int j = 0; j < 7; j++) {
                free(productos[i][j]);
                productos[i][j] = NULL;
            }

            printf("Venta realizada exitosamente.\n");
            encontrado = 1;
            //break;
        }
    }

    if (encontrado == 0) {
        printf("Producto no encontrado con ese c%cdigo.\n",162);
    }
    
}

void registrarVentaEstadoResultados(FILE *estadoderesultados, const char *categoria, float precio, float precio_compra, const char *tipo, const char *genero) {
    fprintf(estadoderesultados, "========== Venta Realizada ==========\n");
    fprintf(estadoderesultados, "Producto: \t\t %s\n", tipo);
    fprintf(estadoderesultados, "Genero: \t\t %s\n", genero);
    fprintf(estadoderesultados, "Categor%ca: \t\t %s\n",161, categoria);
    fprintf(estadoderesultados, "Precio: \t\t %.2f\n", precio);
    fprintf(estadoderesultados, "Costo:  \t\t %.2f\n", precio_compra);
    fprintf(estadoderesultados, "Ganacias: \t\t %.2f\n", precio - precio_compra);
    fprintf(estadoderesultados, "===========================\n");
}

void registrarCompraInventario(FILE *estadoderesultados, const char *categoria, float precio_compra, const char *tipo, const char *genero) { 
    fprintf(estadoderesultados, "============ Inventario ===========\n");
    fprintf(estadoderesultados, "Producto: \t\t %s\n", tipo);
    fprintf(estadoderesultados, "Genero: \t\t %s\n", genero);
    fprintf(estadoderesultados, "Categor%ca: \t\t %s\n",161, categoria);
    fprintf(estadoderesultados, "Costo inventario: \t %.2f\n", precio_compra);
    fprintf(estadoderesultados, "===========================\n");
    fprintf(estadoderesultados, "\n");
}

void mostrarEstadoResultados(FILE *estadoderesultados) {
    rewind(estadoderesultados); // Volver al inicio del archivo
    char linea[256]; // Buffer para leer líneas del archivo
    float totalIngresos = 0.0; // Inicializar variables
    float totalCostos = 0.0;
    float totalGanancias = 0.0;
    float Totalgastosinventario = 0.0;

    printf("============ Estado de Resultados ============\n");
    printf("\n");
    while (fgets(linea, sizeof(linea), estadoderesultados)) { // Leer línea por línea
        printf("%s", linea);
        if (strncmp(linea, "Precio:", 7) == 0) { // Comparar con "Precio:"  
            float precio;
            sscanf(linea, "Precio: %f", &precio); // Leer el precio
            totalIngresos += precio;
        }
        if (strncmp(linea, "Costo:", 6) == 0) { // Comparar los primeros 6 caracteres de la linea con "Costo:"
            float costo;
            sscanf(linea, "Costo: %f", &costo);
            totalCostos += costo;
        }
        if (strncmp(linea, "Costo inventario:", 17) == 0) {
            float costoInventario;
            sscanf(linea, "Costo inventario: %f", &costoInventario);
            Totalgastosinventario += costoInventario;
        }
    }
    totalGanancias = totalIngresos - totalCostos;

    
    
    // Mostrar el resumen financiero
    printf("\n========= Resumen financiero =========\n");
    printf("Total de ingresos: \t\t %.2f\n", totalIngresos);
    printf("Total de costos(por producto): \t %.2f\n", totalCostos);
    printf("Total de ganancias neta: \t %.2f\n", totalGanancias);
    printf("Total de gastos: \t\t %.2f\n", Totalgastosinventario);
    printf("========================================\n");
}
    