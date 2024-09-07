void loop() 
{
// The main code that will run repeatedly
/ Capturing the current time
CurrentTime = millis );
/ Checking whether a specific sensor needs setup if (Serial.available()!= NULL)
{
/ Call the SetupSensors building block (function)
SetupSensorO);
}
/ Verify that it's the time for the new data collection
if (CurrentTime - LastCollectTime >= CollectInterval) 
{
/ Assian the current time to the LastCollectTime variable
LastCollectTime = CurrentTime;
// Call the DataCollect building block (function)
DataCollect);
/ Send the collected readings to the serial monitor
SendToSerial ();
/ Upload the collected measures to ThingSpeak SubmitToCloudO;
// Monitor the measured parameters and verify them with the predefined thresholds
MonitoringO;
}
// Verify that the LCD show interval has been vasted before printing new information on the LCD
if (CurrentTime - LastCollectTime >= LCDShowInterval) 
{
LastCollectTime = Currentlime;
sendToLCDO;
}
}