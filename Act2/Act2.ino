//Se establece la lista boleana de las entradas, las cuales todas son 0
boolean result[4]; //en esta lista se guardaran los resultados de las funciones de los MUX
boolean entr[4] = {false,false,false,false};
//Se establece la lista de los pines input y output
const int In[4] = {2,3,4,8};
const int Out[2] = {6,7};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Se configuran los pines de entrada y los de salida mediante el ciclo for:

  for(int i = 0; i<4; i++){
    pinMode(In[i],INPUT);
  }

  for(int i = 0; i<2; i++){
    pinMode(Out[i],OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  //Se lee lo que hay en el pin de entrada:
  for(int i=0; i<4; i++){
   entr[i] = digitalRead(In[i]);
  }

  //Se establecen que van en cada una de las funciones y en que posicion de la lista ira:
  result[0] = MUX41(entr[0],true,true,!entr[0],entr[2],entr[3]);
  result[1] = MUX42(!entr[0],entr[0],entr[0],false,entr[2],entr[3]);
  result[2] = MUX2X1(result[0],result[1],entr[1]);
  result[3] = MUX8X1(entr[0],true,true,!entr[0],!entr[0],entr[0],entr[0],false,entr[3],entr[2],entr[1]);

  //Se escriben las salidas:
  digitalWrite(Out[0],result[3]);
  digitalWrite(Out[1],result[2]);

  //Se imprimen las entradas:
  Serial.print("a = ");
  Serial.println(entr[0]);
  Serial.print("b = ");
  Serial.println(entr[1]);
  Serial.print("c = ");
  Serial.println(entr[2]);
  Serial.print("d = ");
  Serial.println(entr[3]);


  //Se imprimen las salidas:
  Serial.print("Salida Mux8: ");
  Serial.println(result[3]);
  Serial.print("Salida Mux2: ");
  Serial.println (result[2]);

  delay(400);
}


//Funciones4x1
bool MUX41 (bool I0, bool I1, bool I2, bool I3, bool S0, bool S1) {
  return (I0 && !S1 && !S0) || (I1 && !S1 && S0) || (I2 && S1 && !S0) || (I3 && S1 && S0);
}
bool MUX42 (bool I4, bool I5, bool I6, bool I7, bool S0, bool S1) {
  return (I4 && !S1 && !S0) || (I5 && !S1 && S0) || (I6 && S1 && !S0) || (I7 && S1 && S0);
}

//Funcion 2x1
bool MUX2X1(bool MUX41, bool MUX42, bool S0) {
  return (MUX41 && !S0) || (MUX42 && S0);
  }

   //Funcion del 8X1:
bool MUX8X1 (bool I0,bool I1, bool I2, bool I3, bool I4,bool I5, bool I6, bool I7, bool S0, bool S1, bool S2) {
  return  (I0 && !S0 && !S1 && !S2) || 
          (I1 && S0 && !S1 && !S2 ) || 
          (I2 && !S0 && S1  && !S2) || 
          (I3 && S0 && S1  && !S2 ) || 
          (I4 && !S0  && !S1 && S2) || 
          (I5 && S0  && !S1 && S2 ) || 
          (I6 && !S0  && S1  && S2) || 
          (I7 && S0  && S1  && S2 );

}