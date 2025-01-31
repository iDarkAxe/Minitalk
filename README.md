# Simple Communication Protocol using Unix Signals #
2 Binaries, `server` for listening all messages and `client` to send messages.

# How does it work #
Each character of the string will be cut in 8 pieces (8 bits) and send separetely using `kill` function to send Unix Signals.
`SIGUSR1` is used for 1 (ones) and `SIGUSR2` for 0 (zeros).

There is near 0 down time in the client as it's not using `sleep()` or `usleep()`.
When 8 bits are send, the server concatenes it into a string and waits for the end character to print the string.

The server send an ACK (acknoledgment) signal (`SIGUSR1`) to client when a bit is received.
If the client receives nothing, it will end itself after a fixed time (TIMEOUT defined in `ft_client.h`).
When 8 bits are received by `server`, the `server` sends a `SIGUSR2` signal to say "wait for my processing time".

# How to use `server` #
Just start it using :
```sh
./server
```
It will wait for signals indefinitely and should never end by itself.
It's PID (Process Identifier) should be written in the terminal.

Do Ctrl+C or send a UNIX Signal (any except `SIGUSR1` and `SIGUSR2`) to terminate the program. 

# How to use `client` #
Just start it using :
```sh
./client <PID> <string>
```
PID is the server PID to send the string.

String can be void so just a '\0' should be send.
String can be used from a shell evaluation like :
```sh
./client <PID> $(cat <path_to/some file>)
```

For the bonus version, `<PID>` is not required (it will find the PID of server by itself).
