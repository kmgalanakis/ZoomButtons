//
// Zoom Buttons
//

#include "HID-Project.h"

#define VOLUME
#define ZOOMBTNS

#define led 13

#ifdef VOLUME
  #define ROTARY_A 6
  #define ROTARY_B 5
  #define ROTARY_C 7

  boolean A, a, B, b, C, c;
#endif

#ifdef ZOOMBTNS
  #define BTN1 8
  #define BTN2 9
  #define BTN3 10
  #define BTN4 A0
  #define BTN5 A1
  #define BTN6 A2
  #define NUMBUTTONS 6

  int buttons[ NUMBUTTONS ] = { BTN1, BTN2, BTN3, BTN4, BTN5, BTN6 };
  unsigned long btntime[ NUMBUTTONS ];
  boolean btnpress[ NUMBUTTONS ];
#endif

char line[ 80 ];
unsigned long t;
int n;

void setup() {
//  Serial.begin( 38400 );
//  Serial.write( "Starting...\n" );
//  Serial.end();
  
  pinMode( led, OUTPUT );
  digitalWrite( led, LOW );

  #ifdef VOLUME
    pinMode( ROTARY_A, INPUT_PULLUP );
    pinMode( ROTARY_B, INPUT_PULLUP );
    pinMode( ROTARY_C, INPUT_PULLUP );

    a = b = c = false;
    Consumer.begin();
  #endif

  for ( int i=0; i < 3; i++ ) {
    digitalWrite( led, HIGH ); delay( 20 );
    digitalWrite( led, LOW ); delay( 200 );
    digitalWrite( led, HIGH ); delay( 20 );
    digitalWrite( led, LOW ); delay( 200 );
    digitalWrite( led, HIGH ); delay( 20 );
    digitalWrite( led, LOW ); delay( 500 );
  }

  #ifdef ZOOMBTNS
    for ( int i = 0; i < NUMBUTTONS; i++ ) {
      pinMode( buttons[ i ], INPUT_PULLUP );
      btntime[ i ] = 0;
      btnpress[ i ] = false;
    }

    BootKeyboard.begin();
  #endif
}

void loop() {
  #ifdef VOLUME
    A = digitalRead( ROTARY_A ) == LOW;
    B = digitalRead( ROTARY_B ) == LOW;
    C = digitalRead( ROTARY_C ) == LOW;
    if ( A && ! a ) {
      if ( B ) {
        n++; if ( n > 100 ) n = 100;
        Consumer.write( MEDIA_VOL_UP );
      }
      else {
        n--; if ( n < 0 ) n = 0;
        Consumer.write( MEDIA_VOL_DOWN );
      }
    }

    a = A;
    
    if ( C && ! c ) {
      Consumer.write( MEDIA_VOL_MUTE );
    }
    
    c = C;
  #endif

  #ifdef ZOOMBTNS
    for ( int i = 0; i < NUMBUTTONS; i++ ) {
       if ( ! digitalRead( buttons[ i ] ) ) {
          if ( ! btnpress[ i ] ) {
            btntime[ i ] = millis();
            btnpress[ i ] = true;
          }   
       } else {
        // Button not pressed
        if ( btntime[ i ] != 0 ) {
          if ( abs(  millis() - btntime[ i ] ) > 750 ) {
//            sprintf( line, "%s\n", "long press" );
//            Serial.write( line );
            button_pressed( i, "long" );
          } else if ( abs(  millis() - btntime[ i ] > 20 ) ) { 
//            sprintf( line, "%s\n", "short press" );
//            Serial.write( line );
            button_pressed( i, "short" );
          }

          // Looks like it's just been released
          reset_after_button_release( i );
        }
      }
    }
  #endif
}

void button_pressed( int i, char* press_type ) {
  switch( i ) {
    case 0:
      if ( strcmp( press_type, "short" ) == 0 ) {
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.write(KEY_F2);
        BootKeyboard.release(KEY_LEFT_ALT);
      } else if ( strcmp( press_type, "long" ) == 0 ) {
        
      }
      break;
    case 1:
      if ( strcmp( press_type, "short" ) == 0 ) {
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.write(KEY_F1);
        BootKeyboard.release(KEY_LEFT_ALT);
      } else if ( strcmp( press_type, "long" ) == 0 ) {
        
      }
      break;
    case 2:
      if ( strcmp( press_type, "short" ) == 0 ) {
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.write(KEY_V);
        BootKeyboard.release(KEY_LEFT_ALT);
      } else if ( strcmp( press_type, "long" ) == 0 ) {
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.write(KEY_H);
        BootKeyboard.release(KEY_LEFT_ALT);
      }
      break;
    case 3:
      if ( strcmp( press_type, "short" ) == 0 ) {
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.write(KEY_A);
        BootKeyboard.release(KEY_LEFT_ALT);
      } else if ( strcmp( press_type, "long" ) == 0 ) {
        BootKeyboard.press( KEY_LEFT_ALT );
        BootKeyboard.write( KEY_Q );
        BootKeyboard.release( KEY_LEFT_ALT );
      }
      break;
    case 4:
      if ( strcmp( press_type, "short" ) == 0 ) {
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.write(KEY_F);
        BootKeyboard.release(KEY_LEFT_ALT);
      } else if ( strcmp( press_type, "long" ) == 0 ) {
        
      }
      break;
    case 5:
      if ( strcmp( press_type, "short" ) == 0 ) {
        BootKeyboard.press(KEY_LEFT_ALT);
        BootKeyboard.write(KEY_S);
        BootKeyboard.release(KEY_LEFT_ALT);
      } else if ( strcmp( press_type, "long" ) == 0 ) {
        
      }
      break;
  }
}

void reset_after_button_release( int i ) {
  digitalWrite( led, LOW );
  btntime[ i ] = 0;
  btnpress[ i ] = false;
}
