/*
 * xgama_app.h
 *  Created on: 18/04/2014
 *  Author: Juan Escobar and Jair Cañon
 *  Definicion de la clase para el manejo de la Plataforma X-GAMA, el archivo debe
 *	pertenecer al usuario root y debe tener el bit s activado chmod +s para su correcta
 *	ejecucion por parte del servidor web, ej: Lighttpd
 */

#ifndef XGAMA_APP_H_
#define XGAMA_APP_H_

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WTimer>
#include <Wt/WImage>
#include <Wt/WTable>
#include <Wt/WMemoryResource>
#include <Wt/WSlider>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include "x_gama_board.h"
#include "bcm2835.h"
#include <stdlib.h>

using namespace Wt;
using namespace cv;

/* Video Defines */
#define MINETYPE_FRAME "image/jpeg"
#define FPS_TIMER_ms	30


/* La aplicacion hereda de la clase WApplication */
class XGAMA_Application : public WApplication
{
public:
	/* Constructor, el parametro es para pasarlo al constructor de
	 * de la clase WApplication
	 */
	XGAMA_Application(const WEnvironment& env);

private:

    /* Controladores del video */
		WImage *Video_widget;
		WMemoryResource *Memory_widget;
		vector<uchar> frame_uchar;
		void Capture_Video();

	/* Controladores servomotores */
		/* Servomotores articulares */
			WTable 	*Servo_Table;
			WSlider *Servo_Slider[7];
			WLineEdit 	*Servo_Value[7];
			WContainerWidget *Contenedor_Servos;
			void Init_Servo_Table(WContainerWidget *parent);
			void Slide_Data_Change(void);
			void Servo_Data_Change(void);
		/*Servomotores de tracción */
			WPushButton *Servodir[4]; // 0-> Adelante, 1-> Atras, 2-> Derecha, 3-> Izquierda
			WContainerWidget *Contenedor_Botones;
			void Init_PushBottoms(WContainerWidget *parent);

		/* Widget datos sensores */
			WText *Sensores[6];
			WContainerWidget *Sens_Brujula;
			WContainerWidget *Sens_Temperatura;
			WContainerWidget *Sens_InAnalog;
			void Init_Sensores_Contenedor(WContainerWidget *cont1,WContainerWidget *cont2, WContainerWidget *cont3);

		/*Tranferencia spi */
			XGAMA_t xgama2master, master2xgama;
			void Init_SPI_Raspberry(void);
			void SPI_Transfer(void);
			void Active_Adelante(void);
			void Active_Atras(void);
			void Active_Derecha(void);
			void Active_Izquierda(void);
			void Disable_All(void);



		/* Controladores de Layout (posición)*/
			WHBoxLayout *Layout_Horizontal[2];
			WContainerWidget *Fila[2];
};

namespace{

	struct Servo_Label_t{
			string deg_id;
			string Etiqueta;
			int value;
			int min_value;
			int max_value;
			Servo_Label_t(const string p_id,
							const string p_eti,
							int p_val,
							int p_min,
							int p_max)

			:deg_id(p_id),
			 Etiqueta(p_eti),
			 value(p_val),
			 min_value(p_min),
			 max_value(p_max){}
						};

	Servo_Label_t servo_label[] = {
			Servo_Label_t("1","Base",0,113,250),
			Servo_Label_t("2","Pitch",0,-10,60),
			Servo_Label_t("3","Pitch 2",0,113,262),
			Servo_Label_t("4","Giro Efector",0,113,262),
			Servo_Label_t("5","Efector (cm)",4,0,8),
			Servo_Label_t("6","Panoramica",0,113,262),
			Servo_Label_t("7","Inclinacion",0,113,262)
									};
}

#endif /* XGAMA_APP_H_ */
