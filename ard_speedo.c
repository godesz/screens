#include <TFT.h>  // Arduino LCD library
#include <SPI.h>
#include <SoftwareSerial.h>

#define cs   10
#define dc   9
#define rst  8


SoftwareSerial BTSerial(1,0);
TFT TFTscreen = TFT(cs, dc, rst);
const byte ledPin1 = 13;  //test1 LED
const byte ledPin3 = 6; //gomb LED
int piezzo_pin = 7;
volatile byte state = LOW;
const int buttonpin = 5; //nyomogomb programvalasztos
const int buttonpin1 = 12; //nyomÄ‚Ĺ‚gomb indito
const int buttonpin2 = 4; //nyomogomb idozito ideje
int button = 0,bp = 0; //gomb state es button press
int button1 = 0; //gomb state es button press
int button2 = 0,bp2 = 1;
unsigned long time,v1=0,v2=0,w1=0,w2=0,i1=0,i2=0,i3=0,i4=0;
unsigned long i5=0,idozito=1,felido=0; //idozito megadasa percben
float v3=0.0,w3=0.0,v4=0.0,w4=0.0;
int ora,perc,mperc,mil; //ora szamolasok
unsigned int val=0, val1=0, i;//1.v. erzekelesek szama
unsigned int inval=0, inval1=0;//2.v. ezekelesek szama
unsigned int tavolsag=1000; //versenytav m-ben
int kerekmeret = 2170; //kerek kerulete
float ker=2.17,ta1,ta2;
char v3Print[8],w3Print[8],w3Print_prev[8],v3Print_prev[8],tav1[10],tav2[10];
String v3s,w3s,o,p,m,ms,t1,t2,data;


void setup()

{

  BTSerial.begin(115200);
  BTSerial.print("AT\r\n");
  BTSerial.print("AT+NAMEGOLDSPRINT\r\n");
TFTscreen.begin();
TFTscreen.background(0, 0, 0);
TFTscreen.stroke(255, 255, 255);
TFTscreen.setTextSize(1);
pinMode(piezzo_pin, OUTPUT);
pinMode(ledPin1, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(buttonpin, INPUT);
pinMode(buttonpin1, INPUT);
pinMode(buttonpin2, INPUT);
attachInterrupt(0, test, CHANGE);
attachInterrupt(1, test2, CHANGE);
Serial.begin(9600);
Serial.println("Betoltes..");
}

void software_Reset() 
{
asm volatile ("  jmp 0");  
}  

void test()
{
      if(state = !state){
        w2=w1;
        w1=millis();
        w3=((1.0*kerekmeret/(w1-w2))*3.6);
        //Serial.print("Sebesseg 1: \t");
        //Serial.print(w3,3);
        //Serial.print("\t");
        //Serial.println("km/h");
        inval++;
        }
        if (inval==1){i1=millis();}
        if(w3>w4){w4=w3;}}

void test2()
{ if(state = !state){
  v2=v1;
  v1=millis();
  v3=((1.0*kerekmeret/(v1-v2))*3.6);

  //Serial.print("\t");
  //Serial.print("Sebesseg 2: \t");
  //Serial.print(v3,3);
  //Serial.print("\t");
  //Serial.println("km/h");
  val++;}
        if (v3>v4){(v4=v3);}
        if (val==1){i3=millis();}

  }



void loop()
{   
/*if(millis()==w1+2500){w3=0.0;
                      w3s=String(w3,3);
                      w3s.toCharArray(w3Print, 8);}
if(millis()==v1+2500){v3=0.0;
                      v3s=String(v3,3);
                      v3s.toCharArray(v3Print, 8);}*/
  if(bp > 9)
        {bp=0;
        inval=0;
        inval1=0;
        val=0;
        val1=0;
        v3=0.0;
        w3=0.0;
        TFTscreen.stroke(255, 255, 255);}
  if(button == 1){delay(200);}
  if(button1 == 1){delay(200);}
  if(button2 == 1){delay(200);}

  button2=digitalRead(buttonpin2);
  button1 = digitalRead(buttonpin1);
  button = digitalRead(buttonpin);


switch(bp){

    case 0:
      TFTscreen.text("Egyes versenyprogram", 0, 0);
      TFTscreen.text("Aki a megadott tavot a legr\novidebb ido alatt teljesiti\naz nyer.\n ", 0, 9);
      TFTscreen.text("A feher gomb segitsegevel \nvalasszon az alabbi menu\npontok kozul!\n ", 0, 35);
      TFTscreen.text("A kek gomb tovabb.\n ", 0, 60);
      TFTscreen.text("Zold gomb START!\n ", 0, 70);

      TFTscreen.text("5 km\n ", 0, 90);
      TFTscreen.text("10 km\n ", 0, 99);
      TFTscreen.text("15 km\n ", 0, 108);
      digitalWrite(ledPin3, LOW);


      bp++;
      break;
    case 1:
     if(bp2 > 8)
        {bp2=1;
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("15 km\n ", 0, 108);}
      if(button2==1){bp2++;}
      switch(bp2){
        case 1:
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("1 km\n ", 0, 81);
        //Serial.println("1 km");
        bp2++;
        break;
        case 2:
        tavolsag=1000;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;
        case 3:
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("1 km\n ", 0, 81);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("5 km\n ", 0, 90);
        bp2++;
        break;
        case 4:
        tavolsag=5000;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;
        case 5:
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("5 km\n ", 0, 90);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("10 km\n ", 0, 99);
        bp2++;
        break;
        case 6:
        tavolsag=10000;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;
        case 7:
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("10 km\n ", 0, 99);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("15 km\n ", 0, 108);
        bp2++;
        break;
        case 8:
        tavolsag=15000;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;}
      break;
    case 2:

      if(button==1)
            {bp++;
            }
      if(button1==1){TFTscreen.background(0, 0, 0);
        TFTscreen.stroke(0, 0, 255);
        TFTscreen.text("3 ", 80, 5);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 0, 255);
        TFTscreen.text("2 ", 80, 23);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("1", 80, 41);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 255, 0);
        TFTscreen.text("RAJT", 70, 59);
      tone(piezzo_pin,7000,400);
      inval=0;
      inval1=1;
      val=0;
      val1=1;
      v3=0.0;
      w3=0.0;
      delay (200);
      TFTscreen.background(0, 0, 0);}


      if(val==val1){v3s=String(v3,2);
                    v3s.toCharArray(v3Print, 8);
                    val1=(val1)+2;
                    Serial.print("\t\tSebesseg 2: \t");
                    Serial.print(v3,3);
                    Serial.print("\t");
                    Serial.println("km/h");

                    TFTscreen.stroke(0,0,0);
                    TFTscreen.text(v3Print_prev, 0, 39);}
      if(val<val1 && (val*ker)<tavolsag){
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.text("2. versenyzo", 0, 30);
      TFTscreen.text(v3Print, 0, 39);
      TFTscreen.text("km/h", 0, 48);
      v3s.toCharArray(v3Print_prev, 8);
      }

      if(inval==inval1){w3s=String(w3,2);
                        w3s.toCharArray(w3Print, 8);
                        inval1=(inval1)+2;
                        Serial.print("Sebesseg 1: \t");
                        Serial.print(w3,3);
                        Serial.print("\t");
                        Serial.println("km/h");
                        TFTscreen.stroke(0,0,0);
                        TFTscreen.text(w3Print_prev, 0, 9);}
      if(inval<inval1 && (inval*ker)<tavolsag){
                     TFTscreen.stroke(255, 255, 255);
                     TFTscreen.text("1. versenyzo", 0, 0);
                     TFTscreen.text(w3Print, 0, 9);
                     TFTscreen.text("km/h", 0, 18);
                     w3s.toCharArray(w3Print_prev, 8);}



      if((inval*ker)>=tavolsag)
        {
          i2=millis();
          time=i2-i1;
          tone(piezzo_pin,7000,1000);
          TFTscreen.background(0, 0, 0);
          TFTscreen.text("Az egyes versenyzo a\nnyertes!", 0, 0);
          Serial.println("Az egyes versenyzo a nyertes!");

          TFTscreen.text("Ennyi ido alatt sikerult\nteljesitened:", 0, 18);
          ora=time/3600000;
          perc=(time%3600000)/60000;
          mperc=((time%3600000)%60000)/1000;
          mil=(((time%3600000)%60000)%1000);
          Serial.print(ora);
          Serial.print(":");
          Serial.print(perc);
          Serial.print(":");
          Serial.print(mperc);
          Serial.print(".");
          Serial.println(mil);
          o=String(ora);
                    o.toCharArray(v3Print,8);
          p=String(perc);
                    p.toCharArray(v3Print_prev,8);
          m=String(mperc);
                    m.toCharArray(w3Print,8);
          ms=String(mil);
                    ms.toCharArray(w3Print_prev,8);  
          Serial.print(ora);
          Serial.print(":");
          Serial.print(perc);
          Serial.print(":");
          Serial.print(mperc);
          Serial.print(".");
          Serial.println(mil);
          TFTscreen.text(v3Print, 50, 59);
          TFTscreen.text(":", 60, 59);
          TFTscreen.text(v3Print_prev, 70, 59);
          TFTscreen.text(":", 80, 59);
          TFTscreen.text(w3Print, 90, 59);
          TFTscreen.text(",", 100, 59);
          TFTscreen.text(w3Print_prev, 110, 59);
          digitalWrite(ledPin3, HIGH);
          delay(30000);
          digitalWrite(ledPin3, LOW);
          inval=0;
          bp=2;
          TFTscreen.background(0, 0, 0);}
       else if((val*ker)>=tavolsag)
        { i4=millis();
          time=i4-i3;
          tone(piezzo_pin,7000,1000);
          TFTscreen.background(0, 0, 0);
          TFTscreen.text("A kettes versenyzo a\nnyertes!", 0, 0);
                    Serial.println("A kettes versenyzo a nyertes!");
          TFTscreen.text("Ennyi ido alatt sikerult\nteljesitened:", 0, 18);
          ora=time/3600000;
          perc=(time%3600000)/60000;
          mperc=((time%3600000)%60000)/1000;
          mil=(((time%3600000)%60000)%1000);
          Serial.print(ora);
          Serial.print(":");
          Serial.print(perc);
          Serial.print(":");
          Serial.print(mperc);
          Serial.print(".");
          Serial.println(mil);
          o=String(ora);
                    o.toCharArray(v3Print, 8);
          p=String(perc);
                    p.toCharArray(v3Print_prev, 8);
          m=String(mperc);
                    m.toCharArray(w3Print, 8);
          ms=String(mil);
                    ms.toCharArray(w3Print_prev, 8);    

          TFTscreen.text(v3Print, 50, 59);
          TFTscreen.text(":", 60, 59);
          TFTscreen.text(v3Print_prev, 70, 59);
          TFTscreen.text(":", 80, 59);
          TFTscreen.text(w3Print, 90, 59);
          TFTscreen.text(".", 100, 59);
          TFTscreen.text(w3Print_prev, 110, 59);
          digitalWrite(ledPin3, HIGH);
          delay(30000);
          digitalWrite(ledPin3, LOW);
          val=0;
          bp=2;
          TFTscreen.background(0, 0, 0);}


      break;
    case 3:
      digitalWrite(ledPin3, LOW);
      TFTscreen.background(0, 0, 0);
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.text("Kettes versenyprogram", 0, 0);
      TFTscreen.text("Aki a megadott ido alatt \nmesszebbre jut az nyer..\n ", 0, 9);
      TFTscreen.text("A feher gomb segitsegevel \nvalasszon az alabbi menu\npontok kozul!\n ", 0, 27);
      TFTscreen.text("A kek gomb tovabb.\n ", 0, 51);
      TFTscreen.text("Zold gomb START!\n ", 0, 60);
      TFTscreen.text("1 perc\n ", 0, 73);
      TFTscreen.text("5 perc\n ", 0, 82);
      TFTscreen.text("10 perc\n ", 0, 91);
      TFTscreen.text("15 perc\n ", 0, 100);
      TFTscreen.text("Kovetkezo versenyprogram\n ", 0, 109);
      bp++;
      bp2=1;
      break;
   case 4:

      if(bp2 > 10)
        { TFTscreen.stroke(255, 255, 255);
          TFTscreen.text("Kovetkezo versenyprogram\n ", 0, 109);
          bp2=1;}
      if(button2==1){bp2++;}
      switch(bp2){
        case 1:
        //Serial.println("1 perc");
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("1 perc\n ", 0, 73);
        bp2++;
        break;
        case 2:
        idozito=1;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;
        case 3:
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("1 perc\n ", 0, 73);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("5 perc\n ", 0, 82);
        //Serial.println("5 perc");
        bp2++;
        break;
        case 4:
        idozito=5;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;
        case 5:
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("5 perc\n ", 0, 82);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("10 perc\n ", 0, 91);
        //Serial.println("10 perc");
        bp2++;
        break;
        case 6:
        idozito=10;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;
        case 7:
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("10 perc\n ", 0, 91);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("15 perc\n ", 0, 100);
        //Serial.println("15 perc");
        bp2++;
        break;
        case 8:
        idozito=15;
        if(button == 1)
        {bp++;
        TFTscreen.background(0, 0, 0);}
        break;
        case 9:
        TFTscreen.stroke(255, 255, 255);
        TFTscreen.text("15 perc\n ", 0, 100);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("Kovetkezo versenyprogram\n ", 0, 109);
        //Serial.println("Kovetkezo versenyprogram.");
        bp2++;
        break;
        case 10:
        if(button==1)
        {bp=6;
        TFTscreen.background(0, 0, 0);}

        break;}
      time=0;
      felido=0;
      break;

    case 5:

      if(button1==1){
        idozito=idozito*60*1000;
        felido=idozito/2;  
        TFTscreen.background(0, 0, 0);
        TFTscreen.stroke(0, 0, 255);
        TFTscreen.text("3 ", 80, 5);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 0, 255);
        TFTscreen.text("2 ", 80, 23);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("1", 80, 41);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 255, 0);
        TFTscreen.text("RAJT", 70, 59);
      tone(piezzo_pin,7000,400);
      inval=0;
      inval1=0;
      val=0;
      val1=0;
      w3=0.0;
      v3=0.0;
      delay (200);
      TFTscreen.background(0, 0, 0);
      time=millis();
      i5=time+1000;}

      if(val==val1){v3s=String(v3,2);
                    v3s.toCharArray(v3Print, 8);
                    val1=(val1)+2;
                    Serial.print("\t\tSebesseg 2: \t");
                    Serial.print(v3,3);
                    Serial.print("\t");
                    Serial.println("km/h");
                    TFTscreen.stroke(0,0,0);
                    TFTscreen.text(v3Print_prev, 0, 39);}
      if(val<val1 && idozito !=0){


      TFTscreen.stroke(255, 255, 255);
      TFTscreen.text("2. versenyzo", 0, 30);
      TFTscreen.text(v3Print, 0, 39);
      TFTscreen.text("km/h", 0, 48);
      v3s.toCharArray(v3Print_prev, 8);
      }

      if(inval==inval1){w3s=String(w3,2);
                        w3s.toCharArray(w3Print, 8);
                        inval1=(inval1)+2;
                        Serial.print("Sebesseg 1: \t");
                        Serial.print(w3,3);
                        Serial.print("\t");
                        Serial.println("km/h");
                        TFTscreen.stroke(0,0,0);
                        TFTscreen.text(w3Print_prev, 0, 9);}
      if(inval<inval1 && idozito !=0){
                     TFTscreen.stroke(255, 255, 255);
                     TFTscreen.text("1. versenyzo", 0, 0);
                     TFTscreen.text(w3Print, 0, 9);
                     TFTscreen.text("km/h", 0, 18);
                     w3s.toCharArray(w3Print_prev, 8);}


      if(time != 0){

        if(millis()>=i5){
        i5=i5+1000;
        idozito=idozito-1000;}}

      if(idozito==felido && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("FELIDO", 70, 50);
       Serial.println("Felido");
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("FELIDO", 70, 50);}
      if(idozito==5000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("5", 80, 50);
       Serial.println("5");
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("5", 80, 50);}
      if(idozito==4000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("4", 80, 50);
       Serial.println("4");
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("4", 80, 50);}
       if(idozito==3000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("3", 80, 50);
        Serial.println("3");
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("3", 80, 50);}
       if(idozito==2000 && millis()<i5-850)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("2", 80, 50);
        Serial.println("2");
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("2", 80, 50);}
       if(idozito==1000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("1", 80, 50);
        Serial.println("1");
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("1", 80, 50);}

      if(idozito==0)
      {ta1=inval*ker;
       ta2=val*ker;
       tone(piezzo_pin,7000,1000);
       Serial.println("VEGE");
       TFTscreen.background(0,0,0);
       TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("VEGE", 70, 80);
       delay(2000);
       TFTscreen.background(0,0,0);
       t1=String(ta1);
       t1.toCharArray(tav1, 10);
       TFTscreen.stroke(255, 255, 255);
       TFTscreen.text("Egyes versenyzo megtett\ntav:", 0, 0);
       TFTscreen.text(tav1, 0, 18);
       TFTscreen.text("meter", 40, 18);

       Serial.print("Egyes versenyzo megtett tav:\t");
       Serial.print(ta1);
       Serial.println("meter");
       t2=String(ta2);
       t2.toCharArray(tav2, 10);
       TFTscreen.stroke(255, 255, 255);
       TFTscreen.text("Kettes versenyzo megtett\ntav:", 0, 30);
       TFTscreen.text(tav2, 0, 48);
       TFTscreen.text("meter", 40, 48);
       Serial.print("\tKettes versenyzo megtett tav:\t");
       Serial.print(ta2);
       Serial.println("meter");
       if(ta2==ta1)
         {TFTscreen.text("Dontetlen", 40, 100);
          Serial.println("Dontetlen");
          digitalWrite(ledPin3, HIGH);}
            else if(ta2>ta1)
              {TFTscreen.text("Kettes versenyzo\na nyertes", 40, 100);
               Serial.println("Kettes versenyzo a nyertes");
               digitalWrite(ledPin3, HIGH);}
                   else{TFTscreen.text("Egyes versenyzo\na nyertes", 40, 100);
                    Serial.println("Egyes versenyzo a nyertes");
                   digitalWrite(ledPin3, HIGH);}
                   delay(10000);
                   bp=3;}
       if (button==1){bp=3;
                      TFTscreen.background(0,0,0);}

      break;
    case 6:
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.text("Harmas versenyprogram", 0, 0);
      TFTscreen.text("15 masodperc alatt elert\nlegnagyobb sebesseg", 0, 9);
      TFTscreen.text("Zold gomb START!", 0, 25);
      delay(5000);
      digitalWrite(ledPin3, LOW);
      bp++;
      time=0;
      idozito=15;
      TFTscreen.background(0,0,0);
      break;

    case 7:



      if(button1==1){
        idozito=idozito*1000;  
        val=0;
        val1=0;
        v4=0;
        w4=0;
        inval=0;
        inval1=0;
      TFTscreen.background(0, 0, 0);
        TFTscreen.stroke(0, 0, 255);
        TFTscreen.text("3 ", 80, 5);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 0, 255);
        TFTscreen.text("2 ", 80, 23);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 255, 255);
        TFTscreen.text("1", 80, 41);
      tone(piezzo_pin,6500,150);
      delay(1000);
        TFTscreen.stroke(0, 255, 0);
        TFTscreen.text("RAJT", 70, 59);
      Serial.println("RAJT!");
      tone(piezzo_pin,7000,400);
      inval=0;
      inval1=0;
      w3=0;
      w4=0;
      v4=0;
      v3=0;
      val=0;
      val1=0;
      delay (200);
      TFTscreen.background(0, 0, 0);
       time=millis();
      i5=time+1000;}

            if(val==val1){v3s=String(v3,2);
                    v3s.toCharArray(v3Print, 8);
                    val1=(val1)+2;
                    Serial.print("\t\tSebesseg 2: \t");
                    Serial.print(v3,3);
                    Serial.print("\t");
                    Serial.println("km/h");
                    TFTscreen.stroke(0,0,0);
                    TFTscreen.text(v3Print_prev, 0, 39);}
      if(val<val1  && idozito != 0){
      TFTscreen.stroke(255, 255, 255);
      TFTscreen.text("2. versenyzo", 0, 30);
      TFTscreen.text(v3Print, 0, 39);
      TFTscreen.text("km/h", 0, 48);
      v3s.toCharArray(v3Print_prev, 8);
      }

      if(inval==inval1 && idozito != 0){w3s=String(w3,2);
                        w3s.toCharArray(w3Print, 8);
                        inval1=(inval1)+2;
                        Serial.print("Sebesseg 1: \t");
                        Serial.print(w3,3);
                        Serial.print("\t");
                        Serial.println("km/h");
                        TFTscreen.stroke(0,0,0);
                        TFTscreen.text(w3Print_prev, 0, 9);}
      if(inval<inval1  && idozito != 0){
                     TFTscreen.stroke(255, 255, 255);
                     TFTscreen.text("1. versenyzo", 0, 0);
                     TFTscreen.text(w3Print, 0, 9);
                     TFTscreen.text("km/h", 0, 18);
                     w3s.toCharArray(w3Print_prev, 8);}

      if(time != 0){

        if(millis()>=i5){
        i5=i5+1000;
        idozito=idozito-1000;}}
      if(idozito==5000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("5", 80, 50);
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("5", 80, 50);}
      if(idozito==4000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("4", 80, 50);
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("4", 80, 50);}
       if(idozito==3000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("3", 80, 50);
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("3", 80, 50);}
       if(idozito==2000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("2", 80, 50);
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("2", 80, 50);}
       if(idozito==1000 && millis()<i5-900)
      {TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("1", 80, 50);
       tone(piezzo_pin,6500,150);}
       else{TFTscreen.stroke(0, 0, 0);
       TFTscreen.text("1", 80, 50);}

      if(idozito==0){
       tone(piezzo_pin,7000,1000);
       Serial.println("VEGE");
       TFTscreen.background(0,0,0);
       TFTscreen.stroke(0, 0, 255);
       TFTscreen.text("VEGE", 70, 80);
       delay(2000);
       TFTscreen.background(0,0,0);


      time=0;
      idozito=15;
      tone(piezzo_pin,7000,1000);
       Serial.println("VEGE");
       t1=String(w4);
       t1.toCharArray(tav1, 8);
       TFTscreen.stroke(255, 255, 255);
       TFTscreen.text("Egyes versenyzo\nlegynagyobb sebesseg:", 0, 0);
       TFTscreen.text(tav1, 0, 18);
       TFTscreen.text("km/h", 40, 18);
       Serial.print("Egyes versenyzo legynagyobb sebesseg:\t");
       Serial.print(w4,3);
       Serial.println("\tkm/h");
       t2=String(v4);
       t2.toCharArray(tav2, 8);
       TFTscreen.stroke(255, 255, 255);
       TFTscreen.text("Kettes versenyzo\nlegynagyobb sebesseg:", 0, 30);
       TFTscreen.text(tav2, 0, 48);
       TFTscreen.text("km/h", 40, 48);
       Serial.print("\tKettes versenyzo legynagyobb sebesseg:\t");
       Serial.print(v4,3);
       Serial.println("\tkm/h");
       if(w4==v4)
         {TFTscreen.text("Dontetlen", 40, 100);
          Serial.println("Dontetlen");
          digitalWrite(ledPin3, HIGH);}
            else if(v4>w4)
              {TFTscreen.text("Kettes versenyzo\na nyertes", 40, 100);
               Serial.println("Kettes versenyzo a nyertes");
               digitalWrite(ledPin3, HIGH);}
                   else{TFTscreen.text("Egyes versenyzo\na nyertes", 40, 100);
                        Serial.println("Egyes versenyzo a nyertes");
                        digitalWrite(ledPin3, HIGH);}
       delay(20000);
       digitalWrite(ledPin3, LOW);
       TFTscreen.background(0, 0, 0);}
      if(button == 1)
      {bp++;}
      break;
    case 8:
    TFTscreen.background(0, 0, 0);
    TFTscreen.stroke(255, 255, 255);
      TFTscreen.text("Csak sebesseg", 40, 0);
      //Serial.println("Csak sebesseg");
      digitalWrite(ledPin1, HIGH);
      delay(5000);
      inval=0;
      inval1=0;
      val=0;
      val1=0;
      w3=0.0;
      v3=0.0;
      bp++;
    TFTscreen.background(0, 0, 0);
    break;
    case 9:
      if(button1==1){inval=0;
      inval1=0;
      val=0;
      val1=0;
      w3=0.0;
      v3=0.0;}

            if(val==val1){v3s=String(v3,2);
                    v3s.toCharArray(v3Print, 8);
                    val1=(val1)+3;
                    Serial.print("\t");
                    Serial.print("Sebesseg 2: \t");
                    Serial.print(v3,3);
                    Serial.print("\t");
                    Serial.println("km/h");
                    TFTscreen.stroke(0,0,0);
                    TFTscreen.text(v3Print_prev, 0, 39);}
      if(val<val1 && val>1)
      {TFTscreen.stroke(255, 255, 255);
      TFTscreen.text("2. versenyzo", 0, 30);
      TFTscreen.text(v3Print, 0, 39);
      TFTscreen.text("km/h", 0, 48);
      v3s.toCharArray(v3Print_prev, 8);}

      if(inval==inval1){w3s=String(w3,2);
                        w3s.toCharArray(w3Print, 8);
                        inval1=(inval1)+3;
                        Serial.print("Sebesseg 1: \t");
                        Serial.print(w3,3);
                        Serial.print("\t");
                        Serial.println("km/h");
                        TFTscreen.stroke(0,0,0);
                        TFTscreen.text(w3Print_prev, 0, 9);}
        if(inval<inval1 && inval>1)
                    {
                     TFTscreen.stroke(255, 255, 255);
                     TFTscreen.text("1. versenyzo", 0, 0);
                     TFTscreen.text(w3Print, 0, 9);
                     TFTscreen.text("km/h", 0, 18);
                     w3s.toCharArray(w3Print_prev, 8);}
      if(button == 1)
      {bp++;
      TFTscreen.background(0, 0, 0);}
    break;
  }
}




