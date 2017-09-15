/*
Test del sensor de CO2 CCS811

Conexiones
LCD             I2C
Sensor CCS811   I2C
DHT22           7

by JAVacasM
 */


/* ==== Includes - Librerias==== */
// Sensor CCS811
#include <CCS811.h>

// Pantalla LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Sensor temperatura y humedad
#include <SimpleDHT.h>

/* ====  END Includes ==== */

/* ==== Defines - Constantes ==== */
// Constantes de CCS811
#define CCS811_ADDR       0x5A
//#define CCS811_ADDR      0x5B
#define CCS811_WAKE_PIN   4

#define SENSOR_DHT_PIN    7
/* ==== END Defines ==== */

/* ==== Variables Globales ==== */
// Variables de CCS811
CCS811 sensor;

// Variables de pantalla LCD
LiquidCrystal_I2C lcd(0x27,20,4);

// Variables del DHT
SimpleDHT22 dht22;

/* ==== END Global Variables ==== */


/* ==== Funciones a usar - Prototipos ==== */

/* ==== END Prototipos ==== */

/* ==== Setup - Configuracion ==== */
void setup() {
// Conexion Serie
  Serial.begin(9600);
  Serial.println("CCS811 test");
  
// Constantes de CCS811

  if(!sensor.begin(uint8_t(CCS811_ADDR), uint8_t(CCS811_WAKE_PIN))){
    Serial.println("Error inicializando sensor CCS811");
  }

  // Incializacion de la pantalla
  lcd.init();                 
  lcd.backlight();
  
}
/* ==== END Setup ==== */

/* ==== Loop - Codigo que se repite==== */
void loop() {
  // Medida de temperatura y humedad

  byte bTemperatura = 0;
  byte bHumedad = 0;
  
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read(SENSOR_DHT_PIN, &bTemperatura, &bHumedad, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }

  float fTemperatura=(float)bTemperatura;
  float fHumedad=(float)bHumedad;
  
  // Medida de CO2
  //sensor.compensate(fTemperatura, fHumedad);  // replace with t and rh values from sensor
  sensor.getData();
  Serial.print("CO2 concentration : "); 
  Serial.print(sensor.readCO2()); 
  Serial.println(" ppm");
  lcd.setCursor(0,0);
  lcd.print("CO2: "); 
  lcd.print(sensor.readCO2()); 
  lcd.print(" ppm");
  
  Serial.print("TVOC concentration : "); 
  Serial.print(sensor.readTVOC()); 
  Serial.println(" ppb");
  lcd.setCursor(0,1);
  lcd.print("TVOC: "); 
  lcd.print(sensor.readTVOC()); 
  lcd.print(" ppb");

  Serial.print("Temp:");
  Serial.print(fTemperatura);
  Serial.println("C");
  lcd.setCursor(0,2);
  lcd.print("Temp:");
  lcd.print(fTemperatura);
  lcd.print("C");

  Serial.print("Hum:");
  Serial.print(fHumedad);
  Serial.println("%");
  lcd.setCursor(0,3);
  lcd.print("Hum:");
  lcd.print(fHumedad);
  lcd.print("%");
  delay(2000);
}
/* ==== End Loop ==== */

/* ==== Funciones ==== */

/* ==== END Functions ==== */
