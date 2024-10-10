
/**
 * @file Publicador.h
 * @brief Declaración de la clase Publicador.
 * 
 * Esta clase gestiona la publicación de los datos de CO2 y temperatura utilizando la emisora BLE.
 */

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO




/**
 * @class Publicador
 * @brief Clase encargada de publicar mediciones de CO2 y temperatura usando BLE.
 * 
 * La clase Publicador controla la emisora BLE y se encarga de enviar los datos de mediciones 
 * como CO2 y temperatura, encapsulándolos en anuncios iBeacon.
 */

class Publicador {

private:


  /**
   * @brief UUID usado en los anuncios iBeacon.
   * 
   * Este array de 16 bytes representa el UUID que se usa en los anuncios iBeacon emitidos por la emisora BLE.
   */

  uint8_t beaconUUID[16] = { 
	'c', 'h', 'o', 'l', 'o', 's', 'i', 
	'm', 'e', 'o', 'n', 'e', 'j','e','f','e'
};



  
  
public:

  /**
   * @brief Instancia de la emisora BLE.
   * 
   * Esta instancia de la clase EmisoraBLE se utiliza para emitir anuncios BLE con los datos de los sensores.
   */

  EmisoraBLE laEmisora {
	"GTI-3A", ///< Nombre del dispositivo BLE.
	  0x004c, ///< Identificador de fabricante (Apple).
	  4  ///< Potencia de emisión.
	  };
  

  /**
   * @brief Valor RSSI (Received Signal Strength Indicator) usado en los anuncios iBeacon.
   */
  const int RSSI = -53; 

  
public:

  
  /**
   * @enum MedicionesID
   * @brief Identificadores únicos para los tipos de medición.
   * 
   * Estos valores se utilizan en los anuncios iBeacon para indicar el tipo de medición que se está enviando.
   */
  enum MedicionesID  {
	CO2 = 11, ///< Identificador para la medición de CO2.
	TEMPERATURA = 12, ///< Identificador para la medición de temperatura.
	RUIDO = 13 ///< Identificador para la medición de ruido (no implementado en este código).
  };

  

  /**
   * @brief Constructor de la clase Publicador.
   * 
   * Inicializa una nueva instancia de Publicador.
   */
  Publicador( ) {
  }




  /**
   * @brief Enciende la emisora BLE.
   * 
   * Esta función activa la emisora BLE para que comience a emitir anuncios.
   */
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora(); ///< Llama a la función para encender la emisora.
  } 




  /**
   * @brief Publica una medición de CO2.
   * 
   * Esta función emite un anuncio iBeacon con los datos de CO2 y luego espera el tiempo especificado antes de detener la emisión.
   * 
   * @param valorCO2 Valor medido de CO2.
   * @param contador Contador de iteraciones del bucle.
   * @param tiempoEspera Tiempo en milisegundos que se espera antes de detener el anuncio.
   */

  void publicarCO2( int16_t valorCO2, uint8_t contador,
					long tiempoEspera ) {

	
	
	

	uint16_t major = (MedicionesID::CO2 << 8) + contador; ///< Crea el valor `major` usando el ID de CO2 y el contador.
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorCO2, 
											(*this).RSSI
									);

	

	esperar( tiempoEspera ); ///< Espera el tiempo especificado antes de detener el anuncio.

	
	(*this).laEmisora.detenerAnuncio(); ///< Detiene el anuncio BLE.
  }



  /**
   * @brief Publica una medición de temperatura.
   * 
   * Esta función emite un anuncio iBeacon con los datos de temperatura y luego espera el tiempo especificado antes de detener la emisión.
   * 
   * @param valorTemperatura Valor medido de temperatura.
   * @param contador Contador de iteraciones del bucle.
   * @param tiempoEspera Tiempo en milisegundos que se espera antes de detener el anuncio.
   */
  void publicarTemperatura( int16_t valorTemperatura,
							uint8_t contador, long tiempoEspera ) {


	uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador; ///< Crea el valor `major` usando el ID de temperatura y el contador.
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorTemperatura, 
											(*this).RSSI 
									);
	esperar( tiempoEspera ); ///< Espera el tiempo especificado antes de detener el anuncio.


	(*this).laEmisora.detenerAnuncio(); ///< Detiene el anuncio BLE.
  } 
	
}; 

#endif
