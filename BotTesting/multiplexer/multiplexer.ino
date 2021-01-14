#include<Wire.h>
#include<SoftwareSerial.h> 


const int BUFFER_SIZE = 14; // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
const int DATA_SIZE = 10; // 10byte data (2byte version + 8byte tag)
const int DATA_VERSION_SIZE = 2; // 2byte version (actual meaning of these two bytes may vary)
const int DATA_TAG_SIZE = 8; // 8byte tag
const int CHECKSUM_SIZE = 2; // 2byte checksum

uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame 
int buffer_index = 0;


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
 Wire.begin();

// multiplex(1);
 
}

void loop() {
  // put your main code here, to run repeatedly:

multiplex(1);
if (call_extract_tag == true) {
      if (buffer_index == BUFFER_SIZE) {
        unsigned tag = extract_tag();
        Serial.println(tag);
      }
}

}

//Multiplexer transmition

void multiplex(uint8_t bus){

  Wire.beginTransmission(0x70);
  Wire.write(1 << bus);
  Wire.endTransmission();
  
}

void rfidsetup(int num1,int num2){

  SoftwareSerial ssrfid(num1,num2);
}


unsigned extract_tag() {
    uint8_t msg_head = buffer[0];
    uint8_t *msg_data = buffer + 1; // 10 byte => data contains 2byte version + 8byte tag
    uint8_t *msg_data_version = msg_data;
    uint8_t *msg_data_tag = msg_data + 2;
    uint8_t *msg_checksum = buffer + 11; // 2 byte
    uint8_t msg_tail = buffer[13];

    

    long tag = hexstr_to_value(msg_data_tag, DATA_TAG_SIZE);
    Serial.print("Extracted Tag: ");
    Serial.println(tag);

    long checksum = 0;
    for (int i = 0; i < DATA_SIZE; i+= CHECKSUM_SIZE) {
      long val = hexstr_to_value(msg_data + i, CHECKSUM_SIZE);
      checksum ^= val;
    }
    Serial.print("Extracted Checksum (HEX): ");
    Serial.print(checksum, HEX);
    if (checksum == hexstr_to_value(msg_checksum, CHECKSUM_SIZE)) { // compare calculated checksum to retrieved checksum
      Serial.print(" (OK)"); // calculated checksum corresponds to transmitted checksum!
    } else {
      Serial.print(" (NOT OK)"); // checksums do not match
    }

    Serial.println("");
    Serial.println("--------");

    return tag;
}


long hexstr_to_value(char *str, unsigned int length) { // converts a hexadecimal value (encoded as ASCII string) to a numeric value
   
    char* copy = malloc((sizeof(char) * length) + 1); 
    memcpy(copy, str, sizeof(char) * length);
    copy[length] = '\0'; 
    // the variable "copy" is a copy of the parameter "str". "copy" has an additional '\0' element to make sure that "str" is null-terminated.
    long value = strtol(copy, NULL, 16);  // strtol converts a null-terminated string to a long value
    free(copy); // clean up 
    return value;
    
}
