/*-----------------------------------------------------+
 |     U S H. C                                        
 +-----------------------------------------------------+
 |     Versi�n :                                       |                      
 |     Autor :                                         |
 |     Asignatura :  SOP-GIIROB                        |                               
 |     Descripci�n :                                   |
 +-----------------------------------------------------*/
#define _GNU_SOURCE
#include "defines.h"
#include "analizador.h"
#include "redireccion.h"
#include "ejecucion.h"
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "profe.h"

#include <stdio.h>
//#define PATH_MAX 50

//
// Declaraciones de funciones locales
//
void visualizar( void );
int leerLinea( char *linea, int tamanyLinea );


//
// Prog. ppal.
// 
int main(int argc, char * argv[])
{
    
  char line[255];
  int res;
  char **m_ordenes;
  char ***m_argumentos;
  int *m_num_arg;
  int m_n;

  while(1)
  {
    
    do
    {
        res=leerLinea(line,MAXLINE);
        if (res==-2){
      		fprintf(stdout,"logout\n");
            	exit(0);
        }
    	if (res==-1){
		   fprintf(stdout,"linea muy larga\n");
        }
     }while(res<0);

     if (analizar(line)==OK)
     {
	     m_n=num_ordenes();
	     m_num_arg=num_argumentos();
	     m_ordenes=get_ordenes();
	     m_argumentos=get_argumentos();
	     if(m_n>0)
	     {
                if (pipeline(m_n,fich_entrada(),fich_salida(),es_append(),es_background()) == OK) {
                    if(ejecutar(m_n,m_num_arg,m_ordenes,m_argumentos,es_background()) == ERROR) 
		   	return ERROR;
		} else 
		    return ERROR;         
    	     }
      visualizar();
    } 
 }    

  return 0;
}





/****************************************************************/
/*                       leerLinea                             
  --------------------------------------------------------------
                                                               
   DESCRIPCI�N:                                                 
   Obtiene la l�nea de �rdenes para el mShell.    
   Util para depuracion.                                        
                                                                
   ENTRADA:                                                 
    linea - puntero a un vector de car�cteres donde se almancenan los caracteres 
   le�dos del teclado
    tamanyLinea - tama�o m�ximo del vector anterior

   SALIDA:
    -- linea - si termina bien, contiene como �ltimo car�cter el retorno de carro.
    -- leerLinea -  Entero que representa el motivo de finalizaci�n de la funci�n:
     > 0 - terminaci�n correcta, n�mero de caracteres le�dos, inclu�do '\n'
     -1 - termina por haber alcanzado el n�mero m�ximo de caracteres que se 
    espera leer de teclado, sin encontrar '\n'.
     -2 - termina por haber le�do fin de fichero (EOF).
*/
/****************************************************************/
//char * getline(void)
int leerLinea( char *linea, int tamanyLinea )
{
  /*char path[PATH_MAX]; // array para guardar la ruta del directorio actual
  getcwd(path,PATH_MAX);
  printf("%s%s",path,PROMPT);*/
  printf("%s%s>",get_current_dir_name(),PROMPT);
  //printf("Shell-Alumno$>");
  int i = 0;
  while(i < tamanyLinea) {
    char c = getchar();
    if(c == EOF) {
      //printf("logout\n");
      return -2;
    }
    i++;
    *linea = c;
    linea++;
    if(c == '\n') {
      return i;
    }
  }
  if(i == tamanyLinea) {
    printf("ERROR. N�mero m�ximo de caracteres en l�nea alcanzado.\n");
    return -1;
  }
}




/****************************************************************/
/*                       visualizar                             */
/*--------------------------------------------------------------*/
/*                                                              */
/* DESCRIPCI�N:                                                 */
/* Visualiza los distintos argumentos de la orden analizada.    */
/* Util para depuracion.                                        */
/*                                                              */
/* ENTRADA: void                                                */
/*                                                              */
/* SALIDA: void                                                 */
/*                                                              */
/****************************************************************/
void visualizar( void )
{  
  printf("**********************************\n");
  printf("********   VISUALIZADOR   ********\n");
  printf("**********************************\n\n\n");
  printf("** ORDENES\n");
  int nord = num_ordenes();
  printf("** Numero de Ordenes : %d  \n", nord);
  if(!es_background())
    printf("** Orden en foreground\n");
  else
    printf("** Orden en background\n");
  int *narg = num_argumentos();
  //char **ordenes = get_ordenes();
  char ***argum = get_argumentos();
  for(int i=0;i < nord;i++) {
    printf("** Orden %d \n", i);
    for(int j=0;j < narg[i];j++)
      printf("**   Argumento %d --> %s \n", j, argum[i][j]);
  }
  printf("\n********************************** \n");
  printf("** REDIRECCION ENTRADA \n");
  printf("**  Redireccion entrada a --> %s\n", fich_entrada());
  printf("********************************** \n");
  printf("** REDIRECCION SALIDA \n");
  printf("**  Redireccion de salida a --> %s\n", fich_salida());
    if(strcmp(fich_salida(), "")) {
    	if(es_append())
      	printf("**    Es append\n");
    	else 
      	printf("**    Es trunc\n");
    }
  printf("********************************** \n\n");
} // Fin de "visualizar 



