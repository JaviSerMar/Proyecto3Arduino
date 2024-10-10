# Proyecto3Arduino - Emisora BLE

Este proyecto consiste en el desarrollo de una emisora Bluetooth Low Energy (BLE) utilizando una placa de desarrollo (como Arduino). La emisora está diseñada para enviar anuncios en formato iBeacon y gestionar conexiones con dispositivos BLE. 

## Estructura del Proyecto

El código está organizado en diferentes archivos, cada uno cumpliendo una función específica. A continuación se describen los archivos más importantes:

- **HolaMundoBeacon.ino**: Archivo principal que ejecuta el código de la emisora BLE.
- **Medidor.h**: Contiene funciones y métodos para la lectura de datos del sensor.
- **Publicador.h**: Se encarga de publicar los datos leídos en la red.
- **PuertoSerie.h**: Maneja la comunicación serie entre el Arduino y el ordenador.
- **ServicioEnEmisora.h**: Define los servicios BLE que la emisora puede ofrecer.
- **EmisoraBLE.h**: Clase que gestiona la funcionalidad de la emisora BLE.
- **LED.h**: Clase para controlar un LED en la placa de desarrollo (opcional para indicar estado).

## Funcionalidad del Proyecto

La emisora BLE está diseñada para enviar beacons que contienen información relevante, como la identificación del dispositivo, y permite la recepción de datos desde dispositivos compatibles. Este proyecto permite crear una infraestructura de sensores que pueden comunicarse de manera eficiente utilizando la tecnología BLE.


### Requisitos

Asegúrate de tener instalada la biblioteca correspondiente para Bluetooth Low Energy y que la placa de desarrollo esté correctamente configurada. Este proyecto ha sido probado en una placa Arduino compatible.


### Cómo Cargar el Código

Abre el archivo HolaMundoBeacon.ino en el IDE de Arduino.
Conecta tu placa de desarrollo a la computadora.
Selecciona la placa y el puerto en el menú del IDE de Arduino.
Carga el código en la placa.


### Ejemplo de Uso

En el archivo `HolaMundoBeacon.ino`, puedes encontrar la implementación que configura la emisora BLE, establece los parámetros necesarios y gestiona el envío de beacons. 

```cpp
#include "EmisoraBLE.h"

EmisoraBLE emisora;

void setup() {
  // Inicialización de la emisora BLE
  emisora.iniciar();
}

void loop() {
  // Enviar un beacon cada cierto intervalo
  emisora.enviarBeacon();
  delay(1000); // Intervalo de 1 segundo
}

