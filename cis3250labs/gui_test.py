#!/usr/bin/python

from Tkinter import *
import tkMessageBox 
                    
def helloMessage(): 
    tkMessageBox.showinfo( "Hello ...", "You clicked on display message button!")

root = Tk() 

bDisplayMessage = Button(root, text ="Display Message", command = helloMessage)
bDisplayMessage.pack()
root.mainloop()