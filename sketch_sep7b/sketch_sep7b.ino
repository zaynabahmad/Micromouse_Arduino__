#include <SoftwareSerial.h>
SoftwareSerial mine(1,0);

void setup() {
    
    
    mine.begin(9600);
}



    void loop(){
       mine.println("haay");
       
    }

  

