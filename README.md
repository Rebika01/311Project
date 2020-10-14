# 311Project
311 Websocket Project

So the use of our program would likely be on two different machines, with serverC and serverG being on one machine,
while the client is on another machine.  Because of this, the makefile as it is right now isn't terribly useful except to modify for
use on whatever machine you are on.  Anyway, as he described in class (I'll upload a screenshot of the diagram shortly) serverC accepts game requesets
from a client, and forks to create a new process running serverG.  So there will be one serverC handling multiple serverG processes and there
is one serverG for every client.  
