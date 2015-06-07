
#define TB_DIR_LEFT 3
#define TB_DIR_RIGHT 5
#define TB_DIR_UP 7
#define TB_DIR_DOWN 8

#define TB_CMD 11

#define minus_val -6
#define plus_val 6
#define con_val 4

int u=0,d=0,l=0,r=0;

struct 
{
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t wheel;	/* Not yet implemented */
 } mouseReport;

uint8_t nullReport[4] = { 0, 0, 0, 0 };

void setup();
void loop();


int led = 13;
//int bt1 = 9;
bool active=true;

/* TrackBall */
struct TBState
{
	/* current state */
	int up, down, left, right;
	
	/* cumulated state */
	int c_up, c_down, c_left, c_right;
} tbState;

void initTB()
{
	pinMode(TB_DIR_UP, INPUT);
	pinMode(TB_DIR_DOWN, INPUT);
	pinMode(TB_DIR_LEFT, INPUT);
	pinMode(TB_DIR_RIGHT, INPUT);
        pinMode(TB_CMD, INPUT);
	
	//pinMode(TB_LED_BLUE, OUTPUT);
	//pinMode(TB_LED_RED, OUTPUT);
	//pinMode(TB_LED_GREEN, OUTPUT);
	//pinMode(TB_LED_WHITE, OUTPUT);
	
	tbState.up = digitalRead(TB_DIR_UP);
	tbState.down = digitalRead(TB_DIR_DOWN);
	tbState.left = digitalRead(TB_DIR_LEFT);
	tbState.right = digitalRead(TB_DIR_RIGHT);
	
	//digitalWrite(TB_LED_WHITE, HIGH);
}

void pollTB(bool sendEvents=true)
{
	
}


void setup()
{        
  Serial.begin(9600);	  
  
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    
  initTB(); 
  
}


void loop() {
  /* the track ball */
    mouseReport.buttons = 0;
    mouseReport.x = 0;
    mouseReport.y = 0;
    mouseReport.wheel = 0;
  //  pollTB();
  struct TBState newState = tbState;
	const int threshold = 1;//3
	bool reset = false;
	
	newState.up = digitalRead(TB_DIR_UP);
	newState.down = digitalRead(TB_DIR_DOWN);
	newState.left = digitalRead(TB_DIR_LEFT);
	newState.right = digitalRead(TB_DIR_RIGHT);
 
	if (newState.left != tbState.left) 
         {
		 //Serial.print("up ");
              u=1;
                  mouseReport.y = minus_val;    
                         Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;              

         }
	if (newState.right != tbState.right) 
         {
		 //Serial.print("DOWN ");
                    d=1;
                        mouseReport.y = plus_val;
                        Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;
  
	}
if (newState.down != tbState.down) 
           {
		     //Serial.print("RIGHT ");
                      r=1;
                    mouseReport.x = plus_val;
                        Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;  
	  }
if (newState.up != tbState.up) 
            {
               //Serial.print("LEFT ");
                      l==1;
                   mouseReport.x = minus_val;
                        Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;  
          	   }
          
          
	if (reset)
	{
		newState.c_up = 0;
		newState.c_down = 0;
		newState.c_left = 0;
		newState.c_right = 0;
               // Serial.print(".\n");
	}

if(u==1 && r==1)
{
    mouseReport.y = minus_val;
     mouseReport.x = plus_val;
                        Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;  
                     u=0;r=0;   
  
}

if(u==1 && l==1)
{
    mouseReport.y = minus_val;
      mouseReport.x = minus_val;
                        Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;  
                     u=0;l=0;   
  
}
if(d==1 && l==1)
{
   mouseReport.y = plus_val;
      mouseReport.x = minus_val;
                        Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;  
                     d=0;l=0;   
  
}	

if(d==1 && r==1)
{
    mouseReport.y = plus_val;
     mouseReport.x = plus_val;
                        Serial.write((uint8_t *)&mouseReport, con_val);
	                Serial.write((uint8_t *)&nullReport, con_val);
                        reset = true;  
                     d=0;r=0;   
  
}	
	tbState = newState;
  if(digitalRead(TB_CMD)==0)
    {
        // Serial.print("BUTTON\n");
        mouseReport.buttons = 1;
   	Serial.write((uint8_t *)&mouseReport, con_val);
	Serial.write((uint8_t *)&nullReport, con_val);
        if(active) active=false;
        else active=true;
   // delay(300);
    }
    
  
   
}
