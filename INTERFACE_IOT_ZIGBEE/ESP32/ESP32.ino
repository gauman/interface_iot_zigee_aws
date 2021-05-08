
#include <AWS_IOT.h>
#include <WiFi.h>

AWS_IOT Home_auto;


//ENTER YOUR SSID, PASSWORD, ENDPONT, CLIENT ID AND TOPIC.

char WIFI_SSID[]="";
char WIFI_PASSWORD[]="";
char HOST_ADDRESS[]="";
char CLIENT_ID[]= "";
char TOPIC_NAME[]= "";



int status = WL_IDLE_STATUS; // STATUS OF WIFI
int  msgReceived = 0; // VARIABLE USED TO CHECK THE CONDITIONAL STATEMENT IN IF MSG IS RECEIVED 
char payload[512]; // VARIABLE USED TO STORE RECEIVED VALUE FROM THE SUBSCRIBED BROKER
char rcvdPayload[512];


// CALL BACK FUNCTION OF SUBSCRIBE
void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{

    
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}



void setup() {
    Serial.begin(9600); // BAUD RATE OF SERIAL COMM
    delay(2000);

    while (status != WL_CONNECTED)                       // CHECK THE STATUS OF WIFI CONNECTION
    {
        Serial.print("Attempting to connect to SSID ");
        Serial.println(WIFI_SSID);
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Connect to WPA/WPA2 network. 
        delay(5000);                                   // WAIT FOR 5 SECOND FOR THE CONNECTION    
        Serial.println("Connected to wifi");


       // CHECK THE AWS CONNECTION AND SUBSCRIBE


    if(Home_auto.connect(HOST_ADDRESS,CLIENT_ID)== 0)
    {
        Serial.println("Connected to AWS");
        delay(1000);

        if(0==Home_auto.subscribe(TOPIC_NAME,mySubCallBackHandler))
        {
            Serial.println("Subscribe Successfull");
        }
        else
        {
            Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
            while(1);
        }
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(2000);

}

}
void loop() {


   // CHECK THE RECEIVED VALUE

    if(msgReceived == 1)
    {
        msgReceived = 0;
        if((int)rcvdPayload[0] == 49){    //CHECK ASCII VALUE OF 1 IS 49 
          Serial.write(1); 
        }
        else if((int)rcvdPayload[0] == 50){ //CHECK ASCII VALUE OF 2 IS 50 
          Serial.write(2);
        }
        }

        
    
    vTaskDelay(1000 / portTICK_RATE_MS); 
   
}
