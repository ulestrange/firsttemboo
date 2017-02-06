#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  if (calls <= maxCalls) {
    Serial.println("Running InitializeOAuth - Run #" + String(calls++));
    
    TembooChoreo InitializeOAuthChoreo;

    // Invoke the Temboo client
    InitializeOAuthChoreo.begin();

    // Set Temboo account credentials
    InitializeOAuthChoreo.setAccountName(TEMBOO_ACCOUNT);
    InitializeOAuthChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    InitializeOAuthChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set profile to use for execution
    InitializeOAuthChoreo.setProfile("unasligo");
    
    // Identify the Choreo to run
    InitializeOAuthChoreo.setChoreo("/Library/Google/OAuth/InitializeOAuth");
    
    // Run the Choreo; when results are available, print them to serial
    InitializeOAuthChoreo.run();
    
    while(InitializeOAuthChoreo.available()) {
      char c = InitializeOAuthChoreo.read();
      Serial.print(c);
    }
    InitializeOAuthChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between InitializeOAuth calls
}