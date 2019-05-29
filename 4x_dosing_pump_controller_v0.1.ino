#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// long line to scroll
char * LargeText = "      Calibrate the pump by manually dispensing 100ml of liquid      ";
int iLineNumber = 1;// Line number to show your string (Either 0 or 1)
int iCursor = 0;
int charsOnScreen = 13;// how many characters the message will take on screen

#define KeyOk 13 //connect wire 1 to pin 13
#define KeyDown 12 //connect wire 2 to pin 12
#define KeyUp 11 //connect wire 3 to pin 11
#define KeyLeft 10 //connect wire 4 to pin 10
#define KeyRight 9 //connect wire 4 to pin 5
#define Pump1 0 //connect wire 1 to pin 0
#define Pump2 1 //connect wire 1 to pin 1
#define Pump3 2 //connect wire 1 to pin 2
#define Pump4 3 //connect wire 1 to pin 3

int MenuPage =10;
int MenuPageOld =10;
int SelectedPump = 1;

int Pump1Vol = 10;
int Pump2Vol = 20;
int Pump3Vol = 30;
int Pump4Vol = 40;

String Pump1Name = "Pump 1";
String Pump2Name = "Pump 2";
String Pump3Name = "Pump 3";
String Pump4Name = "Pump 4";

bool Pump1State = true;
bool Pump2State = true;
bool Pump3State = false;
bool Pump4State = false;

bool Pump1Calibrating = false;
bool Pump2Calibrating = false;
bool Pump3Calibrating = false;
bool Pump4Calibrating = false;

// custom characters
byte PlayChar[] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11110,
  B11100,
  B11000,
  B10000
};
byte WallChar[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};
void setup() {
  Serial.begin(9600); 
  // set pins as inputs
  pinMode(KeyOk, INPUT_PULLUP);
  pinMode(KeyDown, INPUT_PULLUP);
  pinMode(KeyUp, INPUT_PULLUP);
  pinMode(KeyLeft, INPUT_PULLUP); 
  pinMode(KeyRight, INPUT_PULLUP);
  // set pins as outputs
  pinMode(Pump1, OUTPUT);
  pinMode(Pump2, OUTPUT);  
  pinMode(Pump3, OUTPUT);  
  pinMode(Pump4, OUTPUT);    
  // initialize the LCD
  lcd.begin();
  lcd.createChar(0, PlayChar);
  lcd.createChar(1, WallChar);
  // Turn on the blacklight and print a message.
  MenuDisplay(MenuPage);
}

void loop() {
  int KeyOkS = digitalRead(KeyOk);// read if KeyOk is pressed
  int KeyDownS = digitalRead(KeyDown);// read if KeyDown is pressed
  int KeyUpS = digitalRead(KeyUp);// read if KeyUp is pressed
  int KeyLeftS = digitalRead(KeyLeft);// read if KeyLeft is pressed 
  int KeyRightS = digitalRead(KeyRight);// read if KeyRight is pressed 
  
  //Change menu
    if(!KeyOkS)
  {
     switch (MenuPage)
     {
        case 10:
          MenuPage = 10;
          break;
        case 11:
          MenuPage = 10;
          break;
        case 12:
          MenuPage = 10;
          break;
        case 13:
          MenuPage = 10;
          break;
        case 14:
          MenuPage = 10;
          break;
        case 15:
          MenuPage = 10;
          break;
     }
  }
  if(!KeyDownS)
  {
     switch (MenuPage)
     {
        case 10:
          MenuPage = 11;
          break;
        case 11:
          MenuPage = 12;
          break;
        case 12:
          MenuPage = 13;
          break;
        case 13:
          MenuPage = 14;
          break;
        case 14:
          MenuPage = 15;
          break;
        case 15:
          //TODO
          break;
     }
  }
  if(!KeyUpS)
  {
     switch (MenuPage)
     {
        //case 10:
          //TODO
          break;
        case 11:
          MenuPage = 10;
          break;
        case 12:
          MenuPage = 11;
          break;
        case 13:
          MenuPage = 12;
          break;
        case 14:
          MenuPage = 13;
          break;
        case 15:
          MenuPage = 14;
          break;
     }
  }
  if(!KeyLeftS)
  {
     switch (MenuPage)
     {
        case 10:
          ChangeSelectedPump('L');
          break;
        case 11:
          ChangePumpState();
          break;
        case 12:
          ChangeSelectedPumpVol('L');
          break;
        case 13:
          //TODO
          break;
        case 14:
          //TODO
          break;
        case 15:
          //TODO
          break;
     }
  }
  if(!KeyRightS)
  {
     switch (MenuPage)
     {
        case 10:
          ChangeSelectedPump('R');
          break;
        case 11:
          ChangePumpState();
          break;
        case 12:
          ChangeSelectedPumpVol('R');
          break;
        case 13:
          //TODO
          break;
        case 14:
          //TODO
          break;
        case 15:
          //TODO
          break;
     }
  }
   
  if(MenuPage != MenuPageOld)
  {
      MenuDisplay(MenuPage);
      MenuPageOld = MenuPage;
  }
       if(!KeyOkS){
      Serial.println("key Ok is pressed");
     }
     if(!KeyDownS){
      Serial.println("key Down is pressed");
            Serial.print("MenuPage:");
            Serial.print(MenuPage);
            Serial.println();
            Serial.print("SelectedPump:");
            Serial.print(SelectedPump);
            Serial.print(SelectedPumpState());
            Serial.println();
     }
     if(!KeyUpS){
      Serial.println("key Up is pressed");
            Serial.print("MenuPage:");
            Serial.print(MenuPage);
            Serial.println();
            Serial.print("SelectedPump:");
            Serial.print(SelectedPump);
            Serial.print(SelectedPumpState());
            Serial.println();
     }
     if(!KeyLeftS){
      Serial.println("key Left is pressed");
            Serial.print("MenuPage:");
            Serial.print(MenuPage);
            Serial.println();
            Serial.print("SelectedPump:");
            Serial.print(SelectedPump);
            Serial.print(SelectedPumpState());
            Serial.println();
     }     
     if(!KeyRightS){
      Serial.println("key Right is pressed");
            Serial.print("MenuPage:");
            Serial.print(MenuPage);
            Serial.println();
            Serial.print("SelectedPump:");
            Serial.print(SelectedPump);
            Serial.print(SelectedPumpState());
            Serial.println();
     }
     if (MenuPage == 12 && !KeyRightS || MenuPage == 12 && !KeyLeftS )
     {
        delay(100);     
     }
     else if(MenuPage == 15 && !Pump1Calibrating && !Pump2Calibrating && !Pump3Calibrating && !Pump4Calibrating)
     {
        UpdateLCDDisplay(); // Scoll text by 1 character
        delay(200); 
     }
     else
     {
        delay(350);     
     }

}//--------------- End of loop() loop ---------------------

// Enable Disable Pumps
void ChangePumpState()
{
  if(SelectedPump == 1)
  {
    if(!Pump1State) Pump1State = true;
    else if(Pump1State) Pump1State = false; 
  }
  else if(SelectedPump == 2)
  {
    if(!Pump2State) Pump2State = true;
    else if(Pump2State) Pump2State = false; 
  }
  else if(SelectedPump == 3)
  {
    if(!Pump3State) Pump3State = true;
    else if(Pump3State) Pump3State = false; 
  }
  else if(SelectedPump == 4)
  {
    if(!Pump4State) Pump4State = true;
    else if(Pump4State) Pump4State = false; 
  }
  MenuDisplay(MenuPage);
}

//change selected pump
void ChangeSelectedPump(char Direction)
{
  if (Direction == 'L' && SelectedPump > 1)
  {
    SelectedPump = SelectedPump -1;
  }
  else if (Direction == 'R' && SelectedPump < 4)
  {
    SelectedPump = SelectedPump +1;
  }
  MenuDisplay(MenuPage);  
}

//change selected pump dispensed volume
void ChangeSelectedPumpVol(char Direction)
{
  int volume = SelectedPumpVol();
  if (Direction == 'L' && volume > 1)
  {
    volume = volume -1;
  }
  else if (Direction == 'R' && volume < 500)
  {
    volume = volume +1;
  }

  switch (SelectedPump)
  {
    case 1:
      Pump1Vol = volume;
      break;
    case 2:
      Pump2Vol = volume;
      break;
    case 3:
      Pump3Vol = volume;
      break;
    case 4:
      Pump4Vol = volume;
      break;
  }
  MenuDisplay(MenuPage);  
}
//Print Selected Pump Name
String SelectedPumpName()
{
  String str = "";
  if (SelectedPump == 1)str = Pump1Name;
  else if (SelectedPump == 2)str = Pump2Name;
  else if (SelectedPump == 3)str = Pump3Name;
  else if (SelectedPump == 4)str = Pump4Name;
  return str;
}
String SelectedPumpState()
{
  String str = "";
  if (SelectedPump == 1)
  {
    if (Pump1State)str = "Enabled";
    else str = "Disabled";
  }
  else if (SelectedPump == 2)
  {
    if (Pump2State)str = "Enabled";
    else str = "Disabled";
  }
  else if (SelectedPump == 3)
  {
    if (Pump3State)str = "Enabled";
    else str = "Disabled";
  }
  else if (SelectedPump == 4)
  {
    if (Pump4State)str = "Enabled";
    else str = "Disabled";
  }
  return str;
}
int SelectedPumpVol()
{
  int vol = 0;
  if (SelectedPump == 1)vol = Pump1Vol;
  else if (SelectedPump == 2)vol = Pump2Vol;
  else if (SelectedPump == 3)vol = Pump3Vol;
  else if (SelectedPump == 4)vol = Pump4Vol;
  return vol;
}
// refresh display
// scrolling line
void UpdateLCDDisplay()
{
  int iLenOfLargeText = strlen(LargeText);// Calculate lenght of string.
  if (iCursor == (iLenOfLargeText - 1) )// Reset variable for rollover effect.
  {
    iCursor = 0;
  }
  //lcd.clear();
  lcd.setCursor(0,iLineNumber);
  
  if(iCursor < iLenOfLargeText - charsOnScreen)// This loop exicuted for normal 16 characters.
  {
    for (int iChar = iCursor; iChar < iCursor + charsOnScreen ; iChar++)
    {
      lcd.print(LargeText[iChar]);
    }
  }
  else
  {
    for (int iChar = iCursor; iChar < (iLenOfLargeText - 1) ; iChar++)//  This code takes care of printing charecters of current string.
    {
      lcd.print(LargeText[iChar]);
    }
    for (int iChar = 0; iChar <= charsOnScreen - (iLenOfLargeText - iCursor); iChar++)//  Reamining charecter will be printed by this loop.
    {
      lcd.print(LargeText[iChar]);   
    }
  }
  iCursor++;
}
void MenuDisplay(int page)
{
    switch (page)
    {
      case 10:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(SelectedPumpName());
        lcd.setCursor(13,0);
        lcd.print("< >");
        lcd.setCursor(0,1);
        lcd.print("* " + SelectedPumpState());
        break;
      case 11:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(SelectedPumpName());
        lcd.setCursor(0,1);
        lcd.print("* " + SelectedPumpState());
        lcd.setCursor(13,1);
        lcd.print("< >");
        break;
      case 12:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(SelectedPumpName());
        lcd.setCursor(0,1);
        lcd.print("* Vol:" + String(SelectedPumpVol()) + "ml");
        lcd.setCursor(13,1);
        lcd.print("< >");
        break;
      case 13:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(SelectedPumpName());
        lcd.setCursor(0,1);
        lcd.print("* When:" "12:15");
        lcd.setCursor(13,1);
        lcd.print("< >");
        break;
      case 14:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(SelectedPumpName());
        lcd.setCursor(0,1);
        lcd.print("* Repeat:" "24hrs.");
        lcd.setCursor(13,1);
        lcd.print("< >");
        break;
      case 15:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(SelectedPumpName());
        lcd.setCursor(0,1);
        lcd.setCursor(13,1);
        lcd.write(1);
        lcd.setCursor(14,1);
        lcd.print("Ok");
        break;
    }
 
}
