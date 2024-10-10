/**
 * @file LED.h
 * @brief Declaración de la clase LED y funciones asociadas para controlar un LED en una placa de desarrollo.
 * 
 * Este archivo define la clase `LED` para controlar el encendido, apagado y parpadeo de un LED conectado
 * a un pin digital de una placa de desarrollo (como Arduino).
 */
#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO


/**
 * @brief Función auxiliar para esperar una cantidad de tiempo.
 * 
 * Esta función utiliza `delay` para pausar la ejecución por un tiempo dado en milisegundos.
 * 
 * @param tiempo Cantidad de tiempo en milisegundos para esperar.
 */

void esperar (long tiempo) {
  delay (tiempo);
}


/**
 * @class LED
 * @brief Clase para controlar un LED.
 * 
 * Esta clase permite encender, apagar, alternar el estado y hacer parpadear un LED conectado a un pin digital.
 */

class LED {
private:
  int numeroLED; ///< Número del pin al que está conectado el LED.
  bool encendido; ///< Estado del LED (encendido o apagado).
public:

  /**
   * @brief Constructor de la clase LED.
   * 
   * Inicializa el LED configurando el pin como salida y apagando el LED.
   * 
   * @param numero Número del pin digital al que está conectado el LED.
   */

  LED (int numero)
	: numeroLED (numero), encendido(false)
  {
	pinMode(numeroLED, OUTPUT);
	apagar ();
  }


  /**
   * @brief Enciende el LED.
   * 
   * Establece el pin digital correspondiente en estado alto (HIGH) para encender el LED y marca el estado como encendido.
   */
  void encender () {
	digitalWrite(numeroLED, HIGH); 
	encendido = true;
  }


  /**
   * @brief Apaga el LED.
   * 
   * Establece el pin digital correspondiente en estado bajo (LOW) para apagar el LED y marca el estado como apagado.
   */
  void apagar () {
	  digitalWrite(numeroLED, LOW);
	  encendido = false;
  }

  /**
    * @brief Alterna el estado del LED.
    * 
    * Si el LED está encendido, lo apaga; si está apagado, lo enciende.
    */
  void alternar () {
	if (encendido) {
	  apagar();
	} else {
	  encender ();
	}
  } 


  /**
   * @brief Hace que el LED brille por un tiempo especificado.
   * 
   * Enciende el LED, espera durante el tiempo especificado y luego lo apaga.
   * 
   * @param tiempo Tiempo en milisegundos que el LED permanecerá encendido antes de apagarse.
   */

  void brillar (long tiempo) {
	encender ();
	esperar(tiempo); 
	apagar ();
  }
}; 


#endif
