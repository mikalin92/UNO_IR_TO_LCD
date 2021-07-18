#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include <IRremoteInt.h>




//change "7" to your pin. value
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

//change/delete if your remote is not "car mp3"
const unsigned long STOP_CODE=4294967295uL;

const int CH_MINUS=10;
const int CH=11;
const int CH_PLUS=12;

const int PREV=13;
const int NEXT=14;
const int PLAY_PAUSE=15;

const int VOL_MINUS=16;
const int VOL_PLUS=17;
const int EQ=18;

const int ONE_HUND_PLUS=19;
const int TWO_HUND_PLUS=20;



//change "0x3F" to your reg. value
LiquidCrystal_I2C lcd(0x3F, 16, 2);
Servo servo;

int turn_angle=0;
const int DIGIT_MULTIPLYER=10;


//change cases if your remote is not "car mp3"
int getButton(unsigned long value){
    switch(value){
      case 16738455:
      return 0;
      break;
      case 16724175:
      return 1;
      break;
      case 16718055:
      return 2;
      break;
      case 16743045:
      return 3;
      break;
      case 16716015:
      return 4;
      break;
      case 16726215:
      return 5;
      break;
      case 16734885:
      return 6;
      break;
      case 16728765:
      return 7;
      break;
      case 16730805:
      return 8;
      break;
      case 16732845:
      return 9;
      break;

      case 16753245:
      return CH_MINUS;
      break;
      case 16736925:
      return CH;
      break;
      case 16769565:
      return CH_PLUS;
      break;
      case 16720605:
      return PREV;
      break;
      case 16712445:
      return NEXT;
      break;
      case 16761405:
      return PLAY_PAUSE;
      break;
      case 16769055:
      return VOL_MINUS;
      break;
      case 16754775:
      return VOL_PLUS;
      break;
      case 16748655:
      return EQ;
      break;
      case 16750695:
      return ONE_HUND_PLUS;
      break;
      case 16756815:
      return TWO_HUND_PLUS;
      break;
            
      default:
      return 9999;
      break;
  }
  
}

String button2str(int value){
    if(value<10){
      String retval="";
      retval+=value;
      return retval;  
    }else{
      String retval="";
      switch(value){
        case CH_MINUS:
        retval+="Channel-";
        break;
        case CH:
        retval+="Channel";
        break;
        case CH_PLUS:
        retval+="Channel+";
        break;
        case PREV:
        retval+="|<<";
        break;
        case NEXT:
        retval+=">>|";
        break;
        case PLAY_PAUSE:
        retval+=">||";
        break;
        case VOL_MINUS:
        retval+="-";
        break;
        case VOL_PLUS:
        retval+="+";
        break;
        case EQ:
        retval+="Equalizer";
        break;
        case ONE_HUND_PLUS:
        retval+="100+";
        break;
        case TWO_HUND_PLUS:
        retval+="200+";
        break;
        
      }
      return retval;
    }
  
}


void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  //servo.attach(11);
  //servo.write(0);
  
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.print("Initialized");
  delay(500);
  lcd.clear();
  lcd.print("Input>");
  
  
}

void loop(){
  if (irrecv.decode(&results)){
    Serial.println(results.value);
    
    if(getButton(results.value)<10&&results.value>=0){
      lcd.print(button2str(getButton(results.value)));
      turn_angle*=DIGIT_MULTIPLYER;
      turn_angle+=getButton(results.value);
    }
    if(getButton(results.value)==EQ){
      lcd.clear();
      servo.attach(11);
      delay(250);
      servo.write(turn_angle);
      delay(900);
      servo.detach();
      turn_angle=0;
      lcd.print("Input>");  
    }


    
    
    irrecv.resume();
  }
}
