#coding=utf-8
#detail:for chatroom
#name:AntiyChatServer.py
#time:2016-3-22


import socket
import threading

SEND_BUF_SIZE = 16384
RECV_BUF_SIZE = 16384
class AntiyChatServer:

    def __init__ (self):
        host = "192.168.1.251"
        port = 4423
        self.mysoc = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        self.mysoc.bind((host,port))
        self.mysoc.listen(5)
        self.socklist = []
        #bufsize = self.mysoc.getsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF)  
        #print "Buffer size [Before]: %d" %bufsize  
        #self.mysoc.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)  
        self.mysoc.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, SEND_BUF_SIZE)  
        #self.mysoc.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, RECV_BUF_SIZE)
        #bufsize = self.mysoc.getsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF)  
        #print "Buffer size [After]: %d" %bufsize 
    
    def __del__(self):  
        self.mysoc.close()
        for i in self.socklist:
            i.close()
            
    def ClientThread (self,sock,addr):
        sock.send('welcome to Antiy Chat Room!\n')
        while True:
            try:
                buf = sock.recv(1024)
            except socket.error , msg:
                #self.socklist.remove(sock)
                print addr + 'has left'
                break
            if buf:
                print buf
                print len(self.socklist)
                for i in self.socklist:
                    try:
                        i.send(buf)
                    except socket.error , msg:
                        self.socklist.remove(i)
        sock.close()    


        
    def StartServer (self):
        while True:
            connectsocket,addr = self.mysoc.accept()
            print 'connect ',addr
            self.socklist.append(connectsocket)
            t = threading.Thread(target=self.ClientThread, args=(connectsocket,addr))
            t.start()
            #connectsocket.close()
            
  
        

if __name__ == "__main__":
    antiy = AntiyChatServer()
    antiy.StartServer()
    
