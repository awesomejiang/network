This is the first project of network.

#Target
Build a simple echo system including a echo server and a echo client:   
1. Server can accept single-line messages from client and echo it back.     
2. Client sends messages to server and accept the echo from server.

#Calling
1. Compile files by makefile

2. Open a terminal, input       
    ```
    ./echo_server <port>
    ```
3. OPen a new terminal, input       
    ```
    ./echo_client <host> <port>
    ```

    P.S.        
    i.  In the case that running server and client in same machine, host should be "127.0.0.1".        
    ii. Multi clients are suported.

3. Follow the instruction of ./echo_client, input some test strings. Empty input will return empty echo.