// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include <iostream>
using namespace std;

//Declaración de ventana
GLFWwindow *window;

GLfloat red, green, blue;
GLfloat angulo = 0.0f;
GLfloat velocidadAngular = 180.0f;

double tiempoAnterior = 0.0f;
double velocidad = 0.5f;

GLfloat enemigoX = 0.0f;
GLfloat enemigoY = -1.0f;
GLfloat heroeY = 0.0f;
GLfloat heroeX = 0.0f;

void checarColisiones() {
	if (heroeX >= enemigoX - 0.08 &&
		heroeX <= enemigoX + 0.08 &&
		heroeY >= enemigoY - 0.08 &&
		heroeY <= enemigoY + 0.08) {
		exit(0);
		
	}
}

void actualizar() { 
	//Aquí esta bien para cambiar los valores
	//De las variables de mi programa!
	double tiempoActual = glfwGetTime();
	double tiempoTranscurrido = 
		tiempoActual - tiempoAnterior;
	
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		if (heroeY < 1)
			heroeY += velocidad * tiempoTranscurrido;
	}

	int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		if (heroeY > -1)
			heroeY -= velocidad * tiempoTranscurrido;
	}

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		if (heroeX < 1)
			heroeX += velocidad * tiempoTranscurrido;
	}

	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		if (heroeX > -1)
			heroeX -= velocidad * tiempoTranscurrido;
	}

	checarColisiones();

	tiempoAnterior = tiempoActual;

}

void dibujarHeroe() {
	glPushMatrix();
	glTranslatef(heroeX, heroeY, 0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f); //Afecta eje z
	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_POLYGON); //Inicia la rutina con un modo de dibujo
	glColor3f(1.0f, 0.0f, 1.0f);
	for (float i = 0; i < 360; i++) {
		glVertex3f(0.4 * cos(i) * 1, 0.8 * sin(i) * 1, 0);
	}
	glEnd();//Finaliza la rutina
	glPopMatrix();
}

void dibujarEnemigo() {
	glPushMatrix();
	glTranslatef(enemigoX, enemigoY, 0.0f);
	glScalef(0.08f, 0.08f, 0.08f);
	glBegin(GL_TRIANGLES); //Inicia la rutina con un modo de dibujo
	glColor3f(0.5019f, 0.0f, 0.0f);
	glVertex3f(-1.0f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(1.0, -0.5f, 0.0f);
	glEnd();//Finaliza la rutina

	glPopMatrix();
}

void dibujar() {
	
	dibujarEnemigo();
	dibujarHeroe();
}

/*void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (ty < 1)
			ty += 0.05f;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (ty > -1)
			ty -= 0.05f;
	}

	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (tx < 1)
			tx += 0.05f;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		if (tx > -1)
			tx -= 0.05f;
	}


}*/

int main()
{
	
	//Propiedades de la ventana
	GLfloat ancho = 1200;
	GLfloat alto = 600;

	//Inicialización de GLFW
	if (!glfwInit()) {
		//Si no se inició bien, terminar la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verficar si se creó bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializó bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;


	red = green = blue = 0.0f;

	//glfwSetKeyCallback(window, key_callback);

	tiempoAnterior = glfwGetTime();

	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar señales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

