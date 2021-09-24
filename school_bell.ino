// RTC to use : DS1307
#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;
const int buzzer = 9; // Buzzer Pin
const int pushButton = 7; // The push button to manually ring the bell
int pushButtonVal = 0;

//char daysOfTheWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", 
//						"Thursday", "Friday", "Saturday"};
        
int bellTimingsHours[6] = {6, 7, 8, 9, 10, 11};

int bellTimingsMinutes[3] = {15, 45, 55};

int bellTimingsLen = 11;

int bellTypes[bellTimingsLen] = {
    // 0 = long bell
    0, 1, 2, 3, 4, 0, 0, 6, 7, 8, 0
    // depart for assembly , 1, 2, 3, 4 bells
    // lunch begin bell, lunch end bell (and the 5th period bell)
    // 6, 7, 8 bells, then finally, छुट्टी की घंटी !!!
};

int bellLongDurations[bellTimingsLen] = {
    3000, 1000, 1000, 1000, 1000, 4000, 4000, 1000, 1000, 1000, 5000
};

/*typedef struct hourMinute {
	int hour;
	int minute;
} hourMinute_t;*/

/*hourMinute_t bellTimings[] = {
    {6, 55}, {7, 15}, {7, 45}, {8, 15}, {8, 45}, 
    {9, 15}, {9, 45}, {10, 15}, {10, 45},
    {11, 15}, {11, 45}
};*/

int bellTimings[bellTimingsLen][2] = {
    {6, 55}, {7, 15}, {7, 45}, {8, 15}, {8, 45}, 
    {9, 15}, {9, 45}, {10, 15}, {10, 45},
    {11, 15}, {11, 45}
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

    pinMode(buzzer, OUTPUT);
    pinMode(pushButton, INPUT);
}

// This block will run until you die or the power goes off...
void loop() {

	val = digitalRead(pushButton);
	if (val == HIGH) {
		tone(buzzer, 1000);
	} else {
		noTone(buzzer);
	}
    
    DateTime now = rtc.now();
    /*
    * 'now's methods:-
    * now.year(), now.month(), now.day()
    * daysOfTheWeek[now.dayOfTheWeek()]
    * now.hour(), now.minute(), now.second()
    * now.unixtime()
    */

    if (now.dayOfTheWeek() == 0) {
    	return;
    }
    
    int h = now.hour();
    int m = now.minute();
    
    if (indexOfInt(bellTimingsHours, h) != -1) {
        if (indexOfInt(bellTimingsMinutes, m) != -1) {
            // It is bell time !!!
            ringBell(h, m);
        }
    }

    delay(5000); // Wait for 5 seconds before checking again
}

int indexOfInt(array ar, int elem) {
	int index = -1;
	int len = sizeof(ar) / sizeof(ar[0]);
	for (int i = 0; i < len; ++i)
	{
		if (elem == ar[i]) {
			index = i;
			break;
		}
	}

	return index;
}

int indexOfArray(array ar, array elem) {
	int index = -1;
	int len = sizeof(ar) / sizeof(ar[0]);
	for (int i = 0; i < len; ++i)
	{
		if (elem == ar[i]) {
			index = i;
			break;
		}
	}

	return index;
}

void ringBell(int h, int m) {
    int index = indexOfArray(bellTimings, {h, m});
    int typeOfBell = bellTypes[index];
    int duration = bellLongDurations[index];

    if (typeOfBell == 0) {
        ringBell_long(duration);
    } else {
        ringBell_ntimes(typeOfBell, duration);
    }
    
    /*switch (typeOfBell) {
        case 3:
            ringBell_ntimes();
            break;
        case 5:
            ringBell_long();
            break;
        default:
            break;
    }*/
}

void ringBell_ntimes(int n = 3, int duration = 1000, int pause = 500) {
    //repeat(n)
        // Start Bell for duration
        // Stop bell for pause

	for (int i = 0; i < n; ++i)
	{
		tone(buzzer, 1000); // Send a 1000 Hz (1KHz) signal to the buzzer
		delay(duration); // Wait duration sec
		noTone(buzzer); // Send no tone to buzzer
		delay(pause);	// Wait pause sec
	}
}

void ringBell_long(int duration = 5000) {
    // Start Bell for duration
    // Stop bell

    tone(buzzer, 1000);
    delay(duration);
    noTone(buzzer);
}
