#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
#define altura_deposito 40 // altura del depósito

long tiempo;
// int trigPin = 7;   // triger
// int echoPin = 8;      // echo
float distancia;

// sensor info
int getSensorData() {
   // return random(1,100);

 // lanzamos un pequeño pulso para activar el sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // medimos el pulso de respuesta
  tiempo = (pulseIn(echoPin, HIGH)/2); // dividido por 2 por que es el 
                                       // tiempo que el sonido tarda
                                       // en ir y en volver
  // ahora calcularemos la distancia en cm
  // sabiendo que el espacio es igual a la velocidad por el tiempo
  // y que la velocidad del sonido es de 343m/s y que el tiempo lo 
  // tenemos en millonesimas de segundo
  distancia = float(tiempo * 0.0343);
  
  // y lo mostramos por el puerto serie una vez por segundo
  Serial.println("Distancia: " + String(distancia) + " cm");

   float nivel = 100 - ((distancia / altura_deposito) * 100);

   Serial.println("nivel: " + String(nivel) + "%");

   if (nivel < 0.0) nivel = 0;
   else if (nivel > 100) nivel = 100;
   
  return nivel;

}
// sensor info
int getSensorWaterData() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(trigPin, LOW);
  
  delayMicroseconds(5);
 // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
  tiempo = pulseIn(echoPin, HIGH);
  
  // Calculate the distance:
  distancia = tiempo*0.034/2;
  
  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance = ");
  Serial.print(distancia);
  Serial.println(" cm");

   float nivel = 100 - ((distancia / altura_deposito) * 100);
   
   if (nivel < 0.0) nivel = 0;
   else if (nivel > 100) nivel = 100;

   Serial.println("nivel: " + String(nivel) + "%");
   
  return nivel;
  
  
}
