This is the first project of network.

#Target
Build a simple echo system including a echo server and a echo client:   
1. Server can accept single-line messages from client and echo it back.     
2. Client sends messages to server and accept the echo from server.

#Calling
1. Open a terminal, input       
    ```
    python echo_server.py <port>
    ```
2. OPen a new terminal, input       
    ```
    python echo_client.py <host> <port>
    ```

    P.S.        
    i.  In the case that running server and client in same machine, host can be "localhost".        
    ii. Multi clients are suported.

3. Follow the instruction of echo_client.py, input some test strings. Empty input will be ignored.