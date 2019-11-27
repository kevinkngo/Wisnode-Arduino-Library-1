/*
 * A library for controlling RAK811 LoRa radio.
 *
 * RAK811 wisnode-lora v1.2
 * Firmware RAK811_V3.0.0.12.H
 * RUI_RAK811_BOOT_Version3_0_2
 * @Author Ncl17
 * BASED ON RAKwireless library for controlling RAK811 LoRa radio.  
 * @Author Chace.cao
 * @Author john.zou
 * @Date 25/11/2019
 *
 */

#ifndef RAK811_h
#define RAK811_h
#define LoRaWAN 0
#define LoRaP2P 1
#define OTAA 0
#define ABP 1
#define BAND "US915";

#define TXpinRAK 2   // Set the virtual serial port pins for Arduino Uno
#define RXpinRAK 3

#define STATUS_RECV_DATA  "at+recv=0,0,0"
#define STATUS_TX_COMFIRMED  "at+recv=1,0,0"
#define STATUS_TX_UNCOMFIRMED  "at+recv=2,0,0"
#define STATUS_JOINED_SUCCESS  "[LoRa]:Join Success"
#define STATUS_JOINED_FAILED  "at+recv=4,0,0"
#define STATUS_TX_TIMEOUT  "at+recv=5,0,0"
#define STATUS_RX2_TIMEOUT  "at+recv=6,0,0"
#define STATUS_DOWNLINK_REPEATED  "at+recv=7,0,0"
#define STATUS_WAKE_UP  "at+recv=8,0,0"
#define STATUS_P2PTX_COMPLETE  "at+recv=9,0,0"
#define STATUS_UNKNOWN  "at+recv=100,0,0"
#include "Arduino.h"

//#define DEBUG_MODE

class RAK811
{
  public:

 /*
  * A simplified constructor taking only a Stream ({Software/Hardware}Serial) object.
  * The serial port should already be initialised when initialising this library.
  */
  RAK811(Stream& serial,Stream& serial1);

 /*
  * Gets the firmware version number of the module.
  * Only applies to the firmware that the module programmed for the RAK811 AT command.
  */
  String rk_getVersion();

 /*
  * Set the frequency band of the module.
  *US915
 */
  String rk_setBand(String band);


 /*
  * Use to change the next send data rate temporary when adr function is off.
  * It will not be save to internal flash.
  * rate : If your Band is EU868 from 0 to 7.
  *        If your Band is US915 from 0 to 4.
  */
  bool rk_setRate(int rate);
 /*
  * Let the module enter the ultra low power sleep mode.
  * When the module is in sleep mode, the host can send any character to wake it up.
  * When the module is awakened, the event response will automatically return through the serial information.
  */
  void rk_sleep();
  void rk_wakeup();

 /*
  * Reset the module .
  */
  void rk_restar();


 /*
  * Set the module work mode, the module defaults to LoRaWAN mode..
  * mode  = 0: Set the module to LoRaWAN mode.
  * mode  = 1: Set the module to LoRaP2P mode.
  */
  bool rk_setWorkingMode(int mode);


/*
* Join to LoraNetwork
*/
  bool rk_joinLoRaNetwork();
 int rk_joinLoRaNetwork2();

 bool RAK811::rk_set_devEUI(String devEUI);
 bool RAK811::rk_set_appEUI(String appEUI);
 bool RAK811::rk_set_appKEY(String appKEY);
 /*
  * Initialize the module parameter, which is the parameter that the module must use when adding the OTAA to the network.
  * devEUI : Device EUI as a HEX string. Example "60C5A8FFFE000001"
  * appEUI : Application EUI as a HEX string. Example "70B3D57EF00047C0"
  * appKEY : Application key as a HEX string. Example "5D833B4696D5E01E2F8DC880E30BA5FE"
  */
  bool rk_initOTAA(String devEUI, String appEUI, String appKEY);

 /*
  * Initialize the module parameter, which is the parameter that the module must use when adding the ABP to the network.
  * devADDR : The device address as a HEX string. Example "00112233"
  * nwksKEY : Network Session Key as a HEX string. Example "3432567afde4525e7890cfea234a5821"
  * appsKEY : Application Session Key as a HEX string. Example "a48adfc393a0de458319236537a11d90"
  */
  bool rk_initABP(String devADDR, String nwksKEY, String appsKEY);


 /*
  * Get the received signal strength and signal to noise ratio.Is negative, the greater the value the better
  * Through the last packet received, from which the LoRa gateway or base station signal strength.
  */
  String rk_getSignal(void);

 /*
  * Set the LoRa configuration parameters.
  * Key : Represents the parameter type.Example "dev_addr" "adr" "dr" "tx_power" ......
  *       Refer to the Programming Manual for parameter type details.:RAK811 Lora AT Command User Guide V1.3.pdf
  *       http://docs.rakwireless.com/en/RAK811%20LoRa%20Module/Software%20Development/RAK811%C2%A0LoRa%C2%A0AT%C2%A0Command%C2%A0V1.3.pdf
  * Value : Represents the parameter value.
  *       The size of each parameter type is strictly specified, please refer to the programming manual for more information
  */
  bool rk_setConfig(String Key, String Value);

 /*
  * Obtain the configuration parameters of the LoRa module.
  * Key : Represents the parameter type.Example "dev_addr" "adr" "dr" "tx_power" ......
  *       Refer to the Programming Manual for parameter type details.:RAK811 Lora AT Command User Guide V1.3.pdf
  *       http://docs.rakwireless.com/en/RAK811%20LoRa%20Module/Software%20Development/RAK811%C2%A0LoRa%C2%A0AT%C2%A0Command%C2%A0V1.3.pdf
  */
  String rk_getConfig(String Key);

 /*
  * After joining the network, send the packet at the specified application port.
  * port : The port number.(1-223)
  * datahex : hex value(no space). max 64 byte.
  * This function can only be used in module work in LoRaWAN mode.
  */
  bool rk_sendData( int port, String datahex);

  /*
   * Send Bytes
   * port : The port number.(1-223)
   * buffer : uint8_t inputBuffer
   * size : Size of buffer
   * This function can only be used in module work in LoRaWAN mode.
   */
   bool rk_sendBytes(int port, uint8_t* buffer, int bufSize);

 /*
  * Returns the data or event information received by the module.
  *
  */
  String rk_recvData(void);

 /*
  * Get the parameters configured in the LoRaP2P mode
  * it will used to the rk_sendDataContinuously and rk_recvDataContinuously command.
  * The returned string represents the meaning of : OK[<FREQ>, <SF>, <BW>, <CR>, <PRlen>, <PWR>]
  */
  String rk_getP2PConfig(void);

 /*
  * Get the Lora status
  */
  String rk_getLoraStatus(void);

 /*
  * Get the device status
  */
  String rk_getDeviceStatus(void);



 /*
  * Initialize the required parameters in LoRaP2P mode.
  * You must first switch the module operating mode to LoRaP2P mode
  * FREQ : frequency, default 860000000 range: (860000000 ~1020000000)
  * SF : spread factor, default 7 ( 6-10) more low more fast datarate
  * BW : Band-with, default 0 ( 0:125KHz, 1:250KHz, 2:500KHz)
  * CR : coding Rate, default 1 (1:4/5, 2:4/6, 3:4/7, 4:4/8)
  * PRlen : Preamlen, default 8 (8-65535)
  * PWR : Tx power, default 14 (5-20)
  * User can use this command to build their point to point communication or RFtest command. It will save to flash.
  */
  bool rk_initP2P(String FREQ, int SF, int BW, int CR, int PRlen, int PWR);

 /*
  * Set LoRaP2P Tx continues, module will send the counts packet with rfconfig until receive the rk_stopSendP2PData command or rk_reset,.
  * CNTS : Number of consecutive transmissions (1-65535)
  * interver : Continuous transmission interval.This interval is begin with last packet send success or fail., (10-3600000ms)
  * DATAHex : hex value ( no space) , max 64 byte.
  */
  bool rk_sendP2PData(char* DATAHex);

 /*
  * Set LoRaP2P Rx continues,module will receive packets with rfconfig until receive the rk_stopRecvP2PData command or rk_reset.
  * report_en : enable report to host or not. 0 : not enable.  1 : enable.
  * If used normal rx ,can set the report_en :1, report data to host.
  */
  bool rk_recvP2PData(int report_en);



 /*
  * Set the module serial port parameters.Module restart effective
  * Band : Serial baud rate.Supports baud rate: 9600  19200  38400  57600  115200  230400  460800  921600.
  */
  bool rk_setUARTConfig(int Baud);

 /*
  * Send a raw command to the RAK811 module.
  * Returns the raw string as received back from the RAK811.
  * If the RAK811 replies with multiple line, only the first line will be returned.
  */
  String sendRawCommand(String command);
 
  private:
  Stream& _serial;

  Stream& _serial1;

  String _devADDR = "00112233";

  String _devEUI = "60C5A8FFFE000001";

  String _appEUI = "";

  String _nwksKEY = "";

  String _appKEY = "";

  String _appsKEY = "";

};
#endif
