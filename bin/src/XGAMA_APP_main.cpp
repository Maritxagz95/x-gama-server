#include "xgama_app.h"


/* Creacion del objeto, para la funcion WRun, que requiere como parametro un puntero */
WApplication * createApplication(const WEnvironment& env)
	{
    	return new XGAMA_Application(env);
	}

/* Main donde se crea una aplicacion por cada peticion de clientes */
int main(int argc, char **argv)
	{
    	return WRun(argc, argv, &createApplication);
	}
