	          ORG         $8000
  
  solveQuad   LINK    A6,#0
              ;MOVEM.L D2-D5,-(SP)
              MOVE    12(A6),D2
              MULU    D2,D2
              MULU    #5,D2
              MOVE    12(A6),D3
              MOVE    10(A6),D4
              MULU    #2,D3
              MULU    D4,D3
              MOVE    8(A6),D5
              MULU    D5,D5
   
              SUB     D3,D2
              ADD     D2,D5
              MOVE    D5,D1
              ;MOVEM.L (SP)+,D2-D5
              UNLK    A6
              RTS
  	START:
  
	 MAIN    LINK        A6,#-6
	         MOVE        D0,-2(A6)
	         MOVE        D1,-4(A6)
	         MOVE        D2,-6(A6)
	         MOVE        -2(A6),-(A7)
	         MOVE        -4(A6),-(A7)
	         MOVE        -6(A6),-(A7)
	         JSR         solveQuad
	         LEA         4(A7),A7
	         UNLK        A6
	         RTS
	          
	         TRAP        #14
      		 END         START