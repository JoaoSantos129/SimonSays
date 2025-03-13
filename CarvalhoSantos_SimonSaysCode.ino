/*
 *
 *  Author      : João Carvalho Santos
 *  Project     : Jeu du Simon
 *  DATE        : 08 november 2022
 *  VERSION     : 1.0
 *  Description : Simon says game (sequence mode) : 4 LED's will turn on in a sequence, the player has to press the buttons in the same order. Press the 1st button to start
 * 
 */

// libraries
#include <Bounce2.h>

// defines a name for each button pin
#define button1 A2
#define button2 A3
#define button3 A4
#define button4 A5

// defines a name for each led pin
#define ledBlue 2
#define ledYellow 3
#define ledRed 4
#define ledGreen 5

// defines a name for the buzzer pin
#define buzzer 6

// defines de maximum of codes
#define CODES_MAX 31

// initialize global variables
int codesMemory[CODES_MAX];
bool wrongCode = false;
int code;
bool lost = false;

// instantiate Bounce objects
Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();
Bounce debouncer4 = Bounce();

// table with all the different notes needed
const float gameNotes[]={65.41,329.63,261.63,220,164.81,0,400,500,600,700,800,900,1300};

void setup(){
  debouncer1.attach(button1, INPUT_PULLUP); // attaches anti-bounce to pin A2 (first button) as INPUT_PULLUP
  debouncer1.interval(25);                  // anti-bounce interval equals to 25 milliseconds
    
  debouncer2.attach(button2, INPUT_PULLUP); // attaches anti-bounce to pin A3 (second button) as INPUT_PULLUP
  debouncer2.interval(25);                  // anti-bounce interval equals to 25 milliseconds

  debouncer3.attach(button3, INPUT_PULLUP); // attaches anti-bounce to pin A4 (third button) as INPUT_PULLUP
  debouncer3.interval(25);                  // anti-bounce interval equals to 25 milliseconds

  debouncer4.attach(button4, INPUT_PULLUP); // attaches anti-bounce to pin A5 (fourth button) as INPUT_PULLUP
  debouncer4.interval(25);                  // anti-bounce interval equals to 25 milliseconds

  // for loop, each repetition it initializes a led or the buzzer (pin 2 to 5 = leds + pin 6 = buzzer). The loop ends once all of them were initialized
  for (int i = 2; i <= 6; i++){
    pinMode(i, OUTPUT); // initialize pin number i as OUTPUT
  }

  // initialize random number generator 
  randomSeed(analogRead(0));
}

/*
 * this function lights up a led depending on which note is played
 * @param note
 */
void lightShow(int note){
  switch (note){

    //play the first led (blue led) sound (Mi3) and turn the led on
    case 1:
      digitalWrite(ledBlue, HIGH);    // turn on the blue led
      tone(buzzer, gameNotes[note]);  // play the note Mi3
      
      delay(200);                     // leave the led and the buzzer on for 200ms
      
      digitalWrite(ledBlue, LOW);     // turn off the blue led
      noTone(buzzer);                 // turn off the buzzer
      
      delay(70);                      // leave the led and the buzzer off for 70ms
      
      break;

    //play the second led (yellow led) sound (Do3) and turn the led on
    case 2:
      digitalWrite(ledYellow, HIGH);  // turn on the yellow led
      tone(buzzer, gameNotes[note]);  // play the note Do3
      
      delay(200);                     // leave the led and the buzzer on for 200ms
      
      digitalWrite(ledYellow, LOW);   // turn off the yellow led
      noTone(buzzer);                 // turn off the buzzer
      
      delay(70);                      // leave the led and the buzzer off for 70ms
      
      break;

    //play the third led (red led) sound (La2) and turn the led on
    case 3:
      digitalWrite(ledRed, HIGH);     // turn on the red led
      tone(buzzer, gameNotes[note]);  // play the note La3
      
      delay(200);                     // leave the led and the buzzer on for 200ms
      
      digitalWrite(ledRed, LOW);      // turn off the red led
      noTone(buzzer);                 // turn off the buzzer
      
      delay(70);                      // leave the led and the buzzer off for 70ms
      
      break;

    //play the forth led (green led) sound (Mi2) and turn the led on
    case 4:
      digitalWrite(ledGreen, HIGH);   // turn on the green led
      tone(buzzer, gameNotes[note]);  // play the note Mi2
      
      delay(200);                     // leave the led and the buzzer on for 200ms
      
      digitalWrite(ledGreen, LOW);    // turn off the red led
      noTone(buzzer);                 // turn off the buzzer
      
      delay(70);                      // leave the led and the buzzer off for 70ms
      
      break;

    // play the error sound with all the leds turning on and off at the same time
    case 5:
      //for loop, each repetition all the leds turn on while the buzzer plays the error sound, then turns everything off. This loop repeats 3 times
      for(int j = 0; j < 3; j++){
        digitalWrite(ledBlue,HIGH);   // turn on the blue led
        digitalWrite(ledYellow,HIGH); // turn on the yellow led
        digitalWrite(ledRed,HIGH);    // turn on the red led
        digitalWrite(ledGreen,HIGH);  // turn on the green led
        tone(buzzer, gameNotes[0]);   // play the error note
        
        delay(500);                   // leave the leds on and the note be played for 500ms
        
        digitalWrite(ledBlue,LOW);    // turn off the blue led
        digitalWrite(ledYellow,LOW);  // turn off the yellow led
        digitalWrite(ledRed,LOW);     // turn off the red led
        digitalWrite(ledGreen,LOW);   // turn off the green led
        noTone(buzzer);               // turn off the buzzer
        
        delay(500);                   // leave the leds and the buzzer off for 500ms
      }
      
      break;

    // turn off all the leds and the buzzer
    default:
      digitalWrite(ledBlue,LOW);    // turn off the blue led
      digitalWrite(ledYellow,LOW);  // turn off the yellow led
      digitalWrite(ledRed,LOW);     // turn off the red led
      digitalWrite(ledGreen,LOW);   // turn off the green led
      noTone(buzzer);               // turn off the buzzer
      
      break;
  }
}

/*
 * this function plays the victory melody (sounds + leds)
 */
void victoryShow(){
  // for loop, for each repetition plays two sounds and turns on two pairs of leds at a time, the played sound is always higher than the last one. This loop repeats 3 times
  for(int i = 6; i < 12; i = i + 2){
    digitalWrite(ledBlue,HIGH);   // turn on the blue led
    digitalWrite(ledRed,HIGH);    // turn on the red led
    tone(buzzer, gameNotes[i]);   // play a higher sound than the last one (first = 400)
    
    delay(250);                   // leave the leds on and the buzzer play for 250ms
    
    noTone(buzzer);               // turn off the buzzer
    
    delay(250);                   // leave the buzzer turned off for 250ms
    
    digitalWrite(ledBlue,LOW);    // turn off the blue led
    digitalWrite(ledRed,LOW);     // turn off the red led
    digitalWrite(ledYellow,HIGH); // turn on the yellow led
    digitalWrite(ledGreen,HIGH);  // turn on the green led
    
    tone(buzzer, gameNotes[i+1]); // play a higher sound than the last one
    
    delay(250);                   // leave the buzzer play for 250ms
    
    noTone(buzzer);               // turn off the buzzer
    
    delay(250);                   // leave the buzzer turned off for 250ms
    
    digitalWrite(ledYellow,LOW);  // turn off the yellow led
    digitalWrite(ledGreen,LOW);   // turn off the green led
  }
}

/*
 * this function plays the start melody (sounds + leds)
 */
void musicStart(){
  // for loop, each repetition plays a sound and a turns on a led, both are chosen by a generated random number between 1 and 4. This loop repeats 5 times
  for(int i = 1; i <= 5; i++){
    lightShow(random(1,5));       // play the random sound and turn on the respective led
    delay(200);                   // leave the led and the buzzer on for 200ms
  }

  // for loop, for each repetition it plays three sounds where the played note is always higher than the last one, while all the leds turn on and off
  for(int i = 0; i < 3; i++){
    digitalWrite(ledBlue,HIGH);   // turn on the blue led
    digitalWrite(ledYellow,HIGH); // turn on the yellow led
    digitalWrite(ledRed,HIGH);    // turn on the red led
    digitalWrite(ledGreen,HIGH);  // turn on the green led
    tone(buzzer, gameNotes[4-i]); // play a higher sound than the last one
        
    delay(150);                   // leave the buzzer and the leds turned on for 150ms
      
    digitalWrite(ledBlue,LOW);    // turn off the blue led
    digitalWrite(ledYellow,LOW);  // turn off the yellow led
    digitalWrite(ledRed,LOW);     // turn off the red led
    digitalWrite(ledGreen,LOW);   // turn off the green led
    noTone(buzzer);               // turn off the sound/buzzer
        
    delay(150);                   // leave the buzzer and the leds turned off for 150ms
  }
}

/*
 * this function tests if the user pressed the right button
 * @param codeLevel
 * @param codeToTest
 * @return true if the user just lost, or false if the user did not lose yet
 */
bool testCodes(int codeLevel,int codeToTest){
  // tests if the user lost, in that case wrongCode will be true, which will end the game. Else nothing happens, the game continues
  if(codeToTest != codesMemory[codeLevel]){
    wrongCode = true; // wrongCode is now true, the user lost
    return true;
  }else{
    return false;
  }
}

/*
 * this function plays the game
 */
void playGame(){
  // initialize variables
  int codeNumber;
  int pressedButtons[CODES_MAX];

  // restart the variable
  wrongCode = false;
  
  musicStart();
  delay(500); // the game starts a 500ms after the music

  // for loop, for each repetition it generates a new code (1 to 4) and writes each one in codesMemory. The loop will stop when it generated and saved the same amount of codes as CODES_MAX
  for (code = 1; code <= CODES_MAX; code++){
    // create all the codes and put them in codesMemory
    codesMemory[code-1] = random(1,5);

    // for loop, for each repetition it plays the sound and turns on the led corresponding on each code. The loop will stop when all the number of played codes is the same as the level the player is in
    for (int i = 0; i < code; i++) {
      lightShow(codesMemory[i]);  // play the sound and led corresponding to the code
    }

    // restart the variable
    codeNumber = 0;

    // loop while the user did not press the same amount of buttons as the played codes
    while (codeNumber != code){
      // update buttons state
      debouncer1.update();
      debouncer2.update();
      debouncer3.update();
      debouncer4.update();

      // if the first button was pressed, save it in pressedButtons and verify if the user lost
      if(debouncer1.fell()){
        pressedButtons[codeNumber - 1] = 1; // save button 1 as a pressed button for this code
        lightShow(1);                       // play the sound and light on the led corresponding to the first button

        // test if the first button is the wrong one, if it is the user lost
        if(testCodes(codeNumber,pressedButtons[codeNumber - 1]) == true){
          break;                            // break the loop to end the game
        }
        
        codeNumber++;                       // the user did not lose yet, so, the number of codes is incremented

      // else, if the second button was pressed, save it in pressedButtons and verify if the user lost
      }else if(debouncer2.fell()){
        pressedButtons[codeNumber - 1] = 2; // save button 2 as a pressed button for this code
        lightShow(2);                       // play the sound and light on the led corresponding to the second button

        // test if the second button is the wrong one, if it is the user lost
        if(testCodes(codeNumber,pressedButtons[codeNumber - 1]) == true){
          break;                            // break the loop to end the game
        }
  
        codeNumber++;                       // the user did not lose yet, so, the number of codes is incremented

      // else, if the third button was pressed, save it in pressedButtons and verify if the user lost
      }else if(debouncer3.fell()){
        pressedButtons[codeNumber - 1] = 3; // save button 3 as a pressed button for this code
        lightShow(3);                       // play the sound and light on the led corresponding to the third button

        // test if the third button is the wrong one, if it is the user lost
        if(testCodes(codeNumber,pressedButtons[codeNumber - 1]) == true){
          break;                            // break the loop to end the game
        }
  
        codeNumber++;                       // the user did not lose yet, so, the number of codes is incremented

      // else, if the fourth button was pressed, save it in pressedButtons and verify if the user lost
      }else if(debouncer4.fell()){
        pressedButtons[codeNumber - 1] = 4; // save button 4 as a pressed button for this code
        lightShow(4);                       // play the sound and light on the led corresponding to the third button

        // test if the fourth button is the wrong one, if it is the user lost
        if(testCodes(codeNumber,pressedButtons[codeNumber - 1]) == true){
          break;                            // break the loop to end the game
        }
  
        codeNumber++;                       // the user did not lose yet, so, the number of codes is incremented
      }
    }

    // test if the user lost, if it's the case then play the defeat sounds with the leds
    if(wrongCode == true){
      lightShow(5); // play the defeat sounds with the leds
      break;        // break the loop to end the game
    }

    delay(500);     // leave the buzzer and the leds turned off for 500ms
  }
}

void loop() {
  // initialize variables
  int codesTotal = 0;
  int codesMemory[30]{};
  int color;

  // restart the variable
  lost = true;

  // update the Bounce instance
  debouncer1.update();
  
  // start the game when the 1st button is pressed
  if (debouncer1.fell()){
    // play while user did not win
    while (lost == true){
      delay(100);       // wait 100ms before actually start the game
      playGame();       // play the game
      
      // if wrongCode is false, the user won, in that case the victory sounds will play among the leds
      if(wrongCode == false){
        lost = false;   // lost is equal to false, knowing the user won
        victoryShow();  // play the victory sounds among the leds
      }
    }
  }
}
