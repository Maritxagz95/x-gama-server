// Defines for BCM2835
#ifndef X_GAMA_DRIVER_H
#define X_GAMA_DRIVER_H
#include <stdint.h>
/* Definiciones I2C */

/* LM75B */
#define LM75B_SLAVE_ADDR		0x48
#define LM75B_TEMP_RD			0X00
#define LM75B_CONFIG_RD			0x01
#define LM75B_THYST_RD			0X02
#define LM75B_TOS_RD			0X03
#define LM75B_NUMFAULT_1		(0 << 4) | (0 << 3)
#define LM75B_NUMFAULT_2		(1 << 3)
#define LM75B_NUMFAULT_4		(1 << 4)
#define LM75B_NUMFAULT_6		(3 << 3)
#define LM75B_OS_POL_0			(0 << 2)
#define LM75B_OS_POL_1			(1 << 2)
#define LM75B_MOD_COMP			(0 << 1)
#define LM75B_MOD_INT			(1 << 1)
#define LM75B_ENABLE			(0 << 0)
#define LM75B_DISABLE			(1 << 0)

/* CMPS10 */ 
#define CMPS10_SLAVE_ADDR		0x60
#define CMPS10_COMPASS_MSB 		2
#define CMPS10_COMPASS_LSB 		3
#define CMPS10_PITCH	 		4
#define CMPS10_ROLL		 		5
#define CMPS10_MAGNETX_MSB		10
#define CMPS10_MAGNETX_LSB 		11
#define CMPS10_MAGNETY_MSB		12
#define CMPS10_MAGNETY_LSB 		13
#define CMPS10_MAGNETZ_MSB		14
#define CMPS10_MAGNETZ_LSB 		15
#define CMPS10_ACCELX_MSB		16
#define CMPS10_ACCELX_LSB		17
#define CMPS10_ACCELY_MSB		18
#define CMPS10_ACCELY_LSB		19
#define CMPS10_ACCELZ_MSB		20
#define CMPS10_ACCELZ_LSB 		21
#define CMPS10_CONFIG	 		22

/* Puente H - DRV8830 */
#define DRV8830_SLAVE_ADDR		0x68
#define DRV8830_CONTROL			0X00
#define DRV8830_FAULT			0X01
#define DRV8830_STANDBY			(0 << 1) | (0 << 0)
#define DRV8830_REVERSE			(1 << 0)
#define DRV8830_FORWARD			(1 << 1)
#define DRV8830_BRAKE			(3 << 0)
#define DRV8830_VSET			2
#define DRV8830_CLEAR_FLAGS		(1 << 7)

/* Enumeracion para los servomotores */
enum Compare_enum	{D_0C0A, D_0C0B, D_0C0C, D_0C0D, D_0C1A, D_0C1B, C_0C0A, C_0C0B, C_0C0C};
enum Servo_enum		{Grado_1,Grado_2,Grado_3,Grado_4,Grado_5,Panoramica,Inclinacion,Left_Motor,Rigth_Motor};

/* Sensor de temperatura LM75B */
typedef struct{
	int16_t Temp_r; /* Para obtener el valor real de la temperatura de debe dividir este valor por 2^8  (256)*/
	uint8_t Conf_r;
	uint8_t Hyst;
	uint8_t Comp;
	/*La estructura con o sin el dummy pesa 4 bytes, razon por la cual se debe compensar la
	  estructara para que tenga congruencia con el tamaño en bytes con el X-MEGA (sin dummy
	  pesa 3Bytes)*/
	uint8_t dummy;
}LM75B;

/* Brujula Digital CMPS10 */
typedef struct{
	uint16_t Compas;
	int8_t Pitch;
	int8_t Roll;
}CMPS10;

/* Puente H - Motor DC */
typedef struct{
	uint8_t control_reg;
	uint8_t fault_reg;
}H_BRIDGE;

/* Perifericos ADC */
typedef struct{
	uint8_t Light_Sens;
	uint8_t Sonar_Sens;
}ADC_Perifericos;

typedef struct{
		LM75B LM75B_Sens;
		CMPS10 CMPS10_Sens;
		H_BRIDGE H_BRIDGE_DVR;
}I2C_Prerifericos;

/*Estructura para el protocolo SPI */
typedef struct{
		int8_t Sync[2];
		uint16_t OC[9];	//Output compare de 16 bits
		ADC_Perifericos ADC_slaves;
		I2C_Prerifericos I2C_slaves;
}XGAMA_t;

#endif
