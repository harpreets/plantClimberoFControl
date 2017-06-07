
//PUMP should turn on separately before the lights
//Local time should be set on the system
//currentLight should be set i.e at least one light should have been set after starting the application

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    int baud = 9600;
    serial.setup(0, baud); //open the first device
    //serial.setup("COM4", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    
    nTimesRead = 0;
    nBytesRead = 0;
    readTime = 0;
    memset(bytesReadString, 0, 4);
 
    isTimeStarted = true;
    
    currentLight = 0; //zero for no lights
    currMin = prevMin = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    //look at time calc
    if(isTimeStarted){
        elapsedTime  =  (ofGetElapsedTimeMillis() - startTime); //convert to secs
        elapsedsecs  =  ((elapsedTime /  1000)                 % 60);
        elapsedMins  =  ((elapsedTime / (1000 * 60))           % 60);
        elapsedHours =  ((elapsedTime / (1000 * 60 * 60))      % 24); //hours in this case set to zero after 24
        elapsedDays  =  ((elapsedTime / (1000 * 60 * 60 * 24))     ); //days keep on counting in this case
        
        currMin = elapsedMins;
        
        //check every min for local time change
        if(currMin != prevMin){
            //check hour and minute of day
            currLocalHour = ofGetHours();
            currLocalMin = ofGetMinutes();
            
            
            if( (currLocalHour == 7) && (currLocalMin == 0) ){
                //turn on at 6am
                if(currentLight != 0){
                    serial.writeByte(currentLight);
                }
            }else if( (currLocalHour == 19) && (currLocalMin == 0) ){
                //turn off the light at this hour
                if(currentLight != 0){
                    //turn off the current light
                    serial.writeByte(currentLight);
                    turnOffAllLights(); //send '5'
                }
            }
            
            prevMin = currMin;
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key==' '){
        isTimeStarted = !isTimeStarted;
        startTime = ofGetElapsedTimeMillis();
    }
    
    if(key=='w'){
        serial.writeByte('w');
    }else if(key=='s'){
        serial.writeByte('s');
    }else if(key=='q'){
        serial.writeByte('q');
    }else if(key=='a'){
        serial.writeByte('a');
    }else if(key=='x'){
        serial.writeByte('x');
    }
    
    
    if(key=='1'){
        currentLight = '1';
        serial.writeByte(currentLight);
    }else if(key == '2'){
        currentLight = '2';
        serial.writeByte(currentLight);
    }else if(key == '3'){
        currentLight = '3';
        serial.writeByte(currentLight);
    }else if(key == '4'){
        currentLight = '4';
        serial.writeByte(currentLight);
    }else if(key == '5'){
        currentLight = '5';
        serial.writeByte(currentLight);
    }
}

void ofApp::turnOffAllLights(){
    serial.writeByte('5');
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
