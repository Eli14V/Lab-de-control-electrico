/*Se establecen los vectores con las entradas y las salidas
además de utilizar boolean para definir los false de una manera más practica
evitando el estar definiendo tantas variables, se usan vectores para acortar*/
const int PinEntrada[4] = {2,3,4,5};
const int PinSalf1[3] = {6,7,8};
const int PinSalf2[3] = {9,10,11};
boolean entradas[4]; //mismo numero que las entradas
boolean resultlog[6] = {false,false,false,false,false,false};

/*En void setup se utiliza el ciclo for para poder leer las entradas
mediante la suma de i++ se logra establecer las 4 entradas de los pines
recordar que los valores van de 0 a 3
Se hace lo mismo para establecer los pines de salida*/
  void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
  
    for(int i = 0; i < 4; i++) {
      pinMode(PinEntrada[i], INPUT);
    }
  
    for(int i = 0; i < 3; i++ ) {
      pinMode(PinSalf1[i], OUTPUT);
    }

    for(int i = 0; i < 3; i++){
      pinMode(PinSalf2[i], OUTPUT);
    }
  }

/*En void loop se realizan la lectura de las entradas y se escriben las salidas*/
  void loop() {
    // put your main code here, to run repeatedly:

    //se leen las entradas
    for(int i=0; i<4; i++){
      entradas[i] = digitalRead(PinEntrada[i]);
    }

    //programa:
    resultlog[0] = f1SDP(entradas[0],entradas[1],entradas[2],entradas[3]);
    resultlog[1] = f1PDS(entradas[0],entradas[1],entradas[2],entradas[3]);
    resultlog[2] = f1NAND(entradas[0],entradas[1],entradas[2],entradas[3]);
    resultlog[3] = f2SDP(entradas[0],entradas[1],entradas[2],entradas[3]);
    resultlog[4] = f2PDS(entradas[0],entradas[1],entradas[2],entradas[3]);
    resultlog[5] = f2NOR(entradas[0],entradas[1],entradas[2],entradas[3]);



    //se escriben las salidas
    for(int i = 0; i < 3; i++) {
      digitalWrite(PinSalf1[i],resultlog[i]);
    }
    
    for(int i = 0; i < 3; i++) {
      digitalWrite(PinSalf2[i],resultlog[i+3]);
    }

    //Imprimir entradas:
    Serial.print("Entradas:");
    for(int i = 0; i < 4; i++){
      Serial.print(entradas[i]);
      Serial.print(" ");
    }
    //Imprimir salidas:
    Serial.print("Salidas F1:");
    for(int i =0; i < 3; i++){
      Serial.print(resultlog[i]);
      Serial.print(" ");
    }

    Serial.print("Salidas F2:");
    for(int i =3; i < 6; i++){
      Serial.print(resultlog[i]);
      Serial.print(" ");
    }
    Serial.println();

    delay(200);
  }
//F1
  bool f1SDP(bool a,bool b,bool c,bool d){
    return (a && b) || (b && d) || (a && c && d);
  }


  bool f1PDS(bool a, bool b, bool c, bool d){
    return (a || b) && (a || d) && (b || d) && (b || c);
  }

  bool f1NAND(bool a, bool b, bool c, bool d){
    return !(!(a && b) && !(b && d) && !(a && c && d));
  }


//F2
  bool f2SDP(bool a, bool b, bool c, bool d){
    return (a && !b && !c && !d) || (!a &&  !b && c) || (a && b && c) || (a && b && d);
  }

  bool f2PDS(bool a, bool b, bool c, bool d){
    return (a || c) && ( a || !b) && (b || c || !d) && (!b || c || d) && (!a || b || !c);
  }

  bool f2NOR(bool a, bool b, bool c, bool d){
    return !(!(a || c) || !(a || !b) || !(b || c || !d) || !(!b || c || d) || !(!a || b || !c));
  }
