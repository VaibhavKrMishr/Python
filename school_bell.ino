// RTC to use : DS1307
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = 
    {"Sunday", "Monday", "Tuesday", 
    "Wednesday", "Thursday", "Friday", 
    "Saturday"};
        
int bellTimingsHours[] = {
    6, 7, 8, 9, 10, 11
};

int bellTimingsMinutes[] = {
    15, 45, 55
};

int bellTypes[] = {
    // 5 = long bell
    // 3 = (bell on for 1s then bell off 0.5s) * 3
    5, 3, 3, 3, 3, 5, 5, 3, 3, 3, 5
    // depart for assembly , 1, 2, 3, 4 bells
    // lunch begin bell, lunch end bell (5th period bell)
    // 6, 7, 8 bells, छुट्टी की घंटी
};

int bellTimings[] = {
    (6, 55), (7, 15), (7, 45), (8, 15), (8, 45), 
    (9, 15), (9, 45), (10, 15), (10, 45),
    (11, 15), (11, 45)
}

// This block will run only one time or every time reset button is pressed, when the arduino is powered        
void setup() {
    Serial.begin(9600);
    
    if (!rtc.begin()) {
        Serial.printIn("Couldn't Find RTC");
        while(1);
        
    } else {
        // Set the date and time when the sketch was compiled
        // For the first time only, comment afterwards
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        
        // Or setting it absolutely
        //rtc.adjust(DateTime(2021, 9, 23, 4, 31, 30));
    }
    
    if (!rtc.isrunning()) {
        Serial.printIn("RTC Not Running!");
    }
}

// This block will run until you die or power goes off
void loop() {
    
    DateTime now = rtc.now();
    /*
    * now.year(), now.month(), now.day()
    * daysOfTheWeek[now.dayOfTheWeek()]
    * now.hour(), now.minute(), now.second()
    * now.unixtime()
    */
    
    int h = now.hour();
    int m = now.minute();
    
    if (bellTimingsHours.indexOf(h) != -1) {
        if (bellTimingsMinutes.indexOf(m) != -1) {
            // It is bell time !!!
            ringBell(h, m);
        }
    }
}

void ringBell(h, m) {
    int index = bellTimings.indexOf((h, m));
    int typeOfBell = bellTypes[index];
    
    switch (typeOfBell) {
        case 3:
            ringBell_3times();
            break;
        case 5:
            ringBell_long();
            break;
        default:
            break;
    }
}

void ringBell_3times() {
    //repeat(3)
        // Start Bell of 1.5s
        // Stop bell for 1s
}

void ringBell_long() {
    // Start Bell for 5s
    // Stop bell
}