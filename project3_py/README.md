This is the third project of network.

#Target
Build a UDP client which:       
1. Can send UDP datagram to given server. In this project, client will send ```PING seq_number timestamp``` to server periodically.      
2. Support timeout setting.     


#Compile
1. Compile server by

```
    javac PingServer.java
```
2. python client file do not need compile.


#Calling
1. Open a terminal, input     
```
    java PingServer --port=<server port> --loss_rate=<loss rate> --avg_delay=<delay time>
```
to open a server.       

2. Input
```
    python ping_client.py [options]
```
to open a client.       
Use --help or -h to call usage.
```
[options]:
    -h/--help:                       call usage function
    --server_ip=<server ip addr>:    default: hostname
    --server_port=<server port>:     default: 8080
    --count=<number of pings>:       default: 10
    --period=<wait interval>:        default: 1000(ms)
    --timeout=<timeout>:             default: 10000(ms)
```
