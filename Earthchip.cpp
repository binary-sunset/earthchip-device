
#include "Earthchip.h"
#include "Arduino.h"
#include <FS.h>

Earthchip::Earthchip() {
    this->_state = MQTT_DISCONNECTED;
    this->_client = NULL;
    this->stream = NULL;
    setCallback(NULL);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

Earthchip::Earthchip(Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

Earthchip::Earthchip(IPAddress addr, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(addr, port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
Earthchip::Earthchip(IPAddress addr, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(addr,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

Earthchip::Earthchip(uint8_t *ip, uint16_t port, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip, port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
Earthchip::Earthchip(uint8_t *ip, uint16_t port, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
Earthchip::Earthchip(uint8_t *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip, port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
Earthchip::Earthchip(uint8_t *ip, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(ip,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
/// CANDIDATE CONSTRUCTOR
Earthchip::Earthchip(const char* domain, uint16_t port, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
    this->node_id = retrieve();
    connect(node_id.c_str());
}

Earthchip::Earthchip(const char* domain, uint16_t port, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
Earthchip::Earthchip(const char* domain, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setCallback(callback);
    setClient(client);
    this->stream = NULL;
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}
Earthchip::Earthchip(const char* domain, uint16_t port, MQTT_CALLBACK_SIGNATURE, Client& client, Stream& stream) {
    this->_state = MQTT_DISCONNECTED;
    setServer(domain,port);
    setCallback(callback);
    setClient(client);
    setStream(stream);
    this->bufferSize = 0;
    setBufferSize(MQTT_MAX_PACKET_SIZE);
    setKeepAlive(MQTT_KEEPALIVE);
    setSocketTimeout(MQTT_SOCKET_TIMEOUT);
}

Earthchip::~Earthchip() {
  free(this->buffer);
}

boolean Earthchip::connect(const char *id) {
    return connect(id,NULL,NULL,0,0,0,0,1);
}

boolean Earthchip::connect(const char *id, const char *user, const char *pass) {
    return connect(id,user,pass,0,0,0,0,1);
}

boolean Earthchip::connect(const char *id, const char* willTopic, uint8_t willQos, boolean willRetain, const char* willMessage) {
    return connect(id,NULL,NULL,willTopic,willQos,willRetain,willMessage,1);
}

boolean Earthchip::connect(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, boolean willRetain, const char* willMessage) {
    return connect(id,user,pass,willTopic,willQos,willRetain,willMessage,1);
}

boolean Earthchip::connect(const char *id, const char *user, const char *pass, const char* willTopic, uint8_t willQos, boolean willRetain, const char* willMessage, boolean cleanSession) {
    if (!connected()) {
        int result = 0;


        if(_client->connected()) {
            result = 1;
        } else {
            if (domain != NULL) {
                result = _client->connect(this->domain, this->port);
            } else {
                result = _client->connect(this->ip, this->port);
            }
        }

        if (result == 1) {
            nextMsgId = 1;
            // Leave room in the buffer for header and variable length field
            uint16_t length = MQTT_MAX_HEADER_SIZE;
            unsigned int j;

#if MQTT_VERSION == MQTT_VERSION_3_1
            uint8_t d[9] = {0x00,0x06,'M','Q','I','s','d','p', MQTT_VERSION};
#define MQTT_HEADER_VERSION_LENGTH 9
#elif MQTT_VERSION == MQTT_VERSION_3_1_1
            uint8_t d[7] = {0x00,0x04,'M','Q','T','T',MQTT_VERSION};
#define MQTT_HEADER_VERSION_LENGTH 7
#endif
            for (j = 0;j<MQTT_HEADER_VERSION_LENGTH;j++) {
                this->buffer[length++] = d[j];
            }

            uint8_t v;
            if (willTopic) {
                v = 0x04|(willQos<<3)|(willRetain<<5);
            } else {
                v = 0x00;
            }
            if (cleanSession) {
                v = v|0x02;
            }

            if(user != NULL) {
                v = v|0x80;

                if(pass != NULL) {
                    v = v|(0x80>>1);
                }
            }
            this->buffer[length++] = v;

            this->buffer[length++] = ((this->keepAlive) >> 8);
            this->buffer[length++] = ((this->keepAlive) & 0xFF);

            CHECK_STRING_LENGTH(length,id)
            length = writeString(id,this->buffer,length);
            if (willTopic) {
                CHECK_STRING_LENGTH(length,willTopic)
                length = writeString(willTopic,this->buffer,length);
                CHECK_STRING_LENGTH(length,willMessage)
                length = writeString(willMessage,this->buffer,length);
            }

            if(user != NULL) {
                CHECK_STRING_LENGTH(length,user)
                length = writeString(user,this->buffer,length);
                if(pass != NULL) {
                    CHECK_STRING_LENGTH(length,pass)
                    length = writeString(pass,this->buffer,length);
                }
            }

            write(MQTTCONNECT,this->buffer,length-MQTT_MAX_HEADER_SIZE);

            lastInActivity = lastOutActivity = millis();

            while (!_client->available()) {
                unsigned long t = millis();
                if (t-lastInActivity >= ((int32_t) this->socketTimeout*1000UL)) {
                    _state = MQTT_CONNECTION_TIMEOUT;
                    _client->stop();
                    return false;
                }
            }
            uint8_t llen;
            uint32_t len = readPacket(&llen);

            if (len == 4) {
                if (buffer[3] == 0) {
                    lastInActivity = millis();
                    pingOutstanding = false;
                    _state = MQTT_CONNECTED;
                    return true;
                } else {
                    _state = buffer[3];
                }
            }
            _client->stop();
        } else {
            _state = MQTT_CONNECT_FAILED;
        }
        return false;
    }
    return true;
}

// reads a byte into result
boolean Earthchip::readByte(uint8_t * result) {
   uint32_t previousMillis = millis();
   while(!_client->available()) {
     yield();
     uint32_t currentMillis = millis();
     if(currentMillis - previousMillis >= ((int32_t) this->socketTimeout * 1000)){
       return false;
     }
   }
   *result = _client->read();
   return true;
}

// reads a byte into result[*index] and increments index
boolean Earthchip::readByte(uint8_t * result, uint16_t * index){
  uint16_t current_index = *index;
  uint8_t * write_address = &(result[current_index]);
  if(readByte(write_address)){
    *index = current_index + 1;
    return true;
  }
  return false;
}

uint32_t Earthchip::readPacket(uint8_t* lengthLength) {
    uint16_t len = 0;
    if(!readByte(this->buffer, &len)) return 0;
    bool isPublish = (this->buffer[0]&0xF0) == MQTTPUBLISH;
    uint32_t multiplier = 1;
    uint32_t length = 0;
    uint8_t digit = 0;
    uint16_t skip = 0;
    uint32_t start = 0;

    do {
        if (len == 5) {
            // Invalid remaining length encoding - kill the connection
            _state = MQTT_DISCONNECTED;
            _client->stop();
            return 0;
        }
        if(!readByte(&digit)) return 0;
        this->buffer[len++] = digit;
        length += (digit & 127) * multiplier;
        multiplier <<=7; //multiplier *= 128
    } while ((digit & 128) != 0);
    *lengthLength = len-1;

    if (isPublish) {
        // Read in topic length to calculate bytes to skip over for Stream writing
        if(!readByte(this->buffer, &len)) return 0;
        if(!readByte(this->buffer, &len)) return 0;
        skip = (this->buffer[*lengthLength+1]<<8)+this->buffer[*lengthLength+2];
        start = 2;
        if (this->buffer[0]&MQTTQOS1) {
            // skip message id
            skip += 2;
        }
    }
    uint32_t idx = len;

    for (uint32_t i = start;i<length;i++) {
        if(!readByte(&digit)) return 0;
        if (this->stream) {
            if (isPublish && idx-*lengthLength-2>skip) {
                this->stream->write(digit);
            }
        }

        if (len < this->bufferSize) {
            this->buffer[len] = digit;
            len++;
        }
        idx++;
    }

    if (!this->stream && idx > this->bufferSize) {
        len = 0; // This will cause the packet to be ignored.
    }
    return len;
}

boolean Earthchip::loop() {
    if (connected()) {
        unsigned long t = millis();
        if ((t - lastInActivity > this->keepAlive*1000UL) || (t - lastOutActivity > this->keepAlive*1000UL)) {
            if (pingOutstanding) {
                this->_state = MQTT_CONNECTION_TIMEOUT;
                _client->stop();
                return false;
            } else {
                this->buffer[0] = MQTTPINGREQ;
                this->buffer[1] = 0;
                _client->write(this->buffer,2);
                lastOutActivity = t;
                lastInActivity = t;
                pingOutstanding = true;
            }
        }
        if (_client->available()) {
            uint8_t llen;
            uint16_t len = readPacket(&llen);
            uint16_t msgId = 0;
            uint8_t *payload;
            if (len > 0) {
                lastInActivity = t;
                uint8_t type = this->buffer[0]&0xF0;
                if (type == MQTTPUBLISH) {
                    if (callback) {
                        uint16_t tl = (this->buffer[llen+1]<<8)+this->buffer[llen+2]; /* topic length in bytes */
                        memmove(this->buffer+llen+2,this->buffer+llen+3,tl); /* move topic inside buffer 1 byte to front */
                        this->buffer[llen+2+tl] = 0; /* end the topic as a 'C' string with \x00 */
                        char *topic = (char*) this->buffer+llen+2;
                        // msgId only present for QOS>0
                        if ((this->buffer[0]&0x06) == MQTTQOS1) {
                            msgId = (this->buffer[llen+3+tl]<<8)+this->buffer[llen+3+tl+1];
                            payload = this->buffer+llen+3+tl+2;
                            callback(topic,payload,len-llen-3-tl-2);

                            this->buffer[0] = MQTTPUBACK;
                            this->buffer[1] = 2;
                            this->buffer[2] = (msgId >> 8);
                            this->buffer[3] = (msgId & 0xFF);
                            _client->write(this->buffer,4);
                            lastOutActivity = t;

                        } else {
                            payload = this->buffer+llen+3+tl;
                            callback(topic,payload,len-llen-3-tl);
                        }
                    }
                } else if (type == MQTTPINGREQ) {
                    this->buffer[0] = MQTTPINGRESP;
                    this->buffer[1] = 0;
                    _client->write(this->buffer,2);
                } else if (type == MQTTPINGRESP) {
                    pingOutstanding = false;
                }
            } else if (!connected()) {
                // readPacket has closed the connection
                return false;
            }
        }
        return true;
    }
    return false;
}

boolean Earthchip::publish(const char* topic, const char* payload) {
    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0,false);
}

boolean Earthchip::publish(const char* topic, const char* payload, boolean retained) {
    return publish(topic,(const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0,retained);
}

boolean Earthchip::publish(const char* topic, const uint8_t* payload, unsigned int plength) {
    return publish(topic, payload, plength, false);
}

boolean Earthchip::publish(const char* topic, const uint8_t* payload, unsigned int plength, boolean retained) {
    if (connected()) {
        if (this->bufferSize < MQTT_MAX_HEADER_SIZE + 2+strnlen(topic, this->bufferSize) + plength) {
            // Too long
            return false;
        }
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        length = writeString(topic,this->buffer,length);

        // Add payload
        uint16_t i;
        for (i=0;i<plength;i++) {
            this->buffer[length++] = payload[i];
        }

        // Write the header
        uint8_t header = MQTTPUBLISH;
        if (retained) {
            header |= 1;
        }
        return write(header,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

boolean Earthchip::publish_P(const char* topic, const char* payload, boolean retained) {
    return publish_P(topic, (const uint8_t*)payload, payload ? strnlen(payload, this->bufferSize) : 0, retained);
}

boolean Earthchip::publish_P(const char* topic, const uint8_t* payload, unsigned int plength, boolean retained) {
    uint8_t llen = 0;
    uint8_t digit;
    unsigned int rc = 0;
    uint16_t tlen;
    unsigned int pos = 0;
    unsigned int i;
    uint8_t header;
    unsigned int len;
    int expectedLength;

    if (!connected()) {
        return false;
    }

    tlen = strnlen(topic, this->bufferSize);

    header = MQTTPUBLISH;
    if (retained) {
        header |= 1;
    }
    this->buffer[pos++] = header;
    len = plength + 2 + tlen;
    do {
        digit = len  & 127; //digit = len %128
        len >>= 7; //len = len / 128
        if (len > 0) {
            digit |= 0x80;
        }
        this->buffer[pos++] = digit;
        llen++;
    } while(len>0);

    pos = writeString(topic,this->buffer,pos);

    rc += _client->write(this->buffer,pos);

    for (i=0;i<plength;i++) {
        rc += _client->write((char)pgm_read_byte_near(payload + i));
    }

    lastOutActivity = millis();

    expectedLength = 1 + llen + 2 + tlen + plength;

    return (rc == expectedLength);
}

boolean Earthchip::beginPublish(const char* topic, unsigned int plength, boolean retained) {
    if (connected()) {
        // Send the header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        length = writeString(topic,this->buffer,length);
        uint8_t header = MQTTPUBLISH;
        if (retained) {
            header |= 1;
        }
        size_t hlen = buildHeader(header, this->buffer, plength+length-MQTT_MAX_HEADER_SIZE);
        uint16_t rc = _client->write(this->buffer+(MQTT_MAX_HEADER_SIZE-hlen),length-(MQTT_MAX_HEADER_SIZE-hlen));
        lastOutActivity = millis();
        return (rc == (length-(MQTT_MAX_HEADER_SIZE-hlen)));
    }
    return false;
}

int Earthchip::endPublish() {
 return 1;
}

size_t Earthchip::write(uint8_t data) {
    lastOutActivity = millis();
    return _client->write(data);
}

size_t Earthchip::write(const uint8_t *buffer, size_t size) {
    lastOutActivity = millis();
    return _client->write(buffer,size);
}

size_t Earthchip::buildHeader(uint8_t header, uint8_t* buf, uint16_t length) {
    uint8_t lenBuf[4];
    uint8_t llen = 0;
    uint8_t digit;
    uint8_t pos = 0;
    uint16_t len = length;
    do {

        digit = len  & 127; //digit = len %128
        len >>= 7; //len = len / 128
        if (len > 0) {
            digit |= 0x80;
        }
        lenBuf[pos++] = digit;
        llen++;
    } while(len>0);

    buf[4-llen] = header;
    for (int i=0;i<llen;i++) {
        buf[MQTT_MAX_HEADER_SIZE-llen+i] = lenBuf[i];
    }
    return llen+1; // Full header size is variable length bit plus the 1-byte fixed header
}

boolean Earthchip::write(uint8_t header, uint8_t* buf, uint16_t length) {
    uint16_t rc;
    uint8_t hlen = buildHeader(header, buf, length);

#ifdef MQTT_MAX_TRANSFER_SIZE
    uint8_t* writeBuf = buf+(MQTT_MAX_HEADER_SIZE-hlen);
    uint16_t bytesRemaining = length+hlen;  //Match the length type
    uint8_t bytesToWrite;
    boolean result = true;
    while((bytesRemaining > 0) && result) {
        bytesToWrite = (bytesRemaining > MQTT_MAX_TRANSFER_SIZE)?MQTT_MAX_TRANSFER_SIZE:bytesRemaining;
        rc = _client->write(writeBuf,bytesToWrite);
        result = (rc == bytesToWrite);
        bytesRemaining -= rc;
        writeBuf += rc;
    }
    return result;
#else
    rc = _client->write(buf+(MQTT_MAX_HEADER_SIZE-hlen),length+hlen);
    lastOutActivity = millis();
    return (rc == hlen+length);
#endif
}

boolean Earthchip::subscribe(const char* topic) {
    return subscribe(topic, 0);
}

boolean Earthchip::subscribe(const char* topic, uint8_t qos) {
    size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == 0) {
        return false;
    }
    if (qos > 1) {
        return false;
    }
    if (this->bufferSize < 9 + topicLength) {
        // Too long
        return false;
    }
    if (connected()) {
        // Leave room in the buffer for header and variable length field
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0) {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString((char*)topic, this->buffer,length);
        this->buffer[length++] = qos;
        return write(MQTTSUBSCRIBE|MQTTQOS1,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

boolean Earthchip::unsubscribe(const char* topic) {
	size_t topicLength = strnlen(topic, this->bufferSize);
    if (topic == 0) {
        return false;
    }
    if (this->bufferSize < 9 + topicLength) {
        // Too long
        return false;
    }
    if (connected()) {
        uint16_t length = MQTT_MAX_HEADER_SIZE;
        nextMsgId++;
        if (nextMsgId == 0) {
            nextMsgId = 1;
        }
        this->buffer[length++] = (nextMsgId >> 8);
        this->buffer[length++] = (nextMsgId & 0xFF);
        length = writeString(topic, this->buffer,length);
        return write(MQTTUNSUBSCRIBE|MQTTQOS1,this->buffer,length-MQTT_MAX_HEADER_SIZE);
    }
    return false;
}

void Earthchip::disconnect() {
    this->buffer[0] = MQTTDISCONNECT;
    this->buffer[1] = 0;
    _client->write(this->buffer,2);
    _state = MQTT_DISCONNECTED;
    _client->flush();
    _client->stop();
    lastInActivity = lastOutActivity = millis();
}

uint16_t Earthchip::writeString(const char* string, uint8_t* buf, uint16_t pos) {
    const char* idp = string;
    uint16_t i = 0;
    pos += 2;
    while (*idp) {
        buf[pos++] = *idp++;
        i++;
    }
    buf[pos-i-2] = (i >> 8);
    buf[pos-i-1] = (i & 0xFF);
    return pos;
}


boolean Earthchip::connected() {
    boolean rc;
    if (_client == NULL ) {
        rc = false;
    } else {
        rc = (int)_client->connected();
        if (!rc) {
            if (this->_state == MQTT_CONNECTED) {
                this->_state = MQTT_CONNECTION_LOST;
                _client->flush();
                _client->stop();
            }
        } else {
            return this->_state == MQTT_CONNECTED;
        }
    }
    return rc;
}

Earthchip& Earthchip::setServer(uint8_t * ip, uint16_t port) {
    IPAddress addr(ip[0],ip[1],ip[2],ip[3]);
    return setServer(addr,port);
}

Earthchip& Earthchip::setServer(IPAddress ip, uint16_t port) {
    this->ip = ip;
    this->port = port;
    this->domain = NULL;
    return *this;
}

Earthchip& Earthchip::setServer(const char * domain, uint16_t port) {
    this->domain = domain;
    this->port = port;
    return *this;
}

Earthchip& Earthchip::setCallback(MQTT_CALLBACK_SIGNATURE) {
    this->callback = callback;
    return *this;
}

Earthchip& Earthchip::setClient(Client& client){
    this->_client = &client;
    return *this;
}

Earthchip& Earthchip::setStream(Stream& stream){
    this->stream = &stream;
    return *this;
}

int Earthchip::state() {
    return this->_state;
}

boolean Earthchip::setBufferSize(uint16_t size) {
    if (size == 0) {
        // Cannot set it back to 0
        return false;
    }
    if (this->bufferSize == 0) {
        this->buffer = (uint8_t*)malloc(size);
    } else {
        uint8_t* newBuffer = (uint8_t*)realloc(this->buffer, size);
        if (newBuffer != NULL) {
            this->buffer = newBuffer;
        } else {
            return false;
        }
    }
    this->bufferSize = size;
    return (this->buffer != NULL);
}

uint16_t Earthchip::getBufferSize() {
    return this->bufferSize;
}
Earthchip& Earthchip::setKeepAlive(uint16_t keepAlive) {
    this->keepAlive = keepAlive;
    return *this;
}
Earthchip& Earthchip::setSocketTimeout(uint16_t timeout) {
    this->socketTimeout = timeout;
    return *this;
}

//OFF THE SHELF PUSH METHODS
boolean Earthchip::pushTemp(double temp) {
    String strTopic = node_id + TEMPERATURE_TOPIC; 
    return publish(strTopic.c_str(), String(temp).c_str());
}

boolean Earthchip::pushTemp(const char* temp) {
    String strTopic = node_id + TEMPERATURE_TOPIC; 
    return publish(strTopic.c_str(), temp);
}

String Earthchip::retrieve () {
    if (mountFS()) {
        if(readFS()== "") {
            return writeFS();
        } return readFS();
    } 
    return "Failed to mount FS";
}

boolean Earthchip::mountFS () {
    if (SPIFFS.begin()) {
        return 1;
    } 
    return 0;
}

String Earthchip::readFS() {
    File file = SPIFFS.open(CONFIG_FILE_NAME, "r");
    if (!file) {
        return "";
    }
    String content;
    while (file.available()) {
        content += char(file.read());
    }
    file.close();
    return content;
}

String Earthchip::writeFS() {
    File file = SPIFFS.open(CONFIG_FILE_NAME, "w");
    if (!file) {
        return "no writable file";
    }
    int bytesWritten = file.print(PLANT_NAMES[(rand() % size_of(PLANT_NAMES -1)) + 1]);
 
    if (bytesWritten == 0) {
    file.close();
    return "File write failed";
    
  }
    file.close();
    return "File write success";
}

const char* PLANT_NAMES[] = {"AFRICAN_VIOLET","ALGERIAN_OAK_QUERCUS","AMERICAN_CRESS","AMERICAN_DOGWOOD","AMERICAN_NIGHTSHADE","AMERICAN_WHITE_HELLEBORE","AMERICAN_WINTERBERRY","AMY_ROOT","ANNUAL_SOW_THISTLE","APPALACHIAN_TEA","ARIZONA_SYCAMORE","ARROW_WOOD","ASH_LEAVED_MAPLE","ASIAN_RICE","BABY_ROSE","BANK_CRESS","BASTARD_PELLITORY","BAY_LAUREL","BEAR_CORN","BELLE_ISLE_CRESS","BERMUDA_CRESS","BETULA_LENTA","BIG_HELLEBORE","BIRDS_NEST","BIRDS_NEST_PLANT","BITTER_NIGHTSHADE","BITTER_WEED","BLACK_ALDER","BLACK_ASH","BLACK_BIRCH","BLACK_CAP","BLACK_CHERRY","BLACK_EYED_SUSAN","BLACK_HELLEBORE","BLACK_MAPLE","BLACK_NIGHTSHADE","BLACK_RASPBERRY","BLACK_WEED","BLACKHAW_VIBURNUM","BLACKIE_HEAD","BLUE_ASH","BLUE_BINDWEED","BLUE_OAK","BLUE_OF_THE_HEAVENS","BLUEBERRY_CORNEL","BLUNT_LEAVED_MILKWEED","BOLEAN_BIRCH","BOSTON_FERN_OR_SWORD_FERN","BOW_WOOD","BRILLIANT_CONEFLOWER","BRISTLY_DEWBERRY","BRISTLY_GROUND_BERRY","BRITTLE_BUSH","BROADLEAF_PLANTAIN","BROWN_BETTY","BROWN_DAISY","BROWN_EYED_SUSAN","BUCKEYE_CALIFORNIA_BUCKEYE","BUFFALO_WEED","BULBOUS_CRESS","BULL_NETTLE","BUR_OAK","BUTTERFLY_FLOWER","BUTTERFLY_WEED","CABINET_CHERRY","CALIFORNIA_BAY","CALIFORNIA_BLACK_OAK","CALIFORNIA_BUCKEYE","CALIFORNIA_SYCAMORE","CALIFORNIA_THISTLE","CALIFORNIA_WALNUT","CANADA_ROOT","CANADA_THISTLE","CANCER_JALAP","CANE_ASH","CANOE_BIRCH","CANYON_LIVE_OAK","CAROLINA_AZOLLA","CAROLINA_HORSE_NETTLE","CARROT_WEED","CART_TRACK_PLANT","CATALINA_IRONWOOD","CHAMPION_OAK","CHERRY_BIRCH","CHIGGER_FLOWER","CHRISTMAS_FERN","CLIMBING_NIGHTSHADE","CLUMP_FOOT_CABBAGE","COAST_LIVE_OAK","COAST_POLYPODY","COFFEE_PLANT","COLIC_WEED","COMMON_ALDER","COMMON_DAISY","COMMON_FIG","COMMON_MILKWEED","COMMON_ONION","COMMON_PLANTAIN","COMMON_RAGWEED","COMMON_RAGWORT","COMMON_SERVICEBERRY","COMMON_TANSY","COMMON_YARROW","CORK_OAK","CORN_SOW_THISTLE","CORN_SPEEDWELL","CORN_THISTLE","CORNELIAN_TREE","COTTON_PLANT","COYOTE_WILLOW","CREEK_MAPLE","CREEPING_THISTLE","CREEPING_YELLOW_CRESS","CROWS_NEST","CROWS_TOES","CURSED_THISTLE","CUTLEAF_CONEFLOWER","CUTLEAF_MAPLE","CUTLEAF_TOOTHWORT","DAMASK_VIOLET","DAMES_GILLI_FLOWER","DAMES_ROCKET","DAMES_VIOLET","DEADLY_NIGHTSHADE","DECIDUOUS_HOLLY","DEVILS_BITE","DEVILS_DARNING_NEEDLE","DEVILS_NOSE","DEVILS_PLAGUE","DOGTOOTH_VIOLET","DOORYARD_PLANTAIN","DOWNY_SERVICEBERRY","DUCK_RETTEN","DWARF_WILD_ROSE","DYE_LEAVES","DYERS_OAK","EARLY_WINTER_CRESS","EARTH_GALL","EASTERN_BLACK_OAK","EASTERN_CONEFLOWER","EASTERN_REDBUD","ENGLISH_BULLS_EYE","ENGLISH_OAK","EUROPEAN_FLAX","EUROPEAN_HOLLY","EUROPEAN_PELLITORY","EUROPEAN_WEEPING_BIRCH","EUROPEAN_WHITE_BIRCH","EUROPEAN_WHITE_HELLEBORE","EVERGREEN_HUCKLEBERRY","EVERGREEN_WINTERBERRY","EXTINGUISHER_MOSS","FAIR_MAID_OF_FRANCE","FAIRYMOSS_AZOLLA_CAROLINIANA","FALSE_ALDER","FALSE_BOX","FALSE_BOXWOOD","FALSE_HELLEBORE","FERN_LEAF_CORYDALIS","FERN_LEAF_YARROW","FEVER_BUSH","FIELD_SOW_THISTLE","FLORIDA_DOGWOOD","FLOWERING_DOGWOOD","GARDEN_NIGHTSHADE","GARLIC_MUSTARD","GARLIC_ROOT","GEWA_BANGLADESH","GIANT_ONION","GIANT_RAGWEED","GILLI_FLOWER","GLORIOSA_DAISY","GOLDEN_BUTTONS","GOLDEN_CORYDALIS","GOLDEN_GARLIC","GOLDEN_JERUSALEM","GOODDING_WILLOW","GOOSE_TONGUE","GRAY_ALDER","GRAY_BIRCH","GREAT_RAGWEED","GREATER_PLANTAIN","GREEN_ASH","GREEN_HEADED_CONEFLOWER","GREEN_THISTLE","GROUND_BERRY","HAIRY_BITTERCRESS","HARD_THISTLE","HARES_COLWORT","HARES_THISTLE","HAY_FEVER_WEED","HEALING_BLADE","HEDGE_PLANT","HEMP_DOGBANE","HEN_PLANT","HENBIT_DEADNETTLE","HERB_BARBARA","HISPID_SWAMP_BLACKBERRY","HOARY_RAGWORT","HONEY_MESQUITE","HORSE_CANE","HORSE_NETTLE","HORSETAIL_MILKWEED","HOUNDS_BERRY","INDIAN_ARROW_WOOD","INDIAN_HEMP","INDIAN_PAINTBRUSH","INDIAN_POKE","INDIAN_POSY","INKBERRY_HOLLY","ISLAND_OAK","ISLE_OF_MAN_CABBAGE","ITCH_WEED","JACK_BY_THE_HEDGE","JACK_IN_THE_BUSH","JAPANESE_FLOWERING_DOGWOOD","JUDAS_TREE","KIMBERLY_QUEEN_FERN","KOREAN_ROCK_FERN","KOUSA_DOGWOOD","LACE_FLOWER","LAMBS_CRESS","LAMBS_FOOT","LAND_CRESS","LEATHERLEAF_VIBURNUM","LILY_LEEK","LOVE_VINE","LOW_ROSE","MAHOGANY_BIRCH","MAPLE_ASH","MARSH_RAGWORT","MEADOW_CABBAGE","MEADOW_HOLLY","MILK_THISTLE","MILKY_TASSEL","MIRBECKS_OAK","MOOSE_MAPLE","MOSQUITO_FERN","MOSQUITO_PLANT","MOSSYCUP_WHITE_OAK","MOTHER_OF_THE_EVENING","MOUNTAIN_MAHOGANY","MULTIFLORA_ROSE","NEW_ZEALAND_FLAX","NIGHT_SCENTED_GILLI_FLOWER","NODDING_ONION","NODDING_THISTLE","NORTHERN_RED_OAK","OAK_TREE_QUERCUS","ORANGE_CONEFLOWER","ORANGE_MILKWEED","ORANGE_ROOT","ORANGE_SWALLOW_WORT","OSAGE_ORANGE","OSIER_SALIX","OXFORD_RAGWORT","PACIFIC_DOGWOOD","PALE_CORYDALIS","PAPER_BIRCH","PEDUNCULATE_OAK","PENNSYLVANIA_BLACKBERRY","PENNY_HEDGE","PEPPER_ROOT","PERENNIAL_THISTLE","PETTY_MOREL","PIGEON_BERRY","PIN_OAK","PINK_CORYDALIS","PLANE_EUROPEAN_SYCAMORE","PLEURISY_ROOT","POCAN_BUSH","POISON_IVY","POISON_BERRY","POISON_FLOWER","POLECAT_WEED","POOR_ANNIE","POOR_MANS_MUSTARD","POORLAND_DAISY","PRAIRIE_ROSE","PRICKLY_THISTLE","PURPLE_FLOWERED_TOOTHWORT","PURPLE_RASPBERRY","QUEEN_ANNES_LACE","QUEENS_GILLI_FLOWER","RADICAL_WEED","RAMBLER_ROSE","RED_ASH","RED_BIRCH","RED_DEADNETTLE","RED_INK_PLANT","RED_MULBERRY","RED_OAK","RED_OSIER","RED_RIVER_MAPLE","RED_WILLOW","RED_BRUSH","RED_WEED","REDWOOD_SORREL","RHEUMATISM_ROOT","RIVER_ASH","RIVER_BIRCH","RIVER_MAPLE","ROAD_WEED","ROCK_HARLEQUIN","ROCKET_CRESS","ROGUES_GILLI_FLOWER","ROMAN_WORMWOOD","ROSE_MILKWEED","ROSE_WILLOW","ROUND_LEAF_PLANTAIN","RUM_CHERRY","RUNNING_SWAMP_BLACKBERRY","SAFFRON_CROCUS","SAND_BRIER","SAUCE_ALONE","SCARLET_BERRY","SCARLET_OAK","SCOTCH_CAP","SCRAMBLED_EGGS","SCREW_BEAN_MESQUITE","SCRUB_OAK","SCURVY_CRESS","SCURVY_GRASS","SESSILE_OAK","SHAD_BLOW","SHAD_BLOW_SERVICEBERRY","SHARP_FRINGED_SOW_THISTLE","SILKY_CORNEL","SILKY_DOGWOOD","SILKY_SWALLOW_WORT","SILVER_BIRCH","SILVER_MAPLE","SILVER_RAGWORT","SILVER_LEAF_MAPLE","SKUNK_CABBAGE","SKUNK_WEED","SMALL_FLOWERED_THISTLE","SNAKE_BERRY","SNEEZEWORT_YARROW","SOFT_MAPLE","SOLDIERS_WOUNDWORT","SPANISH_OAK","SPECKLED_ALDER","SPICE_BIRCH","SPINY_LEAVED_SOW_THISTLE","SPINY_SOW_THISTLE","SPOOL_WOOD","SPOTTED_DEADNETTLE","SPOTTED_OAK","SPRING_CRESS","SQUAW_BUSH","STAG_BUSH","STAR_OF_PERSIA","STRAWBERRY_TREE","STRIPED_ALDER","STRIPED_MAPLE","SUGAR_MAPLE","SUMMER_LILAC","SUNDARI_BANGLADESH","SWALLOW_WORT","SWAMP_ASH","SWAMP_CABBAGE","SWAMP_DEWBERRY","SWAMP_DOGWOOD","SWAMP_HELLEBORE","SWAMP_HOLLY","SWAMP_MAPLE","SWAMP_MILKWEED","SWAMP_OAK","SWAMP_SILKWEED","SWAMP_SPANISH_OAK","SWAMP_WHITE_OAK","SWEET_BIRCH","SWEET_ORANGE","SWEET_POTATO","SWEET_POTATO_VINE","SWEET_ROCKET","SWINE_THISTLE","SWORD_FERNS","SYCAMORE_AMERICAN","SYCAMORE_ARIZONA","SYCAMORE_CALIFORNIA","TALL_AMBROSIA","TALL_CONEFLOWER","TASSEL_WEED","THIN_LEAVED_CONEFLOWER","THOUSAND_LEAF","THOUSAND_SEAL","THREE_LEAVED_CONEFLOWER","TICKLE_WEED","TOBACCO_PLANT","TOUCH_ME_NOT","TRAILING_BITTERSWEET","TRAILING_NIGHTSHADE","TRAILING_RED_HUCKLEBERRY","TRAILING_VIOLET_NIGHTSHADE","TRAVELLERS_JOY","TREAD_SOFTLY","TREE_ONION","TREE_SOW_THISTLE","TREE_TOBACCO","TRUE_CINNAMON","TUBER_ROOT","UPLAND_CRESS","VALLEY_OAK","VANILLA_ORCHID","VIOLA_SPECIES","VIOLET_BLOOM","VIRGINIA_SILK_WEED","VIRGINIA_VIRGINS_BOWER","VIRGINIA_WINTERBERRY","VIRGINS_BOWER","WALL_SPEEDWELL","WALNUT_CALIFORNIA_WALNUT","WATER_ASH","WATER_BIRCH","WATER_FERN","WATER_MAPLE","WAY_THISTLE","WAY_BREAD","WAYSIDE_PLANTAIN","WEEPING_BIRCH","WESTERN_REDBUD","WESTERN_SWORD_FERN","WESTERN_TRILLIUM","WESTERN_WAKE_ROBIN","WHISKEY_CHERRY","WHITE_ALDER","WHITE_ASH","WHITE_BIRCH","WHITE_CORNEL","WHITE_HELLEBORE","WHITE_INDIAN_HEMP","WHITE_MANS_FOOT","WHITE_MAPLE","WHITE_MULBERRY","WHITE_OAK","WHITE_ROOT","WHITE_TANSY","WHITE_TRILLIUM","WHORLED_MILKWEED","WILD_BLACK_CHERRY","WILD_CARROT","WILD_CHERRY","WILD_COTTON","WILD_GARLIC","WILD_HOPS","WILD_ONION","WILD_ORANGE","WILD_PELLITORY","WILD_ROSE","WILD_TANSY","WIND_ROOT","WINTER_GILLI_FLOWER","WINTER_ROCKET","WINTERBERRY_HOLLY","WINTER_CRESS","WOODY_NIGHTSHADE","WOOLLY_YARROW","WOUND_ROCKET","YAM_DIOS_COREA","YELLOW_BARK_OAK","YELLOW_BIRCH","YELLOW_CONEFLOWER","YELLOW_CORYDALIS","YELLOW_DAISY","YELLOW_FIELD_CRESS","YELLOW_FUME_WORT","YELLOW_HARLEQUIN","YELLOW_MILKWEED","YELLOW_OX_EYE_DAISY","YELLOW_ROCKET","YELLOW_WOOD", "YELLOW_TREE"};


