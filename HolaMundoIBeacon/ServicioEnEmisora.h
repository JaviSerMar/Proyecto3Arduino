
/**
 * @file ServicioEnEmisora.h
 * @brief Declaración de la clase ServicioEnEmisora y sus características BLE.
 * 
 * Este archivo contiene la definición de la clase `ServicioEnEmisora`, que permite gestionar
 * servicios y características BLE (Bluetooth Low Energy) en una emisora. También incluye
 * funciones auxiliares para manipular datos en formato inverso.
 */

#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

#include <vector>

/**
 * @brief Invierte los elementos de un arreglo.
 * 
 * Esta función toma un puntero a un arreglo de tipo `T` y lo invierte en su lugar.
 * 
 * @tparam T El tipo de los elementos del arreglo.
 * @param p Puntero al arreglo.
 * @param n Cantidad de elementos en el arreglo.
 * @return Puntero al arreglo invertido.
 */

template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for( int i=0; i < n/2; i++ ) {
	aux = p[i];
	p[i] = p[n-i-1];
	p[n-i-1] = aux;
  }
  return p;
} 




/**
 * @brief Convierte una cadena a un arreglo de bytes y lo invierte.
 * 
 * Copia los caracteres de una cadena a un arreglo de tipo `uint8_t` y los coloca en orden inverso.
 * 
 * @param pString Puntero a la cadena original.
 * @param pUint Puntero al arreglo de destino de tipo `uint8_t`.
 * @param tamMax Tamaño máximo del arreglo de destino.
 * @return Puntero al arreglo `pUint` con los valores invertidos.
 */

uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

	int longitudString =  strlen( pString );
	int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );
	for( int i=0; i<=longitudCopiar-1; i++ ) {
	  pUint[ tamMax-i-1 ] = pString[ i ];
	} 

	return pUint;
} 




/**
 * @class ServicioEnEmisora
 * @brief Clase para gestionar un servicio BLE y sus características.
 * 
 * Esta clase permite definir un servicio BLE, agregarle características y activarlo para que funcione en una emisora.
 */
class ServicioEnEmisora {

public:

  /**
   * @brief Definición del tipo de callback para características BLE escritas.
   * 
   * Esta función se llama cuando una característica BLE es escrita desde un cliente BLE.
   * 
   * @param conn_handle Identificador de la conexión BLE.
   * @param chr Puntero a la característica BLE escrita.
   * @param data Puntero a los datos escritos.
   * @param len Longitud de los datos escritos.
   */
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
											   BLECharacteristic * chr,
											   uint8_t * data, uint16_t len); 
  


  /**
   * @class Caracteristica
   * @brief Clase que representa una característica BLE.
   * 
   * Cada característica tiene propiedades, permisos y puede notificar o escribir datos.
   */
  class Caracteristica {

  private:

	uint8_t uuidCaracteristica[16] = { 
	  '0', '1', '2', '3', 
	  '4', '5', '6', '7', 
	  '8', '9', 'A', 'B', 
	  'C', 'D', 'E', 'F'
	};

	 
	
	BLECharacteristic laCaracteristica; ///< Característica BLE asociada.

  public:

  /**
  * @brief Constructor de la clase Caracteristica.
  * 
  * Inicializa la característica con un nombre UUID.
  * 
  * @param nombreCaracteristica_ Nombre de la característica en formato string.
  */
  
	Caracteristica( const char * nombreCaracteristica_ )
	  :
	  laCaracteristica( stringAUint8AlReves( nombreCaracteristica_, &uuidCaracteristica[0], 16 ) )
	{
	  
	}


  /**
     * @brief Constructor avanzado de la clase Caracteristica.
     * 
     * Inicializa la característica con propiedades, permisos y tamaño de datos.
     * 
     * @param nombreCaracteristica_ Nombre de la característica en formato string.
     * @param props Propiedades de la característica (lectura, escritura, etc.).
     * @param permisoRead Permiso de lectura.
     * @param permisoWrite Permiso de escritura.
     * @param tam Tamaño máximo de los datos de la característica.
     */

	Caracteristica( const char * nombreCaracteristica_ ,
					uint8_t props,
					SecureMode_t permisoRead,
					SecureMode_t permisoWrite, 
					uint8_t tam ) 
	  :
	  Caracteristica( nombreCaracteristica_ )
	{
	  (*this).asignarPropiedadesPermisosYTamanyoDatos( props, permisoRead, permisoWrite, tam );
	}

  private:
	void asignarPropiedades ( uint8_t props ) {
	  (*this).laCaracteristica.setProperties( props );
	} 

	void asignarPermisos( SecureMode_t permisoRead, SecureMode_t permisoWrite ) {
	  (*this).laCaracteristica.setPermission( permisoRead, permisoWrite );
	} 

	void asignarTamanyoDatos( uint8_t tam ) {
	  (*this).laCaracteristica.setMaxLen( tam );
	} 

  public:

  /**
  * @brief Asigna propiedades, permisos y tamaño de datos a la característica.
  * 
  * @param props Propiedades de la característica.
  * @param permisoRead Permiso de lectura.
  * @param permisoWrite Permiso de escritura.
  * @param tam Tamaño máximo de los datos.
  */

	void asignarPropiedadesPermisosYTamanyoDatos( uint8_t props,
												 SecureMode_t permisoRead,
												 SecureMode_t permisoWrite, 
												 uint8_t tam ) {
	  asignarPropiedades( props );
	  asignarPermisos( permisoRead, permisoWrite );
	  asignarTamanyoDatos( tam );
	} // ()
												 
  /**
     * @brief Escribe datos en la característica.
     * 
     * @param str Cadena de datos a escribir.
     * @return Cantidad de bytes escritos.
     */
	uint16_t escribirDatos( const char * str ) {

	  uint16_t r = (*this).laCaracteristica.write( str );


	  return r;
	} 



  /**
     * @brief Notifica datos a los clientes BLE conectados.
     * 
     * @param str Cadena de datos a notificar.
     * @return Cantidad de bytes notificados.
     */
	uint16_t notificarDatos( const char * str ) {
	  
	  uint16_t r = laCaracteristica.notify( &str[0] );

	  return r;
	} 


    /**
     * @brief Instala un callback para manejar escritura de datos en la característica.
     * 
     * @param cb Callback que se invocará cuando se escriban datos en la característica.
     */
	void instalarCallbackCaracteristicaEscrita( CallbackCaracteristicaEscrita cb ) {
	  (*this).laCaracteristica.setWriteCallback( cb );
	}


    /**
     * @brief Activa la característica en el servicio BLE.
     * 
     * Llama a la función `begin` para habilitar la característica.
     */

	void activar() {
	  err_t error = (*this).laCaracteristica.begin();
	  Globales::elPuerto.escribir(  " (*this).laCaracteristica.begin(); error = " );
	  Globales::elPuerto.escribir(  error );
	} 

  }; 
  

private:
  
  uint8_t uuidServicio[16] = { 
	'0', '1', '2', '3', 
	'4', '5', '6', '7', 
	'8', '9', 'A', 'B', 
	'C', 'D', 'E', 'F'
  };

  
  BLEService elServicio; ///< Servicio BLE asociado.

  
  std::vector< Caracteristica * > lasCaracteristicas; ///< Lista de características asociadas al servicio.

public:

  /**
   * @brief Constructor de la clase ServicioEnEmisora.
   * 
   * Inicializa el servicio BLE con un nombre UUID.
   * 
   * @param nombreServicio_ Nombre del servicio en formato string.
   */
  
  ServicioEnEmisora( const char * nombreServicio_ )
	:
	elServicio( stringAUint8AlReves( nombreServicio_, &uuidServicio[0], 16 ) )
  {
	
  } 
  
  /**
   * @brief Escribe el UUID del servicio en el puerto serie.
   */

  void escribeUUID() {
	Serial.println ( "**********" );
	for (int i=0; i<= 15; i++) {
	  Serial.print( (char) uuidServicio[i] );
	}
	Serial.println ( "\n**********" );
  } 


  /**
   * @brief Añade una característica al servicio.
   * 
   * @param car Referencia a la característica que se añadirá al servicio.
   */

  void anyadirCaracteristica( Caracteristica & car ) {
	(*this).lasCaracteristicas.push_back( & car );
  } 



  /**
   * @brief Activa el servicio BLE y sus características.
   * 
   * Llama a `begin` para iniciar el servicio y activar sus características.
   */
  void activarServicio( ) {

	err_t error = (*this).elServicio.begin();
	Serial.print( " (*this).elServicio.begin(); error = " );
	Serial.println( error );

	for( auto pCar : (*this).lasCaracteristicas ) {
	  (*pCar).activar();
	} 

  } 


  /**
   * @brief Sobrecarga del operador para devolver el servicio BLE.
   * 
   * @return Referencia al servicio BLE.
   */
  operator BLEService&() {
	return elServicio;
  } 
	
}; 

#endif
