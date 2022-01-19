# [Network Programming Assignment](https://github.com/mukezhz/NetworkProgramming/tree/main/assignment)

Project 1: Design and implement TCP client and TCP Server applications using unix network programming for providing registration numbers to the client.

## Requirement:
1. The server contains a buffer in the linked list where each node contains information about the client. **(node should contain id, name, registration no and msg_sent_count)**
2. The client establishes a connection to the server with its **unique ID number** (use your roll no) sent via command-line argument during sending a connection request.
3. The server sends user information on the basis of the provided ID number. Search the above ID number in the linked list and prepare the message and send it to the cliet and increment msg_sent_count.
4. After sending client information from the server, print all information of the respective client in the server console as well.
5. After receiving the first message by the client, if prints the received message in its console and sends "Thank You" message to the server.
6. Server sends asking information immediately after receiving "Thank You" message from client that if he wishes to see the same information again.
7. If server receives again messages from the client it sends the same information again and increments msg_send_count for that client.
8. Your servermust support multiple simultaneous connections.
9. If a client wants to quit, take input **"quit"** from the console, and the client terminates. If a client wants to see the same information again, input **"again"** from the console and send a request to the server.
10. Your server must not support more that 10 simultaneous clients.

Use select() statement to check if the input is coming from the keyboard or from which of the clients.

- The server is started with: **tcpInfoServer -p port**
- The client is strted with: **tcpInfoClient -h serveraddress -p port -n IDNumber**

### Use the following messages rules:
### Information messages from the server to client

- 1. Welcome << Yourname >>, Your unique identification key is << RegistrationNo. >> (Replace <<Yourname>> and <<Registration>> to your roll no and registration no.)
- 3. Do you want to see your information again?

### Message from client to server to see information respectively

- 2. Thank you
- 4. Again
  
**Develop necessary protocols if required to complete the application.**
  
## Steps to compile and run

### Clone the repo then:

```
cd assignment/
  
make clean

make dir

make

cd bin/

- The server is started with: ./tcpInfoServer -p port
- The client is strted with: ./tcpInfoClient -h serveraddress -p port -n IDNumber
```
