#ifndef GRAFICADORTURING_H
#define GRAFICADORTURING_H

#include <winbgim.h>
#include <string>
#include <math.h>
#include <stdexcept>

using namespace std;

class GraficadorTuring
{
private:
    string titulo;
    int ancho;
    int alto;
    int colorEstados;
    int colorTextoEstados;
    int radioEstados;
    int colorTransiciones;
    int colorTextoTransiciones;
    int colorFondo;
    int cantidadEstados;
    int xCentro;
    int yCentro;
    double anguloCentral;
    double radioCirculoCentral;
    string *nombres;
    string **transiciones;

    double degToRad(double degrees) {
        return degrees * M_PI / 180.0;
    }

    double radToDeg(double radians) {
        return radians * 180.0 / M_PI;
    }

    double coseno(double angulo) {
        return cos(degToRad(angulo));
    }

    double seno(double angulo) {
        return sin(degToRad(angulo));
    }

    double arcocoseno(double valor) {
        return radToDeg(acos(valor));
    }

    double arcotangente2(double dy, double dx) {
        return radToDeg(atan2(dy, dx));
    }

    double calcularAnguloPuntos(int x1, int y1, int x2, int y2) {
        double dx = x2 - x1;
        double dy = y2 - y1;
        return arcotangente2(dy, dx);
    }

    int calcularXEstado(int indiceEstado, int radio) {
        return xCentro + radio * coseno(anguloCentral * indiceEstado);
    }

    int calcularYEstado(int indiceEstado, int radio) {
        return yCentro + radio * seno(anguloCentral * indiceEstado);
    }

    double sumarAngulo(double angulo1, double angulo2) {
        angulo1 += angulo2;
        if (angulo1 < 0) {
            while (angulo1 < 0) {
                angulo1 += 360;
            }
        } else {
            while (angulo1 >= 360) {
                angulo1 -= 360;
            }
        }
        return angulo1;
    }

    void dibujarEstado(int x, int y, string texto) {
        setcolor(colorEstados);
        setfillstyle(1, colorEstados);
        fillellipse(x, y, radioEstados, radioEstados);
        moveto(x, y);
        setcolor(colorTextoEstados);
        setbkcolor(colorEstados);
        settextstyle(2, 0, 5);
        settextjustify(1, 1);
        outtext(texto.c_str());
    }

    void dibujarTransicion(int x1, int y1, int x2, int y2, string texto,int par) {
        if (x1 == x2 && y1 == y2) {
            dibujarTransicionCircular(x1, y1, texto,par);
        } else {
            dibujarTransicionLineal(x1, y1, x2, y2, texto,par);
        }
    }

    void dibujarTransicionLineal(int x1, int y1, int x2, int y2, string texto,int par) {
        double angulo = calcularAnguloPuntos(x2, y2, x1, y1);
        int x3 = x2 + radioEstados * coseno(angulo);
        int y3 = y2 + radioEstados * seno(angulo);

        setcolor(colorTransiciones);
        line(x1, y1, x3, y3);
        dibujarFlecha(x3, y3, angulo);

        setbkcolor(colorTransiciones);
        setcolor(colorTextoTransiciones);
        if(par%2 == 0 && par != 0){
            dibujarTexto( ((x1 + x2) / 2)*par+1, ((y1 + y2) / 2)*par+1, texto);
        }
        else{
            dibujarTexto( (((x1 + x2) / 2)*par-1), (((y1 + y2) / 2)*par-1), texto);
        }

    }

    void dibujarTexto(int x, int y, string texto) {
        moveto(x, y);
        settextstyle(2, 0, 5); // tamaño del texto y tipo de letra
        settextjustify(2, 2); // centrado horizontal y vertical -------------------------> (2,2)
        outtext(texto.c_str());
    }

    void dibujarFlecha(int x, int y, double angulo) {
        double longitudFlecha = 15;
        double anguloAperturaFlecha = 30;

        int xFlecha1 = x + longitudFlecha * coseno(sumarAngulo(angulo, -anguloAperturaFlecha));
        int yFlecha1 = y + longitudFlecha * seno(sumarAngulo(angulo, -anguloAperturaFlecha));
        line(x, y, xFlecha1, yFlecha1);

        int xFlecha2 = x + longitudFlecha * coseno(sumarAngulo(angulo, anguloAperturaFlecha));
        int yFlecha2 = y + longitudFlecha * seno(sumarAngulo(angulo, anguloAperturaFlecha));
        line(x, y, xFlecha2, yFlecha2);
    }

    void dibujarTransicionCircular(int x, int y, string texto,int par) {
        double anguloPunto = calcularAnguloPuntos(xCentro, yCentro, x, y);
        int xCentroCiclo = x + (radioEstados * 1.5) * coseno(anguloPunto);
        int yCentroCiclo = y + (radioEstados * 1.5) * seno(anguloPunto);

        double anguloApertura = arcocoseno(3.0 / 4.0);

        double anguloPuntoFlecha = sumarAngulo(anguloPunto, anguloApertura - 2);
        int xFlecha = x + radioEstados * coseno(anguloPuntoFlecha);
        int yFlecha = y + radioEstados * seno(anguloPuntoFlecha);

        setcolor(colorTransiciones);
        dibujarFlecha(xFlecha, yFlecha, anguloPuntoFlecha);
        circle(xCentroCiclo, yCentroCiclo, radioEstados);

        setbkcolor(colorTransiciones);
        setcolor(colorTextoTransiciones);

        int xPosTexto = x + (radioEstados * 2.5) * coseno(anguloPunto);
        int yPosTexto = y + (radioEstados * 2.5) * coseno(anguloPunto);
        if(par%2 == 0 && par != 0){
            dibujarTexto(xPosTexto*(par+1), yPosTexto*(par+1), texto);
        }
        else{
            dibujarTexto(xPosTexto*(par-1), yPosTexto*(par-1) , texto);
        }

    }

public:
    GraficadorTuring(int pAncho, int pAlto, int pCantidadEstados) {
        ancho = pAncho;
        alto = pAlto;
        colorEstados = 1;
        colorTextoEstados = 15;
        radioEstados = 20;
        colorTransiciones = 15;
        colorTextoTransiciones = 0;
        colorFondo = 0;
        cantidadEstados = pCantidadEstados;
        anguloCentral = 360.0 / (double)cantidadEstados;
        xCentro = ancho / 2;
        yCentro = alto / 2;
        radioCirculoCentral = ((xCentro > yCentro)? yCentro : xCentro) - radioEstados * 3;

        // se inicializa el arreglo con los nombres de los nodos
        nombres = new string[cantidadEstados];
        for (int i = 0; i < cantidadEstados; i++) {
            nombres[i] = "";
        }
        // se inicializa la matriz con las etiquetas de las transiciones
        transiciones = new string*[cantidadEstados];
        for (int i = 0; i < cantidadEstados; i++) {
            transiciones[i] = new string[cantidadEstados];
            for (int j = 0; j < cantidadEstados; j++) {
                transiciones[i][j] = "";
            }
        }
        initwindow(ancho, alto);
    }

    ~GraficadorTuring() {
        delete [] nombres;
        for (int i = 0; i < cantidadEstados; i++) {
            delete [] transiciones[i];
        }
    }

    void dibujarEstados() {
        for (int i = 0; i < cantidadEstados; i++) {
            for (int j = 0; j < cantidadEstados; j++) {
                if (transiciones[i][j] != "") {
                    dibujarTransicion(calcularXEstado(i, radioCirculoCentral),
                                      calcularYEstado(i, radioCirculoCentral),
                                      calcularXEstado(j, radioCirculoCentral),
                                      calcularYEstado(j, radioCirculoCentral),
                                      transiciones[i][j],i-j);
                }
            }
        }
        for (int i = 0; i < cantidadEstados; i++) {
            dibujarEstado(calcularXEstado(i, radioCirculoCentral),
                          calcularYEstado(i, radioCirculoCentral),
                          nombres[i]);
        }
    }

    void asignarNombreEstado(int indiceEstado, string nombre) throw(runtime_error) {
        if (indiceEstado < 0 || indiceEstado > cantidadEstados) {
            throw runtime_error("Índice del estado fuera de rango.");
        }
        nombres[indiceEstado] = nombre;
    }

    void asignarTransicion(int indiceOrigen, int indiceDestino, string texto) throw(runtime_error) {
        if (indiceOrigen < 0 || indiceOrigen > cantidadEstados) {
            throw runtime_error("Índice del estado origen fuera de rango.");
        }
        if (indiceDestino < 0 || indiceDestino > cantidadEstados) {
            throw runtime_error("Índice del estado destino fuera de rango.");
        }
        transiciones[indiceOrigen][indiceDestino] = texto;
    }

    void testing() {
    }
};

#endif // GRAFICADORTURING_H
