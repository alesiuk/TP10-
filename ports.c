#include "ports.h"

static porst_t p;
static void w_port (uint16_t estado);

/*W_port*/

static void w_port (uint16_t estado){ //funcion que solo se ocupa de escribir en el puerto
    p.PortD = estado;
}
uint16_t r_port (void){ //funcion que se encarga de leer el puerto
    uint16_t estado = p.PortD;
    return estado;
}
//////////////BITSET///////////////////////

void bitSet (int data,char puerto){
   if ((puerto == 'A')||(puerto == 'a')){
        data +=8;
      
    }
    uint16_t port = r_port();
    unsigned int a = potencia (2 , data);  //obtengo el valor del bit al que necesito analizar
    if ( ( (port&a) == a) == 0 )            //hago un AND con el puerto y el bit y compruebo si el resultado es igual al bit asi verifico si el bit esta encedido o apagado,
    {
        port = port + a;                    // enciendo el bit en caso de que este apagado
    }
    w_port(port);   //si esta encendido no hago nada
    
}

//////////////BITCLR///////////////////////

void bitClr (int data, char puerto){
   if ((puerto == 'A')||(puerto == 'a')){
        data +=8;
    }
    uint16_t port = r_port();
    unsigned int a = potencia (2 , data);  //obtengo el valor del bit al que necesito analizar
    if ( ( (port&a) == a) == 1 )            //hago un AND con el puerto y el bit y compruebo si el resultado es igual al bit asi verifico si el bit esta encedido o apagado,
    {
        port = port - a;                    // apago el bit en caso de que este encendido
    }
    w_port(port);                           //si esta apagado no hago nada
}
//////////////BITGET///////////////////////

int bitGet (int data, char puerto){
    if ((puerto == 'A')||(puerto == 'a')){
        data +=8;
    }
    uint16_t port = r_port();
    int c;
    unsigned int a = potencia (2 , data);  //obtengo el valor del bit al que necesito analizar
    if ( ( (port&a) == a) == 1 )            //hago un AND con el puerto y el bit y compruebo si el resultado es igual al bit asi verifico si el bit esta encedido o apagado,
    {
        c = 1;                              //si esta prendido entonces devuelvo un 1
    }
    else
    {
        c = 0;                              // si esta apagado entonces devuelvo 0
    }
    return c;
}

///////////////////BITTOGGLE//////////////////////

void bitToggle (int data, char puerto){
    if ((puerto == 'A')||(puerto == 'a')){
        data +=8;
    }
    uint16_t port = r_port();
    unsigned int a = potencia (2 , data);  //obtengo el valor del bit al que necesito analizar
    if ( ( (port&a) == a) == 1 )            //hago un AND con el puerto y el bit y compruebo si el resultado es igual al bit asi verifico si el bit esta encedido o apagado,
    {
        port = port - a;                    // si esta encendido lo apago
    }
    else
    {
        port = port + a;                    // si esta apagado lo enciendo
    }
    w_port(port);
}
///////////////////MASKON//////////////////////

void maskOn (int data, char puerto){
   if ((puerto == 'A')||(puerto == 'a')){
        data +=8;
    }
    uint16_t port = r_port();
    int p;                              //genero variables locales para luego analizar bit a bit del puerto y la mascara
    int m;                          
    for ( int i = 0; i<8; i++ )         //voy bit por bit verificando cuales tengo que encender.
    {
        m = bitGet (i, puerto);           //verifico si el bit esta encendio o apagado en la mascara
        p = bitGet (i, puerto);           //verifico si el bit esta encendio o apagado en el puerto
        if ( (p == 0) &&  (m == 1) )    //si hay un bit apagado en el puerto y encendido en la mascara enciendo el bit en el puerto
        {                               //llamando a bitSet con el puerto y el bit a cambiar.
            bitSet (i, puerto);
        }
    }
    w_port(port);
}

///////////////////MASKOFF//////////////////////

void maskOff (int data, char puerto){
    if ((puerto == 'A')||(puerto == 'a')){
        data +=8;
    }
    uint16_t port = r_port();
    int p;                              //genero variables locales para luego analizar bit a bit del puerto y la mascara
    int m; 
    for ( int i = 0; i<8; i++ )         //voy bit por bit verificando cuales tengo que apagar .
    {
        m = bitGet (i, puerto);           //verifico si el bit esta encendio o apagado en la mascara
        p = bitGet (i, puerto);           //verifico si el bit esta encendio o apagado en el puerto
        if ( (p == 1) &&  (m == 1) )    //si hay un bit encendido en el puerto y encendido en la mascara apago el bit en el puerto
        {                               //llamando a bitClr con el puerto y el bit a cambiar.
            bitClr (i,puerto);
        }
    }
    w_port(port);
}

///////////////////MASKTOGGLE//////////////////////

void maskToggle (int data, char puerto){
   if ((puerto == 'A')||(puerto == 'a')){
        data +=8;
    }
    uint16_t port = r_port();
    int p;                              //genero variables locales para luego analizar bit a bit del puerto y la mascara
    int m;
    for ( int i = 0; i<8; i++ )         //voy bit por bit verificando cuales tengo que apagar o prender
    {
        m = bitGet (i, puerto);           //verifico si el bit esta encendio o apagado en el puerto
        p = bitGet (i, puerto);           //verifico si el bit esta encendio o apagado en la mascara
        if ( ( (p == 0) &&  (m == 1) ) || ( (p == 1) &&  (m == 1) ) )  //si hay un bit encendido en el puerto y encendido en la mascara apago el bit en el puerto
        {                                                               //si hay un bit apagado en el puerto y encendido en la mascara enciendo el bit en el puerto
            bitToggle (i, puerto);
        }
    }
    w_port(port);
}

/////////////POTENCIA/////////////////////

int potencia(int x,int n){
    int i;                      //genero variable local para utilizarla como contador
    int num = 1;                //inicializo variable con 1 para utilizarla luego
    for (i = 0; i < n; ++i)     //genero un for hasta alcanzar las veces que quiero multiplicar al numero
    {
        num *= x;               //multiplico num por el valor llamado y lo guardo en num hasta alcanzar las veces que quiero multiplicarlo
    }
    return(num);
}
///////////ESTADI PORT A////////////////////

    unsigned int r_portA (void){			//funcion que se encarga de leer el puerto A

	unsigned int estado=0;				//variable donde queda guardado el resultado

	if((p.puertAB.PortA.bits.b0)==1)					//si el primero esta prendido entonces sumo a estado 1
	{
		estado +=1;
	}
	if((p.puertAB.PortA.bits.b1)==1)					//si el segundo esta prendido entonces sumo a estado 2
	{
		estado +=2;
	}
	if((p.puertAB.PortA.bits.b2)==1)					//si el tercer esta prendido entonces sumo a estado 4
	{
		estado +=4;
	}
	if((p.puertAB.PortA.bits.b3)==1)					//si el cuarto esta prendido entonces sumo a estado 8
	{
		estado +=8;
	}
	if((p.puertAB.PortA.bits.b4)==1)					//si el quinto esta prendido entonces sumo a estado 16
	{
		estado +=16;
	}
	if((p.puertAB.PortA.bits.b5)==1)					//si el sexto esta prendido entonces sumo a estado 32
	{
		estado +=32;
	}
	if((p.puertAB.PortA.bits.b6)==1)					//si el septimo esta prendido entonces sumo a estado 64
	{
		estado +=64;
	}
	if((p.puertAB.PortA.bits.b7)==1)					//si el ultimo esta prendido entonces sumo a estado 128
	{
		estado +=128;
	}
	return estado;						//devuelvo el estado de port A
}







