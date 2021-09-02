//Programa: Controlador de acesso utilizando display 7 segmentos e TCRT5000
//Carrega a biblioteca SevSeg
#include <SevSeg.h>
#define lotacao 15
SevSeg sevseg;
//Definicoes do display 7 segmentos
byte numDigits = 3; //Define o numero de digitos do visor
byte digitPins[] = {2, 3, 4}; // Cria uma matriz que define os pinos do arduino que serão usado como aterramento
byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // Define quais pinos do arduino estão conectados a cada segmento da tela
bool resistorsOnSegments = false; // 'false' se os resistores estiverem ligados nos pinos de digito
byte hardwareConfig = COMMON_ANODE; //Tipo de display - Anodo Comum
bool updateWithDelays = false;
bool leadingZeros = false; //Use 'true' se voce desejar completar o display com zeros
bool disableDecPoint = false; // Use 'true' se o ponto decimal nao existir ou nao for usado
//Armazena o valor do contador
int contador = 0;
//Ligado ao pino "coletor" do sensor óptico
int pinosensor = A1; //Sensor de Entrada
int pinosensor2 = A3; //Sensor de Saida
int Led = 5; //Buzzer
//Armazena o valor lido pelo sensor (0 ou 1)
int VlrSensor, VlrSensor2, VlrAnterior, VlrAnterior2;
void setup()
{
  Serial.begin(9600);
  //Inicializa o display com as definicoes anteriores
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
               updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90); //Controla a luminosidade do display - 0 a 100
  //Define o pino do sensor optico como entrada
  pinMode(pinosensor, INPUT);
  pinMode(pinosensor2, INPUT);
  pinMode(Led, OUTPUT);
}
void loop()
{
  //Le as informações do pino do sensor
  VlrAnterior = VlrSensor;
  VlrSensor = digitalRead(pinosensor);

  //Verifica se o objeto foi detectado na entrada
  if ((VlrSensor == 0) && (VlrAnterior == 1)) {
    //Incrementa o valor do contador
    delay(50);
    contador++;
    Serial.print("Contador1: ");
    Serial.println(contador);
  }

  //Verifica se o objeto foi identificado na Saída
  VlrAnterior2 = VlrSensor2;
  VlrSensor2 = digitalRead (pinosensor2);

  if ((VlrSensor2 == 0) && (VlrAnterior2 == 1)) {
    //decrementa o valor do contador
    if (contador > 0) {
      contador--;
    }
    Serial.print("Contador2: ");
    Serial.println(contador);
  }
  if (contador >= lotacao) {
    digitalWrite(Led, HIGH);
    contador = lotacao;
  } else {
    digitalWrite(Led, LOW);
  }
  //Atualiza as informacoes no display
  sevseg.setNumber(contador, 0); // Imprime o valor no visor
  sevseg.refreshDisplay(); // Esta função é necessária no final da seção do loop para continuar exibindo o número.
}
