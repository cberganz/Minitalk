# Minitalk

| Project Name | Minitalk |
| :-: | :-: |
| Description | Using unix signals to send messages between a server and a client |
| Technologies | <a href="#"><img alt="C" src="https://custom-icon-badges.demolab.com/badge/C-03599C.svg?logo=c-in-hexagon&logoColor=white&style=for-the-badge"></a> |
| External libraries | write(), signal(), sigemptyset(), sigaddset(), sigaction(), kill(), getpid(), malloc(), free(), pause(), sleep(), usleep(), exit() |
| Final grade | 125/125 |

## Usage
```
git clone https://github.com/cberganz/Minitalk.git
cd Minitalk
make bonus
./server_bonus
```
The server will return its PID so clients can connect :
```
./client_bonus SERVER_PID
```
-> Client can now send messages to the server
