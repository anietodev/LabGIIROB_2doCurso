/*!
	practica7.cpp

	Programa que crea un entorno geom�trico plano con objetos sobre �l 
	donde se puede mover acelerando, desacelerando y rotando con las 
	flechas del teclado. En el caso de movimiento hacia atr�s, los 
	giros cambian de sentido (como en un coche).

	@author		Andrea Nieto Gil' <aniegil@upv.edu.es>
	@date		April,2024
 */

#define PROYECTO "practica7"

#include <iostream>	
#include <codebase.h>

using namespace std;
using namespace cb;

// Constantes

// Coordenada maxima del plano xy
#define COORXY	100.0F
// Longitud del contenedor
#define LONG_CONT	2.0F
// Ancho del contenedor
#define ANCHO_CONT	4.0F

// Globales

// Velocidad de simulaci�n 
static const int tasaFPS = 60;

static enum { ALAMBRICO, SOLIDO, DOBLE } modo;
// NOMOV(NO Movement) y NOROT(NO Rotation) indican que no se ha pulsado flecha
static enum { NOMOV, UP, DOWN } direccion;
static enum { NOROT, RIGHT, LEFT } rotacion;

static Vec3 camPosition(0.0f, 0.0f, 1.0f);
static Vec3 camLookAt(0.0f, 1.0f, 1.0f);
static float giroxTR = 0, giroyTR = 0, giroxTA = 0, giroyTA = 0;
int xanterior, yanterior;
static float alfav = 0.0f;	// �
static float vel   = 0.0f;	// km/h
// Vector con desplazamiento actual (magnitud) y direccion actual (angulo)
static float posAct[2] = {vel, 90.0f};	// Empezamos con 0 desplazamiento y angulo 90
GLubyte objeto[1];
static bool luces_fijas = false; // Para activar/desactivar el dibujado de las luces fijas


// Clase contenedor para instanciar un contenedor con sus parametros
class contenedor
{
private:
	float longitud;
	float ancho;
	Vec3 pos_eje;

	// Funcion que dibuja la cara de un contenedor
	void cara()
	{
		glBegin(GL_QUAD_STRIP);

		GLfloat v0[3] = {0.0f, 0.0f, 0.0f}, v1[3] = { 0.0f, longitud, 0.0f},
			v2[3] = { ancho, 0.0f, 0.0f }, v3[3] = { ancho, longitud, 0.0f };
		quad(v0, v1, v2, v3, 10.0f);
		/*
		glVertex3f(0, 0, 0);
		glVertex3f(ancho, 0, 0);
		glVertex3f(0, longitud, 0);
		glVertex3f(ancho, longitud, 0);
		glVertex3f(0, 0, 0);
		*/
		glEnd();
	}

	// Funcion que dibuja las uniones de un contenedor
	void uniones()
	{
		glBegin(GL_QUAD_STRIP);

		glVertex3f(0, 0, 0);
		glVertex3f(ancho, 0, 0);
		glVertex3f(0, ancho, 0);
		glVertex3f(ancho, ancho, 0);
		glVertex3f(0, 0, 0);

		glEnd();
	}


public:

	// Constructor que instancia contenedor asignandole sus parametros
	contenedor(float longitud = 2.0f, float ancho = 4.0f, Vec3 pos_eje = { 0.0f, 0.0f, 0.0f })
	{
		this->longitud = longitud;
		this->ancho = ancho;
		this->pos_eje.x = pos_eje.x;
		this->pos_eje.y = pos_eje.y;
		this->pos_eje.z = pos_eje.z;
	}

	// Funcion que dibuja un contenedor completo
	void dibujar()
	{
		// Pintamos de negro los poligonos
		glColor3f(0, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Primera cara del contenedor
		cara();

		// Segunda cara del contenedor
		glPushMatrix();
		glTranslatef(0, 0, ancho);
		cara();
		glPopMatrix();


		// Tercera cara del contenedor
		glPushMatrix();
		glTranslatef(0, 0, ancho);
		glRotatef(90, 0, 1, 0);
		cara();
		glPopMatrix();


		// Cuarta cara del contenedor
		glPushMatrix();
		glTranslatef(ancho, 0, 0);
		glRotatef(90, 0, 1, 0);
		cara();
		glPopMatrix();

		// Uniones del contenedor
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		uniones();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, longitud, 0);
		glRotatef(90, 1, 0, 0);
		uniones();
		glPopMatrix();

		// Dibujamos en alambrico blanco las uniones
		glColor3f(1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// Uniones del contenedor
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		uniones();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, longitud, 0);
		glRotatef(90, 1, 0, 0);
		uniones();
		glPopMatrix();

	}

};

// Callback de atencion al menu de popup
void onMenu(int valor)
{
	if (valor == 0) modo = ALAMBRICO;
	else if (valor == 1) modo = SOLIDO;
	else modo = DOBLE;

	glutPostRedisplay();
}

void update()
{
	// Incialmente la hora de arranque
	static int antes = glutGet(GLUT_ELAPSED_TIME);

	// Hora actual
	int ahora = glutGet(GLUT_ELAPSED_TIME);

	// Tiempo transcurrido
	float tiempo_transcurrido = (ahora - antes) / 1000.0f;

	// Calcular desplazamiento
	posAct[0] = vel * tiempo_transcurrido;

	// Calcular rotaci�n
	posAct[1] += (alfav * 360.0F) * tiempo_transcurrido;
	
	// Asegurarse de que el �ngulo est� en el rango -180� a 180�
	while (posAct[1] > 180.0f) {
		posAct[1] -= 360.0f;
	}
	while (posAct[1] < -180.0f) {
		posAct[1] += 360.0f;
	}
	

	// Actualizo vector de posicion de la camara
	camPosition.x = camPosition.x + posAct[0] * cosf(rad(posAct[1]));
	camPosition.y = camPosition.y - posAct[0] * sinf(rad(posAct[1]));

	// Actualizo vector del punto central al que se mira 
	camLookAt.x = cosf(rad(posAct[1])) + camPosition.x;
	camLookAt.y =  -sinf(rad(posAct[1])) + camPosition.y;

	antes = ahora;

	// Encolar un evento de redibujo
	glutPostRedisplay();
}

void onTimer(int tiempo)
{
	// Sirve para re-arrancar el reloj de cuenta atras
	glutTimerFunc(tiempo, onTimer, tiempo);

	update();
}

// Inicializaciones (solo una vez)
void init()
{
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL version " << glGetString(GL_VERSION) << endl;

	// Menu de popup
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Luces --------------------------------
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, GRISOSCURO);

	/************ Foco de la linterna ************/
	GLfloat dir_central_linterna[] = { 0.0, 0.0, -1.0 }; // Apunta delante como si fuera una linterna
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir_central_linterna);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, GRISCLARO);
	glLightfv(GL_LIGHT0, GL_SPECULAR, GRISCLARO);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); // Cono con apertura de 20� para simular una linterna
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 128.0); // Atenuacion grande de la luz

	/************** Luces fijas **************/
	GLfloat dir_central_fijas[] = { 0.0, -1.0, 0.0 }; // Apuntan hacia el suelo

	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central_fijas);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, VERDE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, VERDE);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0); // Cono con apertura de 60�
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0); // Atenuacion media de la luz

	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_central_fijas);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, VERDE);
	glLightfv(GL_LIGHT2, GL_SPECULAR, VERDE);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0); // Cono con apertura de 60�
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0); // Atenuacion media de la luz

	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_central_fijas);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, VERDE);
	glLightfv(GL_LIGHT3, GL_SPECULAR, VERDE);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 30.0); // Cono con apertura de 60�
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0); // Atenuacion media de la luz
	 
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_central_fijas);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, VERDE);
	glLightfv(GL_LIGHT4, GL_SPECULAR, VERDE);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 30.0); // Cono con apertura de 60�
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0); // Atenuacion media de la luz

	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_central_fijas);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, VERDE);
	glLightfv(GL_LIGHT5, GL_SPECULAR, VERDE);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 30.0); // Cono con apertura de 60�
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0); // Atenuacion media de la luz

	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, dir_central_fijas);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, VERDE);
	glLightfv(GL_LIGHT6, GL_SPECULAR, VERDE);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 30.0); // Cono con apertura de 60�
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 10.0); // Atenuacion media de la luz
	 

	// Material -----------------------------
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, BRONCE);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, ORO);
	//glMaterialf(GL_FRONT, GL_SHININESS, 40);
	//GLfloat s = 20.0;
	/*GLfloat Em[] = { 0.1,0.1,0.2,1.0 };
	GLfloat Am[] = { 0.2,0.2,0.2,1.0 };
	GLfloat Dm[] = { 0.5,0.7,0.6,1.0 };
	GLfloat Sm[] = { 0.8,0.8,0.8,1.0 };
	glMaterialfv(GL_FRONT, GL_EMISSION, Em);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Am);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Sm);*/
	//glMaterialf(GL_FRONT, GL_SHININESS, s);



	// Configuracion del motor de render 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	/*glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LIGHT6);*/
	
}

// Render en backbuffer 
void displaySinMostrar()
{
	// Se hace lo mismo que en display() pero sin hacer swapbuffers
	// Cada objeto seleccionable se pinta de un color solido diferente

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Seleccionar la MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Situar y orientar la camara
	gluLookAt(2, 1, 2, 0, 0, 0, 0, 1, 0);

	// Geometria

	// Tetera roja
	glPushMatrix();

	glRotatef(giroxTR, 1, 0, 0);
	glRotatef(giroyTR, 0, 1, 0);

	glColor3fv(ROJO);
	glutSolidTeapot(0.5);

	glPopMatrix();

	// Tetera azul
	glPushMatrix();
	glTranslatef(-1, 0, -1);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);

	glColor3fv(AZUL);
	glutSolidTeapot(0.5);

	glPopMatrix();

}

// Callback de atencion al redibujado
void display()
{
	// Limpiar Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Seleccionar la MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Situar el foco de luz de la linterna para que se mueva solidario a la camara
	GLfloat posicion[] = { 0.0, 0.0, 0.0, 1.0 }; // Luz de la linterna
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);

	// Situar la camara fija

	// Situar la camara en (0,0,1) y orientar la camara a (0,1,1) 
	//gluLookAt(0, 1, 0, 0, 1, -1, 0, 1, 0);

	//Animaci�n de la c�mara

	// Vec3 camPosition(posAct[0] * cosf(rad(posAct[1])), 1.0f, -posAct[0] * sinf(rad(posAct[1])));
	// gluLookAt(camPosition.x, camPosition.y, camPosition.z, 2.0f * camPosition.x, camPosition.y, -1 + 2.0f * camPosition.z, 0, 1, 0);
	gluLookAt(camPosition.x, camPosition.y, camPosition.z, camLookAt.x, camLookAt.y, camLookAt.z, 0, 0, 1);

	// Dibujar ejes
	ejes();

	// Instanciamos contenedor

	contenedor c1(LONG_CONT, ANCHO_CONT);

	// Valores default para materiales
	GLfloat Em[] = { 0.0,0.0,0.0,1.0 };


	// Luces fijas en la escena ----------------

	GLfloat L1P[] = { 0.0, -8.0, 3.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, L1P);
	GLfloat L2P[] = { 0.0,-16.0,3.0,1.0 };
	glLightfv(GL_LIGHT2, GL_POSITION, L2P);
	GLfloat L3P[] = { 0.0,-24.0,3.0,1.0 };
	glLightfv(GL_LIGHT3, GL_POSITION, L3P);
	GLfloat L4P[] = { 0.0,-32.0,3.0,1.0 };
	glLightfv(GL_LIGHT4, GL_POSITION, L4P);
	GLfloat L5P[] = { 0.0,-40.0,3.0,1.0 };
	glLightfv(GL_LIGHT5, GL_POSITION, L5P);
	GLfloat L6P[] = { 0.0,-48.0,3.0,1.0 };
	glLightfv(GL_LIGHT6, GL_POSITION, L6P);

	// Construccion Plano XY

	int resx = 400, resy = 400; // Resolucion del plano
	GLfloat v0[3] = {-COORXY, -COORXY, 0.0f }, v1[3] = { COORXY, -COORXY, 0.0f },
		v2[3] =  { COORXY, COORXY, 0.0f }, v3[3] = { -COORXY, COORXY, 0.0f };

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, GRISOSCURO);
	glMaterialfv(GL_FRONT, GL_EMISSION, Em);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, BRONCE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ORO);
	glMaterialf(GL_FRONT, GL_SHININESS, 40);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glColor3fv(GRISOSCURO);
	quad(v0, v1, v2, v3, resx, resy);

	glPopMatrix();

	// Dibujar luces fijas si estan activadas

	if (luces_fijas)
	{

		glPushMatrix();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Trasladar en z
		glTranslatef(0.0, 0.0, 3.0);

		for (int i = 6; i > 0; i--)
		{
			// Trasladar en y
			glTranslatef(0.0, -8.0, 0.0);

			// Material del cono
			glMaterialfv(GL_FRONT, GL_AMBIENT, GRISOSCURO);
			glMaterialfv(GL_FRONT, GL_EMISSION, GRISOSCURO);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, GRISOSCURO);
			glMaterialfv(GL_FRONT, GL_SPECULAR, GRISOSCURO);
			glMaterialf(GL_FRONT, GL_SHININESS, 40);

			// Dibujar un cono
			glutSolidCone(0.3, 0.3, 20, 20); // radio de la base, altura, slices, stacks

			// Material de la esfera
			glMaterialfv(GL_FRONT, GL_AMBIENT, VERDE);
			glMaterialfv(GL_FRONT, GL_EMISSION, VERDE);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, VERDE);
			glMaterialfv(GL_FRONT, GL_SPECULAR, VERDE);
			glMaterialf(GL_FRONT, GL_SHININESS, 40);

			// Dibujar una esfera
			glutSolidSphere(0.1, 20, 20); // radio, slices, stacks
		}

		glPopMatrix();

	}

	// Dibujar Contenedores 

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glColor3fv(NEGRO);

	
	glPushMatrix();

	glTranslatef(-2 * ANCHO_CONT, -COORXY, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, GRISOSCURO);
	glMaterialfv(GL_FRONT, GL_EMISSION, Em);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ROJO);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ROJO);
	glMaterialf(GL_FRONT, GL_SHININESS, 40);

	for (int i = 10; i > 0; i--)
	{
		glTranslatef(0, 2 * ANCHO_CONT, 0);
		//glRotatef(90.0f, 1, 0, 0);
		//glutSolidCube();
		
		glutSolidCylinder(ANCHO_CONT, LONG_CONT, 20, 20);
		//c1.dibujar();
	}

	glPopMatrix();

	glPushMatrix();

	glTranslatef(2 * ANCHO_CONT, -COORXY, 0);
	for (int i = 10; i > 0; i--)
	{
		glTranslatef(0, 2 * ANCHO_CONT, 0);
		glutSolidCylinder(ANCHO_CONT, LONG_CONT, 20, 20);
		//c1.dibujar();
	}

	glPopMatrix();

	if (direccion == UP) 
	{
		/*if (dirPrev == DOWN)
		{
			vel = 0.0f;
		}*/
		if (vel < 2.0f)
		{
			vel += 0.2f;
		}
	}
	else if (direccion == DOWN) 
	{
		/*if (dirPrev == UP)
		{
			vel = 0.0f;
		}*/
		if (vel > -2.0f)
		{
			vel -= 0.2f;
		}
	}


	if (rotacion == RIGHT) 
	{
		if (vel < 0.0f)
		{
			alfav = -0.02f;
		}
		else
		{
			alfav = 0.02f;
		}
	}
	else if (rotacion == LEFT)
	{
		if (vel < 0.0f)
		{
			alfav = 0.02f;
		}
		else
		{
			alfav = -0.02f;
		}
	}
	else 
	{
		// Hemos dejado de rotar
		alfav = 0.0f;
	}

	// Reseteamos direccion y rotacion para el siguiente display
	direccion = NOMOV;
	rotacion = NOROT;

	glutSwapBuffers();
}

// Callback de atencion al redimensionado
void reshape(GLint w, GLint h)
{
	float relacionAspecto = float(w) / h;
	glViewport(0, 0, w, h);

	// Definir la camara
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	// Para mantener la relacion de aspecto en Ortografica
	if(relacionAspecto>1)
		glOrtho(-2*relacionAspecto, 2*relacionAspecto, -2, 2, -20, 20);
	else
		glOrtho(-2, 2, -2/relacionAspecto, 2/relacionAspecto, -20, 20);
	*/

	gluPerspective(30, relacionAspecto, 0.1, 100);
}

// Callback de atencion a los eventos de teclas especiales (flechas)
void onSpecialKey(int specialKey, int x, int y)
{
	//glutTimerFunc(0, onTimer, 1000 / tasaFPS);		// Se llama al arrancar
	switch (specialKey) {

		// Flecha_izquierda: gira a la izquierda
	case GLUT_KEY_LEFT:
		rotacion = LEFT;
		break;

		// Flecha_derecha: gira a la derecha
	case GLUT_KEY_RIGHT:
		rotacion = RIGHT;
		break;

		// Flecha_arriba: acelera en la direcci�n del movimiento
	case GLUT_KEY_UP:
		direccion = UP;
		break;

		// Flecha_abajo: desacelera (acelera marcha atr�s)
	case GLUT_KEY_DOWN:
		direccion = DOWN;
		break;
	}

	glutPostRedisplay();
}

// Callback de atencion a los eventos de teclas alfanumericas
void onKey(unsigned char tecla, int x, int y)
{
	// modo indica si es de dia o de noche. Por defecto es de dia (false)
	static bool modo = false;
	// Si se pulsa esc, sale de la aplicacion
	if (tecla == 27)
	{
		exit(0);
	}
	// Si se pulsa l, cambia de modo noche/dia
	else if (tecla == 108) 
	{
		// Cambiamos de modo
		modo = !modo;

		// Modo noche activado
		if (modo)
		{
			luces_fijas = true;
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHT2);
			glEnable(GL_LIGHT3);
			glEnable(GL_LIGHT4);
			glEnable(GL_LIGHT5);
			glEnable(GL_LIGHT6);
		}
		// Modo dia activado
		else
		{
			luces_fijas = false;
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			glDisable(GL_LIGHT2);
			glDisable(GL_LIGHT3);
			glDisable(GL_LIGHT4);
			glDisable(GL_LIGHT5);
			glDisable(GL_LIGHT6);
		}
	}

	glutPostRedisplay();
}

// Callback de atencion al pulsado de un boton del raton
void onClick(int boton, int estado, int x, int y)
{
	// Almacenar donde se hizo el click
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
	}

	// Para preguntar por el pixel tengo que cambiar la Y de sentido
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLint vy = viewport[3] - y;
	// Render en backbuffer para detectar el objeto
	displaySinMostrar();
	// Leer el pixel del backbuffer en la posicion del click
	glReadPixels(x, vy, 1, 1, GL_RED, GL_UNSIGNED_BYTE, objeto);
}

// Callback de atencion al arrastrado del raton
void onDrag(int x, int y)
{
	// Conversion de pixels a grados
	static const float pixel2grados = 1;

	if (objeto[0] == 0xFF) { // Tetera roja
		// Al mover el raton hacia la derecha, la x aumenta y el giro es 
		// alrededor del eje y positivo
		giroyTR += (x - xanterior) * pixel2grados;
		// Al mover el raton hacia abajo, la y aumenta y el giro es 
		// alrededor del eje x positivo
		giroxTR += (y - yanterior) * pixel2grados;
	}
	else {
		// Al mover el raton hacia la derecha, la x aumenta y el giro es 
		// alrededor del eje y positivo
		giroyTA += (x - xanterior) * pixel2grados;
		// Al mover el raton hacia abajo, la y aumenta y el giro es 
		// alrededor del eje x positivo
		giroxTA += (y - yanterior) * pixel2grados;
	}

	xanterior = x;
	yanterior = y;

	glutPostRedisplay();
}

// Programa principal
int main(int argc, char** argv)
{
	// Inicializaciones
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();

	// Registro de callbacks	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, onTimer, 1000 / tasaFPS);		// Se llama al arrancar
	glutKeyboardFunc(onKey);
	glutSpecialFunc(onSpecialKey);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);

	// Bucle de atencion a eventos
	glutMainLoop();
}