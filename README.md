# Client-Server-socket-app




Task Brief:
Write Linux based Client/Server socket application:
  
  ● Use C or C++ as a programming language (C is preferable)
  
  ● Use Makefile as a program building tool
  
  ● Push the project into github

Server Requirements:
  1. Server shall allow a maximum of 5 clients to connect simultaneously.
  2. Server shall have a command handler that can receive commands from Client and
  respond back. The following commands must be supported in Server command handler:
  
  a. disconnect
  Once the Server receives this command from the Client, it should close the
  connection with the Client.
  
  b. shell “COMMAND”
  Once the Server receives this command from the Client it should execute the COMMAND as Shell command and send the response back to Client.
  
  From Client side:
  
  Client> shell “pwd”
    /home/user/server/

Client Requirements:
  1. Client shall provide CLI (command line interface)
  2. Following commands must be supported by Client:
  
  a. connect <IP_ADDRESS> <PORT>
  Where the “IP_ADDRESS” is IP Address of the Server and the “PORT”is Server
  Port Number
  
  b. disconnect
  
  c. shell “COMMAND”

  ## USAGE

  1)make 

  if 'readline/readline.h' file not found
  install this
  sudo apt-get install libreadline-dev 

  2)./server

  3)./client "127.0.0.1" "4242" 
    for localhost
    or for you ip_address "ifconfig | grep inet" 
    ./client "IP_ADDRESS" "4242"
  
  4)shell "shell_command"
    for example shell "ls -la"

  5)disconnect (or crtl+c)
    for close the connection with the Client

