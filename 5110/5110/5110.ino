    #include <PCD8544.h>
     PCD8544 lcd;
     int CO2 = 561;
     float Temp = 23.1;
     float Press = 100174.4;
     int LDR = 76;
    void setup() {
       lcd.begin(84, 48);
    }
    void loop() {
      lcd.setCursor(0, 0);
      lcd.print("   Logger");
      lcd.setCursor(0, 1);
      lcd.print("Co2: ");
      lcd.print(CO2);
      lcd.print("ppm");
      lcd.setCursor(0, 2);
      lcd.print("Temp: ");
      lcd.print(Temp);
      lcd.print("C");
      lcd.setCursor(0, 3);
      lcd.print("Press: ");
      lcd.setCursor(10, 4);
      lcd.print(Press/1000);
      lcd.print(" kPa");
      lcd.setCursor(0, 5);
      lcd.print("LDR: ");
      lcd.print(LDR);
     
      delay(2000);
     }
