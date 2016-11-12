/*
 * xgama_app.cpp
 *
 *  Created on: 18/04/2014
 *      Author: juan
 */
#include "xgama_app.h"

XGAMA_Application::XGAMA_Application(const WEnvironment& env)
    : WApplication(env)
{
	/* Titulo de la pagina Web */
		setTitle("Plataforma X-GAMA App");

    /* Temporizador para captura de frames */
			WTimer *Init_Time = new WTimer();
			Init_Time->setInterval(FPS_TIMER_ms); //ms
			Init_Time->timeout().connect(this,&XGAMA_Application::Capture_Video);
			Init_Time->start();

	/* Temporizador para transferencia SPI */
			WTimer *SPI_transfer = new WTimer();
			SPI_transfer->setInterval(50); //ms
			SPI_transfer->timeout().connect(this,&XGAMA_Application::SPI_Transfer);
			SPI_transfer->start();

    /* Widget para mostrar Frames,vía metodo de por memoria */
			Memory_widget = new WMemoryResource(MINETYPE_FRAME);
			Memory_widget->setData(frame_uchar);
			Video_widget = new WImage(Memory_widget,"Video Plataforma X-GAMA");
			Video_widget->setMaximumSize(640,480);
			Video_widget->setMinimumSize(640,480);


	/* Widget para control servomotores */
			Contenedor_Servos = new WContainerWidget();
			Contenedor_Servos-> setMaximumSize(640,480);
			Contenedor_Servos-> setMinimumSize(640,480);
			Init_Servo_Table(Contenedor_Servos);
			Contenedor_Botones = new WContainerWidget();
			Init_PushBottoms(Contenedor_Botones);
			Contenedor_Botones->setMaximumSize(150,200);
			Contenedor_Botones->setMinimumSize(150,200);

	/* Widget para el la visualizacion de los sensores*/
			Sens_Temperatura = new WContainerWidget();
			Sens_Brujula = new WContainerWidget();
			Sens_InAnalog = new WContainerWidget();
			Init_Sensores_Contenedor(Sens_Temperatura,Sens_Brujula,Sens_InAnalog);

	/*Comunicación SPI */
			Init_SPI_Raspberry();

	/* Layout de la interfaz Web */
			Layout_Horizontal[0] = new WHBoxLayout();
			Layout_Horizontal[1] = new WHBoxLayout();
			Fila[0] = new WContainerWidget();
			Fila[1] = new WContainerWidget();

			Fila[0]->setLayout(Layout_Horizontal[0]);//Contendor con la primera fila (Video y Controles)
			Layout_Horizontal[0]->addWidget(Video_widget);
			Layout_Horizontal[0]->addWidget(Contenedor_Servos);

			Fila[1]->setLayout(Layout_Horizontal[1]);//Contenedor con la segunda fila (Botones y Datos Sensores)
			Layout_Horizontal[1]->addWidget(Contenedor_Botones);
			Layout_Horizontal[1]->addWidget(Sens_Temperatura);
			Layout_Horizontal[1]->addWidget(Sens_Brujula);
			Layout_Horizontal[1]->addWidget(Sens_InAnalog);

			root()->addWidget(Fila[0]);
			root()->addWidget(new WBreak());
			root()->addWidget(Fila[1]);
}

void XGAMA_Application::Capture_Video()
{
	static VideoCapture video(0);
    static Mat frame;

		if(video.isOpened())
			{
				video >> frame;
				/* Metodo de enviar una zona de memoria */
					imencode(".jpeg",frame,frame_uchar);
					Memory_widget->setData(frame_uchar);
			}
		else
		{
				frame = imread("/home/juan/X-GAMA-Server/docs/img/cam_desc.jpg");
				imencode(".jpeg",frame,frame_uchar);
				Memory_widget->setData(frame_uchar);
		}

}

void XGAMA_Application::Init_Servo_Table(WContainerWidget *parent)
{
	std::stringstream ss;

			/* Widget para control servomotores */
				Servo_Table = new WTable(parent);
				Servo_Table->setHeaderCount(1); //Pone en negrilla la primera fila
				Servo_Table->setWidth("100%");

	        /* Cabeceras */
				Servo_Table->elementAt(0,0)->addWidget(new WText("Grado"));
				Servo_Table->elementAt(0,1)->addWidget(new WText("Etiqueta"));
				Servo_Table->elementAt(0,1)->setContentAlignment(AlignMiddle);
				Servo_Table->elementAt(0,2)->addWidget(new WText("Valor (deg)"));
				Servo_Table->elementAt(0,2)->setContentAlignment(AlignLength);
				Servo_Table->elementAt(0,3)->addWidget(new WText(" "));

				/* Llenado de la tabla */
				for(int i= 0; i < 7; i++)
				{
					Servo_Table->elementAt(i+1,0)->addWidget(new WText(servo_label[i].deg_id));
					Servo_Table->elementAt(i+1,1)->addWidget(new WText(servo_label[i].Etiqueta));

					Servo_Slider[i] = new WSlider();
					Servo_Slider[i]->decorationStyle().setCursor(PointingHandCursor);
					Servo_Slider[i]->resize(300, 50);
					Servo_Slider[i]->setTickPosition(WSlider::TicksAbove);
					Servo_Slider[i]->setTickInterval(1);
					Servo_Slider[i]->setRange(servo_label[i].min_value,servo_label[i].max_value);
					Servo_Slider[i]->setValue(servo_label[i].value);
					Servo_Table->elementAt(i+1,3)->addWidget(Servo_Slider[i]);
					Servo_Slider[i]->valueChanged().connect(this,&XGAMA_Application::Slide_Data_Change);

					ss << servo_label[i].value;
					Servo_Value[i] =new WLineEdit(ss.str());
					Servo_Value[i]->setMaximumSize(40,70);
					Servo_Table->elementAt(i+1,4)->addWidget(Servo_Value[i]);
					ss.str(""); //Se debe reiniciar el stringstream, este es el metodo
					/* La siguiente Linea es para editar el valor desde el LineEdit*/
					//Servo_Value[i]->enterPressed().connect(this,&XGAMA_Application::Servo_Data_Change);
				}
}

void XGAMA_Application::Slide_Data_Change(void)
{
	static std::stringstream ss;

	for(int i= 0; i < 7; i++)
					{
							ss << Servo_Slider[i]->value();
							Servo_Value[i]->setText(ss.str());
							ss.str(""); //Se debe reiniciar el stringstream, este es el metodo
					}
}

/* Esta funcion requiere ser modificada para lograr editar el valor desde el LineEdit*/
/*Fuera de Funcionamiento */
void XGAMA_Application::Servo_Data_Change(void)
{
	static std::stringstream ss;
	static int xvalue;

		for(int i= 0; i < 7; i++)
						{
								ss << Servo_Value[i]->text();
								if(!(ss >> xvalue))
										xvalue = 0;
								Servo_Slider[i]->setValue(xvalue);
								ss.str(""); //Se debe reiniciar el stringstream, este es el metodo
						}
		//ss << xvalue;
		//greeting_->setText(ss.str());
}

void XGAMA_Application::Init_PushBottoms(WContainerWidget *parent)
{
	Servodir[0] = new WPushButton("Adelante");
	Servodir[0]->mouseWentOver().connect(this,&XGAMA_Application::Active_Adelante);
	Servodir[0]->mouseWentOut().connect(this,&XGAMA_Application::Disable_All);
	Servodir[1] = new WPushButton("Atras");
	Servodir[1]->mouseWentOver().connect(this,&XGAMA_Application::Active_Atras);
	Servodir[1]->mouseWentOut().connect(this,&XGAMA_Application::Disable_All);
	Servodir[2] = new WPushButton("Derecha");
	Servodir[2]->mouseWentOver().connect(this,&XGAMA_Application::Active_Derecha);
	Servodir[2]->mouseWentOut().connect(this,&XGAMA_Application::Disable_All);
	Servodir[3] = new WPushButton("Izquierda");
	Servodir[3]->mouseWentOver().connect(this,&XGAMA_Application::Active_Izquierda);
	Servodir[3]->mouseWentOut().connect(this,&XGAMA_Application::Disable_All);
	/* Layout */
	parent->addWidget(new WText(" . . . "));
	parent->addWidget(new WText("<b>Controles Base</b>"));
	parent->addWidget(new WText(" . . ."));
	parent->addWidget(new WBreak());
	parent->addWidget(new WBreak());
	parent->addWidget(new WText(". . . . "));
	parent->addWidget(Servodir[0]);
	parent->addWidget(new WText(" . . . ."));
	parent->addWidget(new WBreak());
	parent->addWidget(Servodir[3]);
	parent->addWidget(Servodir[2]);
	parent->addWidget(new WBreak());
	parent->addWidget(new WText(". . . . . "));
	parent->addWidget(Servodir[1]);
	parent->addWidget(new WText(" . . . . ."));
}

void XGAMA_Application::Init_Sensores_Contenedor(WContainerWidget *cont1,WContainerWidget *cont2, WContainerWidget *cont3)
{
	/* Sensor de Temperatura */
		cont1->addWidget(new WText(". . . . "));
		cont1->addWidget(new WText("<b>Sensor Temperatura</b>"));
		cont1->addWidget(new WText(". . . . "));
		cont1->addWidget(new WBreak());
		cont1->addWidget(new WBreak());
		cont1->addWidget(new WText("<b>Temperatura (C): </b>"));
		Sensores[0] = new WText("Cargado...");
		cont1->addWidget(Sensores[0]);

		/* Brujula Digital */
		cont2->addWidget(new WText(". . . . "));
		cont2->addWidget(new WText("<b>Brujula Digital</b>"));
		cont2->addWidget(new WText(". . . . "));
		cont2->addWidget(new WBreak());
		cont2->addWidget(new WBreak());
		cont2->addWidget(new WText("<b> Compas (deg): </b>"));
		Sensores[1] = new WText("Cargado...");
		cont2->addWidget(Sensores[1]);
		cont2->addWidget(new WBreak());
		cont2->addWidget(new WText("<b> Pitch (deg): </b>"));
		Sensores[2] = new WText("Cargado...");
		cont2->addWidget(Sensores[2]);
		cont2->addWidget(new WBreak());
		cont2->addWidget(new WText("<b> Roll (deg): </b>"));
		Sensores[3] = new WText("Cargado...");
		cont2->addWidget(Sensores[3]);

		/* Brujula Digital */
		cont3->addWidget(new WText(". . . . "));
		cont3->addWidget(new WText("<b>Entradas Analogas</b>"));
		cont3->addWidget(new WText(". . . . "));
		cont3->addWidget(new WBreak());
		cont3->addWidget(new WBreak());
		cont3->addWidget(new WText("<b> Sensor Luz (V): </b>"));
		Sensores[4] = new WText("Cargado...");
		cont3->addWidget(Sensores[4]);
		cont3->addWidget(new WBreak());
		cont3->addWidget(new WText("<b> Sensor Proximidad (cm): </b>"));
		Sensores[5] = new WText("Cargado...");
		cont3->addWidget(Sensores[5]);
}

void XGAMA_Application::Init_SPI_Raspberry(void)
{
	bcm2835_init();
	bcm2835_spi_begin();
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096);
	xgama2master.I2C_slaves.LM75B_Sens.Temp_r = 0;
	xgama2master.I2C_slaves.CMPS10_Sens.Compas = 0;
	xgama2master.I2C_slaves.CMPS10_Sens.Pitch = 0;
	xgama2master.I2C_slaves.CMPS10_Sens.Roll = 0;
	xgama2master.ADC_slaves.Light_Sens = 0;
	xgama2master.ADC_slaves.Sonar_Sens = 0;
	master2xgama.OC[Rigth_Motor] = 0;
	master2xgama.OC[Left_Motor] = 0;
}

void XGAMA_Application::SPI_Transfer(void)
{
	std::stringstream ss;

	/* Copia de los valores de la interfaz en la estructura para enviar al microcontrolador*/
		master2xgama.OC[Grado_1] = (uint8_t)(Servo_Slider[0]->value());
		master2xgama.OC[Grado_2] = (uint8_t)(Servo_Slider[1]->value());
		master2xgama.OC[Grado_3] = (uint8_t)(Servo_Slider[2]->value());
		master2xgama.OC[Grado_4] = (uint8_t)(Servo_Slider[3]->value());
		master2xgama.OC[Grado_5] = (uint8_t)(15.625*(Servo_Slider[4]->value())+125);
		master2xgama.OC[Panoramica] = (uint8_t)(Servo_Slider[5]->value());
		master2xgama.OC[Inclinacion] = (uint8_t)(Servo_Slider[6]->value());

		if((Servo_Slider[1]->value() + 2) < (int)(xgama2master.I2C_slaves.CMPS10_Sens.Pitch*(-1)))
			master2xgama.OC[Grado_2] =125;//Baja
		if((Servo_Slider[1]->value() -2) > (int)(xgama2master.I2C_slaves.CMPS10_Sens.Pitch*(-1)))
			master2xgama.OC[Grado_2] =250;//Sube
		if( ((Servo_Slider[1]->value() -2) <= (int)(xgama2master.I2C_slaves.CMPS10_Sens.Pitch*(-1))) && ((Servo_Slider[1]->value() + 2) >= 
(int)(xgama2master.I2C_slaves.CMPS10_Sens.Pitch*(-1))))
			master2xgama.OC[Grado_2] =186;//Se detiene

		bcm2835_spi_transfernb((char *)(&master2xgama), (char *)(&xgama2master), sizeof(XGAMA_t));

		//ss << std::dec << (int)(master2xgama.OC[Grado_1]);//Test

		ss << std::dec << (float)(xgama2master.I2C_slaves.LM75B_Sens.Temp_r/256);
		Sensores[0]->setText(ss.str()); //Temperatura
		ss.str("");
		ss << std::dec << (float)(xgama2master.I2C_slaves.CMPS10_Sens.Compas/10.0);
		Sensores[1]->setText(ss.str());
		ss.str("");
		ss << std::dec << (int)(xgama2master.I2C_slaves.CMPS10_Sens.Pitch*(-1));
		Sensores[2]->setText(ss.str());
		ss.str("");
		ss << std::dec << (int)(xgama2master.I2C_slaves.CMPS10_Sens.Roll);
		Sensores[3]->setText(ss.str());
		ss.str("");
		ss << std::dec << (float)(xgama2master.ADC_slaves.Light_Sens*2.75/256);
		Sensores[4]->setText(ss.str());
		ss.str("");
		ss << std::dec << (float)((xgama2master.ADC_slaves.Sonar_Sens*2.75/256)*254);//Conversion a voltaje y luego a centimetros
		Sensores[5]->setText(ss.str());
		ss.str("");
}

void XGAMA_Application::Active_Adelante(void)
{
	master2xgama.OC[Rigth_Motor] = 250;
	master2xgama.OC[Left_Motor] = 125;
}

void XGAMA_Application::Active_Atras(void)
{
	master2xgama.OC[Rigth_Motor] = 125;
	master2xgama.OC[Left_Motor] = 250;
}

void XGAMA_Application::Active_Derecha(void)
{
	master2xgama.OC[Rigth_Motor] = 125;
	master2xgama.OC[Left_Motor] = 125;
}

void XGAMA_Application::Active_Izquierda(void)
{
	master2xgama.OC[Rigth_Motor] = 250;
	master2xgama.OC[Left_Motor] = 250;
}

void XGAMA_Application::Disable_All(void)
{
	master2xgama.OC[Rigth_Motor] = 0;
	master2xgama.OC[Left_Motor] = 0;
}
