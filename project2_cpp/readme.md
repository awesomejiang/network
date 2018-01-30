This is the second project of network.

#Target
Build a simple http server which:       
1. Can deal with GET and HEAD request from both "curl" and browsers.        
2. Can response with basic header fields.       
3. Can redirect client to correct website if neccessary.        
4. Do not supporrt other request and consistent-connection.     

#Calling
1. Use make to compile project
Note that low version of compiler may fail to compile it because I use some new charcteristics in c++17. 

2. To open a terminal, input       
```
    ./http_server <port>
```
