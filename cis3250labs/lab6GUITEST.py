#!/usr/bin/python
from Tkinter import *
def pressButton():
    # myText = "You change the text!"
    # label_text.set("myText") #change the label’s text to myText when the button
                           # is clicked/pressed
    return
top = Tk()
label_text=StringVar()
labelTest= Label(top, textvariable=label_text,width=60)
labelTest.pack()
num=1235
label_text.set(str(num))  #set the label’s text at the start of program
                          # to the the string  "1234"
bPress = Button(top, text ="Change Label Text", command = pressButton )
bPress.pack()
top.mainloop()
