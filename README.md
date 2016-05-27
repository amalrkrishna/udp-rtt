# udp-rtt
Create a UDP based MyPing utility to measure round trip time between two computers.

1. Run the UDP server code in the host computer.
2. After making sure the UDP server code is running in the host computer get the details of the IP address of the host computer and enter it in the UDP client code.
3. Run the UDP client code.
4. The packets to be send to the host should be either given as input or will be automatically taken from the text.txt file placed in the same folder.
5. The packet length can be determined from the UDP client code, currently the packet size is set as 6.
6. The packets will be received at the server side.
7. Average time is calculated upon averaging the time difference.


 	rttserver_udp.c : UDP Server
 	rttclient_udp.c : UDP Client which takes input at terminal
 	rttclient_udp_fileinput.c : UDP Client which takes input from text.txt
