#!/usr/bin/python
from Tkinter import *
def changeCaption(a):
    bTxt.set('The value passed to the function << ' + str(a)+ ' >>')
root = Tk()
root.title("A Test Program")
root.geometry('800x500')
x=123456789
bTxt=StringVar()  # creates a string variable which is assigned to a button's caption
# creates a button object with the length of 80 chars, links it to changeCaption()
# and passes variable x to the function when the button is clicked.
b=Button(root,textvariable=bTxt,command=lambda:changeCaption(x),width=80)
b.grid(row=0,column=0) # places the button at location (0,0) on a grid
bTxt.set("Click here...")  # sets the button's caption at the beginning
root.mainloop()