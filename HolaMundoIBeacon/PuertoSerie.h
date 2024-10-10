
/**
 * @file PuertoSerie.h
 * @brief Declaración de la clase PuertoSerie.
 * 
 * La clase PuertoSerie se encarga de gestionar la comunicación serie a través de los puertos seriales.
 */

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO


/**
 * @class PuertoSerie
 * @brief Clase para gestionar la comunicación a través de un puerto serie.
 * 
 * Proporciona métodos para inicializar el puerto serie, verificar su disponibilidad 
 * y enviar datos a través de él.
 */

class PuertoSerie  {

public:

  /**
   * @brief Constructor de la clase PuertoSerie.
   * 
   * Inicializa la comunicación serie con la velocidad en baudios especificada.
   * 
   * @param baudios Velocidad en baudios para la comunicación serie (por ejemplo, 115200).
   */


  PuertoSerie (long baudios) {
	Serial.begin( baudios ); ///< Inicia la comunicación serie.
  } 


  /**
   * @brief Espera a que el puerto serie esté disponible.
   * 
   * Realiza una breve espera para asegurar que el puerto serie esté listo antes de continuar.
   */
  void esperarDisponible() {

	delay(10); ///< Pausa durante 10 milisegundos para dar tiempo a que el puerto serie esté disponible.

  } 


  /**
   * @brief Escribe un mensaje en el puerto serie.
   * 
   * Esta función envía un mensaje a través del puerto serie utilizando la función `Serial.print`.
   * 
   * @tparam T El tipo de dato del mensaje que será enviado (puede ser texto, número, etc.).
   * @param mensaje El mensaje que será enviado por el puerto serie.
   */

  template<typename T>
  void escribir (T mensaje) {
	Serial.print( mensaje ); ///< Envia el mensaje por el puerto serie.
  } 
  
}; 

#endif
