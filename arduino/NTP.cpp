#include "NTP.h"

/*

Udp NTP Client

Get the time from a Network Time Protocol (NTP) time server
Demonstrates use of UDP sendPacket and ReceivePacket
For more on NTP time servers and the messages needed to communicate with them,
see http://en.wikipedia.org/wiki/Network_Time_Protocol

created 4 Sep 2010
by Michael Margolis
modified 9 Apr 2012
by Tom Igoe
modified 02 Sept 2015
by Arturo Guadalupi

This code is in the public domain.

*/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

unsigned int localPort = 8888;				// Local port to listen for UDP packets
const char timeServer[] = "pool.ntp.org";   // time.nist.gov NTP server
const int NTP_PACKET_SIZE = 48;				// NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE];			// Buffer to hold incoming and outgoing packets
EthernetUDP Udp;							// A UDP instance to let us send and receive packets over UDP

void ntp_init()
{
	Serial.print(F("Init NTP..."));
	if (!Udp.begin(localPort))
		Serial.println(F("failed"));
	else
		Serial.println(F("Done"));
}

// send an NTP request to the time server at the given address
bool send_ntp_packet(const char * address)
{
	// set all bytes in the buffer to 0
	memset(packetBuffer, 0, NTP_PACKET_SIZE);
	// Initialize values needed to form NTP request
	// (see URL above for details on the packets)
	packetBuffer[0] = 0b11100011;   // LI, Version, Mode
	packetBuffer[1] = 0;			// Stratum, or type of clock
	packetBuffer[2] = 6;			// Polling Interval
	packetBuffer[3] = 0xEC;			// Peer Clock Precision
									// 8 bytes of zero for Root Delay & Root Dispersion
	packetBuffer[12] = 49;
	packetBuffer[13] = 0x4E;
	packetBuffer[14] = 49;
	packetBuffer[15] = 52;

	// all NTP fields have been given values, now you can send a packet requesting a timestamp:
	bool begin = Udp.beginPacket(address, 123); // NTP requests are to port 123
	bool write = Udp.write(packetBuffer, NTP_PACKET_SIZE);
	bool end = Udp.endPacket();
	return begin && write && end;
}

uint32_t ntp_request_time()
{
	Serial.print(F("NTP time..."));

	bool send = send_ntp_packet(timeServer); // send an NTP packet to a time server
	if (!send)
	{
		Serial.println(F("send_fail"));
		return 0;
	}

	for (int waiting = 0; waiting < 10; waiting++)
	{
		delay(10);			   // wait a bit to see if a reply is available
		
		if (Udp.parsePacket())
		{
			//Serial.print(F("done in "));
			//Serial.print(waiting);
			//Serial.print(F("0ms - time: "));

			// We've received a packet, read the data into the buffer
			Udp.read(packetBuffer, NTP_PACKET_SIZE);

			// The timestamp starts at byte 40 of the received packet and is four bytes,
			// or two words, long. First, extract the two words:
			uint32_t highWord = word(packetBuffer[40], packetBuffer[41]);
			uint32_t lowWord = word(packetBuffer[42], packetBuffer[43]);
			// combine the four bytes (two words) into a long integer
			// this is NTP time (seconds since Jan 1 1900):
			uint32_t secsSince1900 = highWord << 16 | lowWord;
			//Serial.print(F("Seconds since Jan 1 1900 = "));
			//Serial.println(secsSince1900);

			// now convert NTP time into everyday time:
			//Serial.print(F("Unix time = "));
			// Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
			const uint32_t seventyYears = 2208988800UL;
			// subtract seventy years:
			uint32_t epoch = secsSince1900 - seventyYears;
			// print Unix time:
			//Serial.print(epoch);

			// print the hour, minute and second:
			//Serial.print(F("-The UTC time is "));	// UTC is the time at Greenwich Meridian (GMT)
			//Serial.print((epoch % 86400L) / 3600);	// print the hour (86400 equals secs per day)
			//Serial.print(F(":"));
			//if (((epoch % 3600) / 60) < 10)			// In the first 10 minutes of each hour, we"ll want a leading "0"
			//	Serial.print(F("0"));
			//Serial.print((epoch % 3600) / 60);		// print the minute (3600 equals secs per minute)
			//Serial.print(F(":"));
			//if ((epoch % 60) < 10)					// In the first 10 seconds of each minute, we"ll want a leading "0"
			//	Serial.print(F("0"));
			//Serial.println(epoch % 60);				// print the second

			Serial.println(epoch);
			return epoch;
		}
	}
	Serial.println(F("failed"));
	return 0;
}

uint32_t ntp_request_time_safe()
{
	Serial.print(F("Maintain ethernet..."));
	int eth = Ethernet.maintain();
	Serial.println(eth);

	Serial.println(F("Request NTP..."));

	uint32_t timecurr = 0;
	uint32_t timeprev = 0;
	int timei = 0;
	for (int i = 0; i < 50; i++) // we want 3 consequative right ones (sometimes one is off)
	{
		timecurr = ntp_request_time();
		if (timecurr == 0)
		{
			timei = 0;
		}
		else if (timei > 0 && (timecurr - timeprev < -5.0 || timecurr - timeprev  > 5.0))
		{
			timei = 0;
		}
		else if (timei == 2)
		{
			Serial.println(F("Succes"));
			return timecurr;
		}
		else
		{
			timeprev = timecurr;
			timei++;
		}
	}
	Serial.println(F("Fail"));
	return 0;
}