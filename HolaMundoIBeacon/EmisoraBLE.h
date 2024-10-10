#ifndef EMISORA_H_INCLUIDO
#define EMISORA_H_INCLUIDO

#include "ServicioEnEmisora.h"

/**
 * @class EmisoraBLE
 * @brief Clase para gestionar la funcionalidad de una emisora BLE, incluyendo la emisión de anuncios y la conexión con dispositivos BLE.
 */
class EmisoraBLE {
private:
  const char* nombreEmisora;    ///< Nombre de la emisora BLE.
  const uint16_t fabricanteID;  ///< ID del fabricante para identificar el beacon.
  const int8_t txPower;         ///< Potencia de transmisión del beacon.

public:
  /// Callback para gestionar la conexión establecida.
  using CallbackConexionEstablecida = void (uint16_t connHandle);
  /// Callback para gestionar la finalización de una conexión.
  using CallbackConexionTerminada = void (uint16_t connHandle, uint8_t reason);

  /**
   * @brief Constructor para inicializar una emisora BLE.
   * 
   * @param nombreEmisora_ Nombre de la emisora.
   * @param fabricanteID_ ID del fabricante.
   * @param txPower_ Potencia de transmisión.
   */
  EmisoraBLE(const char* nombreEmisora_, const uint16_t fabricanteID_, const int8_t txPower_)
    : nombreEmisora(nombreEmisora_), fabricanteID(fabricanteID_), txPower(txPower_)
  {
  }

  /**
   * @brief Enciende la emisora BLE y detiene cualquier anuncio en curso.
   */
  void encenderEmisora() {
    Bluefruit.begin();
    detenerAnuncio();
  }

  /**
   * @brief Enciende la emisora BLE y registra los callbacks para la conexión.
   * 
   * @param cbce Callback para la conexión establecida.
   * @param cbct Callback para la conexión terminada.
   */
  void encenderEmisora(CallbackConexionEstablecida cbce, CallbackConexionTerminada cbct) {
    encenderEmisora();
    instalarCallbackConexionEstablecida(cbce);
    instalarCallbackConexionTerminada(cbct);
  }

  /**
   * @brief Detiene el anuncio si está en ejecución.
   */
  void detenerAnuncio() {
    if (estaAnunciando()) {
      Bluefruit.Advertising.stop();
    }
  }

  /**
   * @brief Verifica si la emisora está anunciando.
   * 
   * @return true si está anunciando, false en caso contrario.
   */
  bool estaAnunciando() {
    return Bluefruit.Advertising.isRunning();
  }

  /**
   * @brief Emite un anuncio en formato iBeacon.
   * 
   * @param beaconUUID UUID del beacon.
   * @param major Valor major del beacon.
   * @param minor Valor minor del beacon.
   * @param rssi RSSI del beacon.
   */
  void emitirAnuncioIBeacon(uint8_t* beaconUUID, int16_t major, int16_t minor, uint8_t rssi) {
    detenerAnuncio();
    BLEBeacon elBeacon(beaconUUID, major, minor, rssi);
    elBeacon.setManufacturer(fabricanteID);
    Bluefruit.setTxPower(txPower);
    Bluefruit.setName(nombreEmisora);
    Bluefruit.ScanResponse.addName();
    Bluefruit.Advertising.setBeacon(elBeacon);
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(100, 100);
    Bluefruit.Advertising.start(0);
  }

  /**
   * @brief Emite un anuncio iBeacon con carga libre de datos.
   * 
   * @param carga Cadena de datos a emitir como carga del beacon.
   * @param tamanyoCarga Tamaño de la carga en bytes.
   */
  void emitirAnuncioIBeaconLibre(const char* carga, const uint8_t tamanyoCarga) {
    detenerAnuncio();
    Bluefruit.Advertising.clearData();
    Bluefruit.ScanResponse.clearData();
    Bluefruit.setName(nombreEmisora);
    Bluefruit.ScanResponse.addName();
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

    uint8_t restoPrefijoYCarga[4+21] = {0x4c, 0x00, 0x02, 21, '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-'};
    memcpy(&restoPrefijoYCarga[4], &carga[0], (tamanyoCarga > 21 ? 21 : tamanyoCarga));
    Bluefruit.Advertising.addData(BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA, &restoPrefijoYCarga[0], 4 + 21);
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(100, 100);
    Bluefruit.Advertising.setFastTimeout(1);
    Bluefruit.Advertising.start(0);
    Globales::elPuerto.escribir("emitiriBeacon libre Bluefruit.Advertising.start(0);\n");
  }

  /**
   * @brief Añade un servicio a la emisora BLE.
   * 
   * @param servicio Referencia a un servicio de la emisora.
   * @return true si el servicio fue añadido exitosamente, false en caso contrario.
   */
  bool anyadirServicio(ServicioEnEmisora& servicio) {
    Globales::elPuerto.escribir(" Bluefruit.Advertising.addService( servicio ); \n");
    bool r = Bluefruit.Advertising.addService(servicio);
    if (!r) {
      Serial.println(" SERVICIO NO AÑADIDO \n");
    }
    return r;
  }

  /**
   * @brief Añade un servicio y sus características a la emisora BLE.
   * 
   * @param servicio Referencia al servicio a añadir.
   * @return true si el servicio fue añadido exitosamente, false en caso contrario.
   */
  bool anyadirServicioConSusCaracteristicas(ServicioEnEmisora& servicio) {
    return anyadirServicio(servicio);
  }

  /**
   * @brief Añade un servicio con varias características a la emisora BLE.
   * 
   * @param servicio Servicio a añadir.
   * @param caracteristica Primera característica del servicio.
   * @param restoCaracteristicas Otras características del servicio.
   * @return true si el servicio fue añadido exitosamente, false en caso contrario.
   */
  template <typename... T>
  bool anyadirServicioConSusCaracteristicas(ServicioEnEmisora& servicio, ServicioEnEmisora::Caracteristica& caracteristica, T&... restoCaracteristicas) {
    servicio.anyadirCaracteristica(caracteristica);
    return anyadirServicioConSusCaracteristicas(servicio, restoCaracteristicas...);
  }

  /**
   * @brief Añade un servicio con varias características y lo activa.
   * 
   * @param servicio Servicio a añadir.
   * @param restoCaracteristicas Características del servicio.
   * @return true si el servicio fue añadido y activado exitosamente, false en caso contrario.
   */
  template <typename... T>
  bool anyadirServicioConSusCaracteristicasYActivar(ServicioEnEmisora& servicio, T&... restoCaracteristicas) {
    bool r = anyadirServicioConSusCaracteristicas(servicio, restoCaracteristicas...);
    servicio.activarServicio();
    return r;
  }

  /**
   * @brief Instala un callback para la conexión establecida.
   * 
   * @param cb Callback a instalar.
   */
  void instalarCallbackConexionEstablecida(CallbackConexionEstablecida cb) {
    Bluefruit.Periph.setConnectCallback(cb);
  }

  /**
   * @brief Instala un callback para la conexión terminada.
   * 
   * @param cb Callback a instalar.
   */
  void instalarCallbackConexionTerminada(CallbackConexionTerminada cb) {
    Bluefruit.Periph.setDisconnectCallback(cb);
  }

  /**
   * @brief Obtiene la conexión BLE correspondiente al identificador de conexión.
   * 
   * @param connHandle Identificador de la conexión.
   * @return Puntero a la conexión BLE.
   */
  BLEConnection* getConexion(uint16_t connHandle) {
    return Bluefruit.Connection(connHandle);
  }

}; // class EmisoraBLE

#endif
