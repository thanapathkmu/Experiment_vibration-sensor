#ifndef GOERTZEL_H
#define GOERTZEL_H

typedef struct {
    int type;
    int N;
    float TIME_S;
    float SAMPLING_RATE;
    float coeff;
    float Q1;
    float Q2;
} Goertzel;

void Goertzel_Init(Goertzel *goertzel, int type);
void Goertzel_SetNumberCalculation(Goertzel *goertzel, int number);
void Goertzel_SetSamplingRate(Goertzel *goertzel, float rate);
void Goertzel_InitGoertzel(Goertzel *goertzel, float target_frequency);
float Goertzel_Magnitude(Goertzel *goertzel, float *signal, int size);

#endif


/*
variable
  #define GOERTZEL_CALCULATION_SAMPLE     150
  #define SAMPLING_RATE 10000.0f
  #define ANALOG_PIN 35
  
  Goertzel* goertzel;
  float inputSignal[GOERTZEL_CALCULATION_SAMPLE];
  int inputSignalInt[GOERTZEL_CALCULATION_SAMPLE];
  int time_step = (int)(1000000.0f/SAMPLING_RATE);
  int targetFrequency = 50;
  int indexSignalInt = 0;
  int indexSignal = 0;
  float magnitude = 0;

  // Timer0 Configuration Pointer (Handle)
  hw_timer_t *Timer0_Cfg = NULL;
  int timerCount = 0;
  int printFlag = 0;

timer
  inputSignalInt[indexSignalInt++] = analogRead(ANALOG_PIN);
  if (indexSignalInt >= GOERTZEL_CALCULATION_SAMPLE){indexSignalInt = 0;}

init
  // Configure Timer0 Interrupt
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, time_step, true);
  timerAlarmEnable(Timer0_Cfg);

  // Goertzel init
  goertzel = new Goertzel( GOERTZEL_CALCULATION_SAMPLE );
  goertzel->SetNumberCalculation( GOERTZEL_CALCULATION_SAMPLE );
  goertzel->SetSamplingRate( SAMPLING_RATE );
  goertzel->InitGoertzel( targetFrequency );

  Serial.begin(115200);
  pinMode(ANALOG_PIN, INPUT);
run
  if (indexSignalInt != indexSignal){
    inputSignal[indexSignal] = inputSignalInt[indexSignal];
    indexSignal++;
    if (indexSignal >= GOERTZEL_CALCULATION_SAMPLE){indexSignal = 0;}
  }
  if (Serial.available() > 0){
    targetFrequency = Serial.read();
    printFlag = 1;
  }
  if ((printFlag == 1) && (indexSignal == 0)){
    printFlag = 0;
    goertzel->InitGoertzel( targetFrequency );
    magnitude = goertzel->Goertzel_Magnitude( inputSignal, GOERTZEL_CALCULATION_SAMPLE );
    Serial.print("magnitude = ");
    Serial.println(magnitude);
  }
*/
