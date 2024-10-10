

/**
 * @file Medidor.h
 * @brief Declaración de la clase Medidor.
 * 
 * Esta clase se encarga de gestionar las mediciones de CO2 y temperatura
 * de los sensores conectados a la placa.
 */

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO



/**
 * @class Medidor
 * @brief Clase que representa el sensor de medición de CO2 y temperatura.
 * 
 * La clase permite iniciar el sensor y obtener los valores medidos de CO2 y temperatura.
 */
class Medidor {

private:
  // No hay variables privadas en esta clase.


public:


  /**
   * @brief Constructor de la clase Medidor.
   * 
   * Inicializa una nueva instancia de Medidor.
   */
  Medidor(  ) {
  } 


  /**
   * @brief Inicia el medidor de CO2 y temperatura.
   * 
   * Esta función prepara el medidor para comenzar a tomar medidas de CO2 y temperatura.
   */
  void iniciarMedidor() {
  } 


  /**
   * @brief Mide el nivel de CO2.
   * 
   * Esta función simula una medición de CO2 devolviendo un valor fijo.
   * @return int El valor medido de CO2 (actualmente retorna 235 de forma fija).
   */
  int medirCO2() {
	return 235; ///< Valor simulado de CO2.

  } 



  /**
   * @brief Mide la temperatura.
   * 
   * Esta función simula una medición de temperatura devolviendo un valor fijo.
   * @return int El valor medido de la temperatura (actualmente retorna 12 de forma fija).
   */
  int medirTemperatura() {
	return 12; ///< Valor simulado de temperatura.
  } 
	
};

#endif
