#!/usr/bin/python

from Tkinter import *
import tkMessageBox

playerTurn = 0
boxCount = [0,0,0,0,0,0,0,0,0]

def changeCaption(a):
		global playerTurn
   		if playerTurn == 0:
   			playerTurn = 1
   			playerTurnString.set("Player 2's Turn")
             		if a == 0:
				bTxt0.set("X")
				b1.config(state="disabled")
				boxCount[a] = 1
			elif a == 1:
				bTxt1.set("X")
				b2.config(state="disabled")
				boxCount[a] = 1
			elif a == 2:
				bTxt2.set("X")
				b3.config(state="disabled")
				boxCount[a] = 1
			elif a == 3:
				bTxt3.set("X")
				b4.config(state="disabled")
				boxCount[a] = 1
			elif a == 4:
				bTxt4.set("X")
				b5.config(state="disabled")
				boxCount[a] = 1
			elif a == 5:
				bTxt5.set("X")
				b6.config(state="disabled")
				boxCount[a] = 1
			elif a == 6:
				bTxt6.set("X")
				b7.config(state="disabled")
				boxCount[a] = 1
			elif a == 7:
				bTxt7.set("X")
				b8.config(state="disabled")
				boxCount[a] = 1
			elif a == 8:
				bTxt8.set("X")
				b9.config(state="disabled")
				boxCount[a] = 1
   			if (boxCount[0] == 1 and boxCount[1] == 1 and boxCount[2] == 1) or (boxCount[3] == 1 and boxCount[4] == 1 and boxCount[5] == 1) or (boxCount[6] == 1 and boxCount[7] == 1 and boxCount[8] == 1) or (boxCount[0] == 1 and boxCount[3] == 1 and boxCount[6] == 1) or (boxCount[1] == 1 and boxCount[4] == 1 and boxCount[7] == 1) or (boxCount[2] == 1 and boxCount[5] == 1 and boxCount[8] == 1) or (boxCount[0] == 1 and boxCount[4] == 1 and boxCount[8] == 1) or (boxCount[2] == 1 and boxCount[4] == 1 and boxCount[6] == 1): 
				b1.config(state="disabled")
				b2.config(state="disabled")
				b3.config(state="disabled")
				b4.config(state="disabled")
				b5.config(state="disabled")
				b6.config(state="disabled")
				b7.config(state="disabled")
				b8.config(state="disabled")
				b9.config(state="disabled")
				tkMessageBox.showinfo("Congradulations","Player 1 has Won!")
			else:

				if(0 in boxCount):
					 print ""
				else:
					b1.config(state="disabled")
					b2.config(state="disabled")
					b3.config(state="disabled")
					b4.config(state="disabled")
					b5.config(state="disabled")
					b6.config(state="disabled")
					b7.config(state="disabled")
					b8.config(state="disabled")
					b9.config(state="disabled")
					tkMessageBox.showinfo("Stalemate","Nobody has won, the match is a draw.")
				
 		else:
   			playerTurn = 0
   			playerTurnString.set("Player 1's Turn")
			if a == 0:
                                bTxt0.set("O")
                                b1.config(state="disabled")
				boxCount[a] = 2
                        elif a == 1:
                                bTxt1.set("O")
                                b2.config(state="disabled")
				boxCount[a] = 2
                        elif a == 2:
                                bTxt2.set("O")
                                b3.config(state="disabled")
				boxCount[a] = 2
                        elif a == 3:
                                bTxt3.set("O")
                                b4.config(state="disabled")
				boxCount[a] = 2
                        elif a == 4:
                                bTxt4.set("O")
                                b5.config(state="disabled")
				boxCount[a] = 2
                        elif a == 5:
                                bTxt5.set("O")
                                b6.config(state="disabled")
				boxCount[a] = 2
                        elif a == 6:
                                bTxt6.set("O")
                                b7.config(state="disabled")
				boxCount[a] = 2
                        elif a == 7:
                                bTxt7.set("O")
                                b8.config(state="disabled")
				boxCount[a] = 2
                        elif a == 8:
                                bTxt8.set("O")
                                b9.config(state="disabled")
				boxCount[a] = 2

   			if (boxCount[0] == 2 and boxCount[1] == 2 and boxCount[2] == 2) or (boxCount[3] == 2 and boxCount[4] == 2 and boxCount[5] == 2) or (boxCount[6] == 2 and boxCount[7] == 2 and boxCount[8] == 2) or (boxCount[0] == 2 and boxCount[3] == 2 and boxCount[6] == 2) or (boxCount[1] == 2 and boxCount[4] == 2 and boxCount[7] == 2) or (boxCount[2] == 2 and boxCount[5] == 2 and boxCount[8] == 2) or (boxCount[0] == 2 and boxCount[4] == 2 and boxCount[8] == 2) or (boxCount[2] == 2 and boxCount[4] == 2 and boxCount[6] == 2): 
				b1.config(state="disabled")
				b2.config(state="disabled")
				b3.config(state="disabled")
				b4.config(state="disabled")
				b5.config(state="disabled")
				b6.config(state="disabled")
				b7.config(state="disabled")
				b8.config(state="disabled")
				b9.config(state="disabled")
				tkMessageBox.showinfo("Congradulations","Player 2 has Won!")
			else:

				if(0 in boxCount):
					 print ""
				else:
					b1.config(state="disabled")
					b2.config(state="disabled")
					b3.config(state="disabled")
					b4.config(state="disabled")
					b5.config(state="disabled")
					b6.config(state="disabled")
					b7.config(state="disabled")
					b8.config(state="disabled")
					b9.config(state="disabled")
					tkMessageBox.showinfo("Stalemate","Nobody has won, the match is a draw.")


root = Tk()
root.title("Tic Tac Toe")
root.geometry('400x400')

bTxt0=StringVar()
bTxt1=StringVar()
bTxt2=StringVar()
bTxt3=StringVar()
bTxt4=StringVar()
bTxt5=StringVar()
bTxt6=StringVar()
bTxt7=StringVar()
bTxt8=StringVar() 

playerTurnString = StringVar()


b1=Button(root,textvariable=bTxt0,command=lambda:changeCaption(0),width=10,height=10)
b1.grid(row=2,column=0)

b2=Button(root,textvariable=bTxt1,command=lambda:changeCaption(1),width=10)
b2.grid(row=2,column=1)

b3=Button(root,textvariable=bTxt2,command=lambda:changeCaption(2),width=10)
b3.grid(row=2,column=2)

b4=Button(root,textvariable=bTxt3,command=lambda:changeCaption(3),width=10)
b4.grid(row=3,column=0)

b5=Button(root,textvariable=bTxt4,command=lambda:changeCaption(4),width=10)
b5.grid(row=3,column=1)

b6=Button(root,textvariable=bTxt5,command=lambda:changeCaption(5),width=10)
b6.grid(row=3,column=2)

b7=Button(root,textvariable=bTxt6,command=lambda:changeCaption(6),width=10, height = 10)
b7.grid(row=4,column=0)

b8=Button(root,textvariable=bTxt7,command=lambda:changeCaption(7),width=10)
b8.grid(row=4,column=1)

b9=Button(root,textvariable=bTxt8,command=lambda:changeCaption(8),width=10)
b9.grid(row=4,column=2)


playerTurnLabel = Label(root, textvariable = playerTurnString, width = 10)
playerTurnLabel.grid(row=0, column = 1)
bTxt0.set(" ")
bTxt1.set(" ")
bTxt2.set(" ")
bTxt3.set(" ")
bTxt4.set(" ")
bTxt5.set(" ")
bTxt6.set(" ")
bTxt7.set(" ")
bTxt8.set(" ")
playerTurnString.set("Player 1's Turn")
root.mainloop()
