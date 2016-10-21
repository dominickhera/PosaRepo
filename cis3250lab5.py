#!/usr/bin/python

from Tkinter import *
import tkMessageBox 
  
root = Tk()

e = Entry(root)
e.pack()

e.focus_set()

def grabData():
    print e.get()

b = Button(root, text="Validate", width=60, command=grabData)
b.pack()

root.mainloop()
# e = Entry(root, width=50)
# e.pack()

# text = e.get()


# text = content.get()
# content.set(text)                  
# def helloMessage(): 
#     tkMessageBox.showinfo( "Hello ...", "You clicked on display message button!")

# root = Tk() 

# bDisplayMessage = Button(root, text ="Validate", command = helloMessage)

# bDisplayMessage.pack()
# root.mainloop()