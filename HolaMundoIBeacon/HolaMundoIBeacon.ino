

/**
 * @file main.cpp
 * @brief Controlador principal para la placa BLE.
 * 
 * Este archivo contiene las funciones principales del ciclo de vida de la placa
 * que mide CO2 y temperatura, y publica los datos usando Bluetooth Low Energy (BLE).
 */

#include <bluefruit.h>

#undef min 
#undef max 


#include "LED.h"
#include "PuertoSerie.h"


/// @namespace Globales
/// Espacio de nombres que contiene instancias globales de los componentes utilizados.
namespace Globales {
  


  /**
   * @brief Instancia del LED conectado al pin 7.
   */
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );



  /**
   * @brief Instancia del puerto serie configurado a una velocidad de 115200 baudios.
   */
  PuertoSerie elPuerto ( /* velocidad = */ 115200 ); // 115200 o 9600 o ...

};

#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"


namespace Globales {



  /**
   * @brief Instancia del publicador BLE para enviar los datos.
   */
  Publicador elPublicador;



  /**
   * @brief Instancia del medidor de CO2 y temperatura.
   */
  Medidor elMedidor;

};




/**
 * @brief Inicializa los componentes de la placa.
 * 
 * Esta función se encarga de inicializar cualquier periférico o componente adicional
 * conectado a la placa.
 */
void inicializarPlaquita () {

  

} 



/**
 * @brief Función de configuración (setup).
 * 
 * Esta función se ejecuta una sola vez al inicio del programa y prepara el puerto serie,
 * inicializa la emisora BLE y el medidor de CO2 y temperatura.
 */
void setup() {

  Globales::elPuerto.esperarDisponible(); ///< Espera a que el puerto serie esté disponible.

  inicializarPlaquita(); ///< Inicializa la placa.

  Globales::elPublicador.encenderEmisora(); ///< Enciende la emisora BLE.

  
  Globales::elMedidor.iniciarMedidor(); ///< Inicia el medidor de CO2 y temperatura.

  esperar( 1000 ); ///< Espera 1 segundo.

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " ); ///< Escribe un mensaje en el puerto serie indicando que el setup ha finalizado.

} 



/**
 * @brief Controla la secuencia de parpadeo del LED.
 * 
 * Esta función activa y desactiva el LED con un brillo del 100% durante varios intervalos de tiempo.
 */

inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); ///< Enciende el LED al 100% de brillo.
  esperar ( 400 ); ///< Espera 400 ms.
  elLED.brillar( 100 ); 
  esperar ( 400 ); 
  Globales::elLED.brillar( 100 ); 
  esperar ( 400 ); 
  Globales::elLED.brillar( 1000 ); ///< Enciende el LED al 100% de brillo por un tiempo más largo.
  esperar ( 1000 ); ///< Espera 1 segundo.
}
} 


/**
 * @namespace Loop
 * @brief Espacio de nombres que contiene las variables relacionadas con el bucle principal.
 */
namespace Loop {


  /**
   * @brief Contador del número de iteraciones del bucle principal.
   */
  uint8_t cont = 0;
};




/**
 * @brief Bucle principal del programa (loop).
 * 
 * Esta función se ejecuta continuamente y se encarga de realizar mediciones
 * de CO2 y temperatura, publicarlas mediante BLE, y manejar la secuencia de parpadeo del LED.
 */
void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++; ///< Incrementa el contador de iteraciones del bucle.

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );


  lucecitas(); ///< Ejecuta la secuencia de parpadeo del LED.

  
  // Medición y publicación de CO2
  int valorCO2 = elMedidor.medirCO2(); ///< Mide el valor del CO2.
  
  elPublicador.publicarCO2( valorCO2,
							cont,
							1000 
							); ///< Publica el valor del CO2.
  
  


  // Medición y publicación de temperatura
  int valorTemperatura = elMedidor.medirTemperatura(); ///< Mide la temperatura.
  
  elPublicador.publicarTemperatura( valorTemperatura, 
									cont,
									1000 
									); ///< Publica el valor de la temperatura.

  

  // Publicación de un anuncio iBeacon libre
  char datos[21] = {
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H'
  };

  elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 ); ///< Emite un anuncio iBeacon con los datos.

  esperar( 2000 ); ///< Espera 2 segundos.

  elPublicador.laEmisora.detenerAnuncio(); ///< Detiene el anuncio BLE.
  

  
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
} 
